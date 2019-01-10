clc; clear; close all;

slCharacterEncoding('US-ASCII')

arduino = serial('COM4');
arduino.BaudRate = 9600;
arduino.Terminator = 'CR/LF';

global action
global numTrials
global flyIndex
global flyTrials

global flyPassedSignal
global startSignal
global experimentEndSignal

flyIndex = NaN;
flyTrials = [0 0 0 0 0 0 0 0];
action = 'background';
numTrials = 3;

startSignal = 'b';
flyPassedSignal = 'f';
experimentEndSignal = 'e';

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
                recievedNum = fgetl(arduino);
                
                if ~isempty(recievedNum) && ~strcmp(recievedNum, flyPassedSignal)
                    if ~isnan(recievedNum) 
                        flyIndex = str2double(recievedNum);
                        action = 'fly pass';
                    end
                end
                
            case 'fly pass'
                recievedChar = fgetl(arduino);
                
                if strcmp(recievedChar, flyPassedSignal)
                   action = 'trial';
                   fprintf('Successful passing of fly\n')
                end
                
            case 'trial'
                fprintf('Running experiment\n');
                pause(3);
                flyTrials(flyIndex) = flyTrials(flyIndex) + 1;
                disp(flyTrials)
                
            case 'fly removal'
                fprintf(arduino, '%c', experimentEndSignal);
                if all(flyTrials >= numTrials)
                    action = 'end';
                end
            case 'end'
                fprintf('Fin')
                break;
        end
    end
    
catch exception
    fclose(arduino);
    throw (exception);
    
end

fclose(arduino);

function readString = getFromArduino(port)
    if (port.BytesAvailable > 0)
       readString = fgetl(port);
    else
        readString = -1;
    end
end