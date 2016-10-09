function Lect1(F,V)

% Start a new figure
figure
hold on

colours={'red','blue'};

% Plot the reference coordinate frame
plot3(0,0,0,'k.','MarkerSize',20);
plot3([0;5],[0;0],[0;0],'red','LineWidth',3);
plot3([0;0],[0;5],[0;0],'green','LineWidth',3);
plot3([0;0],[0;0],[0;5],'blue','LineWidth',3);

% Draw the two objects
for ind = 1:length(F)
    if ~isempty(F{ind}) && ~isempty(V{ind})
        patch('Vertices', V{ind}, 'Faces', F{ind}, ...
            'FaceColor', colours{ind},...
            'EdgeColor', 'none',...
            'AmbientStrength', 0.4, ...
            'DiffuseStrength', 0.8, ...
            'SpecularStrength', 0.2, ...
            'SpecularColorReflectance', 0.5, ...
'FaceLighting', 'gouraud');
    end
end

% Add lights on the figure to make the objects visible
light('Parent', gca, 'Position', [1 1 1],    'Style', 'infinite', 'Color', [1 1 1]);
light('Parent', gca, 'Position', [-1 -1 -1], 'Style', 'infinite', 'Color', [1 1 1]);

set(gca,'DataAspectRatio',[1 1 1]);