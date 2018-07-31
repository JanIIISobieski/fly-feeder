clc; clear; close all;

s1 = serial('COM4');
s1.BaudRate = 9600;
s1.Terminator = 'LF';

fopen(s1);

try
    i = 1;
    while i < 100
        w = fscanf(s1, '%d');
        display(w)
        i = i + 1;
    end
catch exception
    fclose(s1);
    throw (exception);
end

fclose(s1);