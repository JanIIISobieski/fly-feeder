function getFrameTime(~, event)
    global frame_time
    global frame_num

    frame_time(frame_num, :) = event.Data.AbsTime;
    frame_num = frame_num + 1;
end