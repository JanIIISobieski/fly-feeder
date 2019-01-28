clc; clear; close all;

slCharacterEncoding('US-ASCII')

%arduino = serial('COM4'); %on windows machine, COM(digit)
arduino = serial('/dev/ttyACM0'); %on ubuntu system, ttyACM(digit)
arduino.BaudRate = 9600;
arduino.Terminator = 'CR/LF';

global action
global numTrials
global flyIndex
global flyTrials

global flyPassedSignal
global startSignal
global experimentEndSignal
global completionSignal

flyIndex = NaN;
flyTrials = [0 0 0 0 0 0 0 0];
action = 'background';
numTrials = 3;

startSignal = 'b';
flyPassedSignal = 'f';
experimentEndSignal = 'e';
completionSignal = 'c';

fopen(arduino);
pause(5);

try
    while 1
        switch action
            case 'background'
                fprintf('Getting camera frames\n');
                pause(1);
                fprintf('Taking median\n');
                pause(1);
                fprintf('Complete, ready for more\n');
                action = 'start';
                
            case 'start'
                fprintf(arduino, '%c', startSignal);
                fprintf('Start Signal sent to Arduino\n');
                action = 'fly index';
            
            case 'fly index'                
                recievedNum = getFromArduino(arduino);
                
                if recievedNum ~= -1
                    if ~isnan(recievedNum) 
                        flyIndex = str2double(recievedNum);
                        action = 'fly pass';
                    end
                end
                
            case 'fly pass'
                recievedChar = getFromArduino(arduino);
                
                if strcmp(recievedChar, flyPassedSignal)
                   action = 'trial';
                   fprintf('Successful passing of fly\n')
                end
                
            case 'trial'
                fprintf('Running experiment\n');
                pause(3);
                flyTrials(flyIndex + 1) = flyTrials(flyIndex + 1) + 1; %Matlab indexing starts at 1, not 0 like C++
                disp(flyTrials)
                action = 'fly removal';
                
            case 'fly removal'
                fprintf(arduino, '%c', experimentEndSignal);
                if all(flyTrials >= numTrials)
                    action = 'end';
                else
                    action = 'start';
                end
                
            case 'end'
                
                fprintf('Experiment Complete\n')
                break;
        end
    end
    
catch exception
    
    fclose(arduino);
    throw(exception);
end

fclose(arduino);

function readString = getFromArduino(port)
    if (port.BytesAvailable > 0)
       readString = fgetl(port);
    else
        readString = -1;
    end
end