clc; clear; close all;


slCharacterEncoding('US-ASCII')

i = 1;
arduino = serial('COM4');
arduino.BaudRate = 9600;
arduino.Terminator = 'CR/LF';


fopen(arduino);

try
    while 1
        if i == 1
            w = fgetl(arduino);
            display(w)
            i = 2;
        else
            fprintf(arduino, '%c', 's');
            i = 1;
        end
        
    end
    
catch exception
    fclose(arduino);
    throw (exception);
end

fclose(arduino);