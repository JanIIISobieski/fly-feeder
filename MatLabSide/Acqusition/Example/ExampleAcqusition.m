clear all; close all; daqreset;
imaqreset;
%% Overall, we want to acquire a 6 minute video. During the last three minutes we will
%stimulate with red light to activate ORNs. We have to acquire video and in
%sync stimulate.
% basic parameters
numSecs=360;
%numSecs=30;
numafter=4;
sampleRate=1000;
frameRate=30;
numFrames=numSecs*frameRate;
src.AcquisitionFrameRate = frameRate;
%extshutter=18000; %12000;
%brightness=127; %110;
%gain = 13;

%initialize camera
%vid = videoinput('avtmatlabadaptor64_r2009b', 1, 'F7M3_Mono8_640x512'); %F7M3_YUV422_640x510'); %'F0M5_Mono8_640x480');
vid=videoinput('gentl', 1, 'Mono8');
triggerconfig(vid, 'manual'); %configure trigger type that cameras will expect
vid.FramesPerTrigger=numFrames; %handles.numframes;
vid.LoggingMode = 'disk';
src = getselectedsource(vid);
%src.Brightness = brightness;
%src.Gain = gain;
src.AcquisitionFrameRate = frameRate;
%src.ResultingFrameRate
src.ExposureTime = 32000;
src.AcquisitionFrameRate
fig1=figure(1);
h = image(zeros(vid.VideoResolution));
reset(h)
preview(vid,h);

%define where things will be saved
rootdir = ['F:\Nicholas Data\Behavior\' datestr(date, 'yymmdd'),'Data Not Done'];
mkdir(rootdir);
cd(rootdir);

%update the expNum and trialNum
files=dir('*video.avi');
test=isempty(files);
if test==0; %you have already saved trials in this directory
    prefix=strcat(datestr(date, 'yymmdd'));
    expAccum=[];
    trialAccum=[];
    for i = 1:size(files,1),
        fileName = files(i,1).name;
        tok = regexp(fileName,[prefix '_(\d+)_(\d+)_video.avi'],'tokens');
        exp = tok{1}{1};
        trial = tok{1}{2};
        expAccum = [expAccum str2num(exp)];
        trialAccum = [trialAccum str2num(trial)];
    end;
    lastExp = max(expAccum);
    expNum=lastExp;
    lastTrial = max(trialAccum);
    trialNum=lastTrial+1;
else expNum=1; trialNum=1;
end
trialtag=strcat(datestr(now,'yymmdd'),'_',num2str(expNum),'_',num2str(trialNum));
vidFileName=strcat(trialtag,'_video.avi');
diskLogger= VideoWriter(vidFileName, 'Grayscale AVI');
vid.DiskLogger=diskLogger;
lightONFileName=strcat('lightON','_',trialtag,'.mat');

%initialize DAQ
numdatapts = sampleRate*numSecs;
s = daq.createSession('ni');
s.Rate=sampleRate;
s.addAnalogOutputChannel('Dev1','ao0','voltage'); %drives the red light
s.addAnalogOutputChannel('Dev1','ao1','voltage'); %drives the red light
s.addAnalogInputChannel( 'Dev1','ai0','voltage'); %receives the same command which drives the red light
delay=zeros(((numdatapts/2)-1),1);
after=zeros(numafter,1);
t=(1:1:(numdatapts/2));
odoron(t)=5;
output1=vertcat(delay(1:end-1),odoron',after,0);
%output1=(output1)';
outputData(:,1)=output1;
outputData(:,2)=output1;

s.queueOutputData(outputData);
s.NotifyWhenDataAvailableExceeds =(sampleRate*numSecs);
display('Data acquisition starting');
tic

%start the listener in the background
dataListener = s.addlistener('DataAvailable', @saveData_optogenetics);
s.startBackground(); %start background is code to start data acquisition
display('starting cameras');
start(vid);
trigger(vid);
s.wait();
display(['scans acquired equals ', num2str(s.ScansAcquired)]);
%start the camera


if s.ScansAcquired>0;
    
    global LEDGlobal  timeGlobal triggerGlobal;
    display(size(LEDGlobal));
    save(lightONFileName,'LEDGlobal');
end