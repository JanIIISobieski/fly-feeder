%% Clear workspace
imaqreset; clear; clc; close all;

%% Define global variables
global frame_time
global frame_num

%% Initialize video input
vid = videoinput('gentl', 1, 'Mono8');
src = getselectedsource(vid);

%% Video parameters
tot_time = 10;
fps = 30;

%% Set up preview axis
figure(1); clf;
axis square

vid.ROIPosition = [77 0 1001 1008];
src.AcquisitionFrameRate = fps;
src.ExposureTime = 4000;

triggerconfig(vid, 'manual')

vid.LoggingMode = 'disk';
vid.DiskLogger = VideoWriter('test2.mj2', 'Archival');
vid.FramesPerTrigger = round(tot_time*src.AcquisitionFrameRateLimit);
vid.FramesAcquiredFcnCount = 1;
vid.FramesAcquiredFcn = {'getFrameTime'};

frame_time = zeros(vid.FramesPerTrigger, 6);
frame_num = 1;

start(vid);
trigger(vid);

% while (vid.FramesAcquired ~= vid.DiskLoggerFrameCount) 
%     pause(.1)
% end
% fprintf('Finished acquiring frames\n')
% 
% while (frame_num <= vid.DiskLoggerFrameCount) 
%     pause(.1)
% end
% fprintf('Finished writing to Disk\n')

