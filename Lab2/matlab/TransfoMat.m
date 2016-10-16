function R = TransfoMat(type,axis,value)
%% Function to determine the homogenious transformation matrix R of a rotation or translation
% Inputs:   Type:         string. It can be either 'r' for rotations or 't'
%                                           for translations
%               Axis:         string. It can be either 'x','y',or 'z'
%                                           representing the axis that the transformation
%                                           will happen
%                                           about
%               Value:       scalar. It is the value of the rotation or
%                                           translation that is required

    switch type
        case 'r'
            switch axis
                case 'x'
                    R = Rx(value);
                case 'y'
                    R = Ry(value);
                case 'z'
                    R = Rz(value);
            end
        case 't'
            switch axis
                case 'x'
                    R = Tx(value);
                case 'y'
                    R = Ty(value);
                case 'z'
                    R = Tz(value);
            end
    end
end

function R = Rz(theta)
%% Function to calculate a homogenious transformation matrix R for a rotation of theta radians around the z axis
    R = [cos(theta) -sin(theta) 0 0;sin(theta) cos(theta) 0 0;0 0 1 0;0 0 0 1];
end

function R = Rx(phi)
%% Function to calculate a homogenious transformation matrix R for a rotation of phi radians around the x axis
    R = [1 0 0 0;0 cos(phi) -sin(phi) 0;0 sin(phi) cos(phi) 0;0 0 0 1];
end

function R = Ry(gama)
%% Function to calculate a homogenious transformation matrix R for a rotation of gama radians around the y axis
    R = [cos(gama) 0 sin(gama) 0;0 1 0 0;-sin(gama) 0 cos(gama) 0;0 0 0 1];
end

function T = Tx(a)
%% Function to calculate a homogenious transformation matrix R for a translation of a units on the x axis
    T = [eye(3),[a;0;0];[0 0 0 1]];
end

function T = Ty(b)
%% Function to calculate a homogenious transformation matrix R for a translation of b units on the y axis
    T = [eye(3),[0;b;0];[0 0 0 1]];
end

function T = Tz(c)
%% Function to calculate a homogenious transformation matrix R for a translation of c units on the z axis
    T = [eye(3),[0;0;c];[0 0 0 1]];
end