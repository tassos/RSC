function DHparams
%% Function for drawing the segments of a robot and their coordinate frames
% Input:        M          Cell array of size N. Each element represents a
%                               fundamendal transformation (Rotation or
%                               Translation). The coordinate frames are
%                               drawn after each transformation and
%                               segments are drawn between transformations
    clear all
    global th d a r
    
    th{1}=90;
    d{1}=0;
    a{1}=2;
    r{1}=2;

    

    scrsz = get(groot,'ScreenSize')./2;
    figure('Position',[1 scrsz(4) scrsz(3) scrsz(4)]);
    xlim([-5 5]); ylim([-5 5]); zlim([-5 5]);
    % Set the ascpect ratio to 1 for each direction and set the camera at
    % point [1,1,1], looking towards point [0,0,0]
    set(gca,'DataAspectRatio',[1 1 1]);
    view(-235,45);
    
    handles.ut = uicontrol('Style', 'slider','Min',-90,'Max',90,'Value',th{1},'Position', [scrsz(3)-130 80 120 20]);
    handles.lut = uicontrol('style','text','string','θ 90','position',[scrsz(3)-170 80 40 20]);
    handles.ua = uicontrol('Style', 'slider','Min',-90,'Max',90,'Value',a{1},'Position', [scrsz(3)-130 60 120 20]);
    handles.lua = uicontrol('style','text','string','α 2','position',[scrsz(3)-170 60 40 20]);
    handles.ud = uicontrol('Style', 'slider','Min',-5,'Max',5,'Value',d{1},'Position', [scrsz(3)-130 40 120 20]);
    handles.lud = uicontrol('style','text','string','d 0','position',[scrsz(3)-170 40 40 20]);
    handles.ur = uicontrol('Style', 'slider','Min',-5,'Max',5,'Value',r{1},'Position', [scrsz(3)-130 20 120 20]);
    handles.lur = uicontrol('style','text','string','r 2','position',[scrsz(3)-170 20 40 20]);
    h = uicontrol('style','popup','string',{'seg 1'},'Position',[10 80 120 20],'Callback',@(hObject,event)updateSliders(hObject,handles));
    uicontrol('style','pushbutton','string','Add segment','Position',[10 50 120 20],'Callback',@(hObject,event)addSegment(h));
    uicontrol('style','pushbutton','string','Remove segment','Position',[10 30 120 20],'Callback',@(hObject,event)removeSegment(h));
    addlistener(handles.ut,'ContinuousValueChange',@(hObject, event)listenSliders(h,handles));
    addlistener(handles.ua,'ContinuousValueChange',@(hObject, event)listenSliders(h,handles));
    addlistener(handles.ud,'ContinuousValueChange',@(hObject, event)listenSliders(h,handles));
    addlistener(handles.ur,'ContinuousValueChange',@(hObject, event)listenSliders(h,handles));
    
    DrawRobot
end

function DrawRobot
    global th a d r
    
	for i=1:length(th)
        Z{i}=[cosd(th{i}) -sind(th{i}) 0 0;sind(th{i}) cosd(th{i}) 0 0;0 0 1 d{i};0 0 0 1];
        X{i}=[1 0 0 r{i};0 cosd(a{i}) -sind(a{i}) 0;0 sind(a{i}) cosd(a{i}) 0;0 0 0 1];
        M{i}=Z{i}*X{i};
    end

    cla(gca);
    P=eye(4);
    DrawCoord(P,2);
    for i=1:length(M)
        N=eye(4);
        for k=i:-1:1
            N=M{k}*N;
        end
        DrawCoord(N,1);
        DrawSegment(P,N);
        P=N;
    end
end

function obj = DrawSegment(M1,M2)
%% Function to draw a segment of a robot, based on the transformation matrices of its beginning and end points
    M=[M1(1:3,4)';M2(1:3,4)'];
    obj = plot3(M(:,1),M(:,2),M(:,3),'LineWidth',8);
end

function obj = DrawCoord(M,L)
%% Function to draw a coordinate frame in a 3D plot.
% Inputs: M     4x4 Homogenous transformation matrix
%              L       scalar indicating the length of the axes
%The colours of the coordinate frame are either black when l=2 or red,
%green and blue for the X, Y, and Z axes respectively
    
    %Obtain the direction and position of each of the axes of the
    %coordinate frame (CoX, CoY, CoZ) and the position of the
    %center of the frame
    CoX = M(1:3,4)+L*M(1:3,1);
    CoY = M(1:3,4)+L*M(1:3,2);
    CoZ = M(1:3,4)+L*M(1:3,3);
    CoO = M(1:3,4);

    axes(gca)
    hold on

    %Set the colours for the big (l=2) coordinate frame
    if L==2;
        colours={'k','k','k'};
    else
        colours={'r','g','b'};
    end
    % Plot origin in bone-plot
    obj{1} = plot3(CoO(1),CoO(2),CoO(3),'k.','MarkerSize',20);
    % Draw X-axis
    obj{2} = plot3([CoO(1);CoX(1)],[CoO(2);CoX(2)],...
        [CoO(3);CoX(3)],colours{1},'LineWidth',3);
    % Draw Y-axis
    obj{3} = plot3([CoO(1);CoY(1)],[CoO(2);CoY(2)],...
        [CoO(3);CoY(3)],colours{2},'LineWidth',3);
    % Draw Z-axis
    obj{4} = plot3([CoO(1);CoZ(1)],[CoO(2);CoZ(2)],...
        [CoO(3);CoZ(3)],colours{3},'LineWidth',3);
end

function addSegment(h)
    global th a d r
    
    segs = get(h,'String');
    idx = length(segs)+1;
    th{idx}=90;
    a{idx}=0;
    d{idx}=2;
    r{idx}=2;
    set(h,'String',[segs;['seg ',num2str(idx)]])
    set(h,'Value',idx)
    DrawRobot
end

function removeSegment(h)
    global th a d r
    segs = get(h,'String');
    idx=length(segs);
    
    if idx>1
        th(idx)=[];
        a(idx)=[];
        d(idx)=[];
        r(idx)=[];
        set(h,'String',segs(1:end-1))
        set(h,'Value',min(idx-1,get(h,'Value')))
        DrawRobot
    end
end

function listenSliders(h,handles)
    global th a d r
    
    idx = get(h,'Value');
    th{idx} = get(handles.ut,'Value');
    set(handles.lut,'string',['θ ',num2str(th{idx})]);
    a{idx} = get(handles.ua,'Value');
    set(handles.lua,'string',['α ',num2str(a{idx})]);
    d{idx} = get(handles.ud,'Value');
    set(handles.lud,'string',['d ',num2str(d{idx})]);
    r{idx} = get(handles.ur,'Value');
    set(handles.lur,'string',['r ',num2str(r{idx})]);
    DrawRobot
end

function updateSliders(hObject,handles)
    global th a d r
    h = get(hObject,'Value');
    set(handles.ut,'Value',th{h});
    set(handles.ua,'Value',a{h})
    set(handles.ud,'Value',d{h})
    set(handles.ur,'Value',r{h})
end