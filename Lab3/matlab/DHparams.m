function DHparams
%% Function for drawing the segments of a robot and their coordinate frames
% Input:        M          Cell array of size N. Each element represents a
%                               fundamendal transformation (Rotation or
%                               Translation). The coordinate frames are
%                               drawn after each transformation and
%                               segments are drawn between transformations

theta=0;
delta=0;
alpha=0;
rho=0;

	Z=[cosd(theta) -sind(theta) 0 0;sind(theta) cosd(theta) 0 0;0 0 1 delta;0 0 0 1];
    X=[1 0 0 rho;0 cosd(alpha) -sind(alpha) 0;0 sind(alpha) cosd(alpha) 0;0 0 0 1];
    M={Z*X};

    scrsz = get(groot,'ScreenSize')./2;
    figure('Position',[1 scrsz(4) scrsz(3) scrsz(4)]);
    xlim([-5 5]); ylim([-5 5]); zlim([-5 5]);
    DrawRobot(M);
    
    utheta=uicontrol('Style', 'slider','Min',-90,'Max',90,'Value',theta,'Position', [scrsz(3)-130 80 120 20]);
    uicontrol('style','text','string','θ','position',[scrsz(3)-140 80 10 20]);
    ualpha=uicontrol('Style', 'slider','Min',-90,'Max',90,'Value',alpha,'Position', [scrsz(3)-130 60 120 20]);
    uicontrol('style','text','string','α','position',[scrsz(3)-140 60 10 20]);
    udelta=uicontrol('Style', 'slider','Min',-5,'Max',5,'Value',delta,'Position', [scrsz(3)-130 40 120 20]);
    uicontrol('style','text','string','d','position',[scrsz(3)-140 40 10 20]);
    urho=uicontrol('Style', 'slider','Min',-5,'Max',5,'Value',rho,'Position', [scrsz(3)-130 20 120 20]);
    uicontrol('style','text','string','r','position',[scrsz(3)-140 20 10 20]);
    addlistener([utheta,ualpha,udelta,urho],'ContinuousValueChange',@(hObject, event) calculateMatrix(utheta,ualpha,udelta,urho));
end

function DrawRobot(M)
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
    
    % Set the ascpect ratio to 1 for each direction and set the camera at
    % point [1,1,1], looking towards point [0,0,0]
    set(gca,'DataAspectRatio',[1 1 1]);
    view(-235,45);
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

function calculateMatrix(utheta,ualpha,udelta,urho)
    theta=get(utheta,'Value');
    alpha=get(ualpha,'Value');
    delta=get(udelta,'Value');
    rho=get(urho,'Value');
    
	Z=[cosd(theta) -sind(theta) 0 0;sind(theta) cosd(theta) 0 0;0 0 1 delta;0 0 0 1];
    X=[1 0 0 rho;0 cosd(alpha) -sind(alpha) 0;0 sind(alpha) cosd(alpha) 0;0 0 0 1];
    M={Z*X};
    DrawRobot(M);
end