clc; clear; close all;

slCharacterEncoding('US-ASCII')

arduino = serial('COM4');
arduino.BaudRate = 9600;
arduino.Terminator = 'CR/LF';


fopen(arduino);

try
    while 1
        disp(arduino.BytesAvailable)
        w = fgetl(arduino);
        display(w)
    end
    
catch exception
    fclose(arduino);
    throw (exception);
end

fclose(arduino);