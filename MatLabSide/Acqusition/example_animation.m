Z = peaks;
surf(Z); 
axis tight manual 
set(gca,'nextplot','replacechildren');

v = VideoWriter('peaks.avi');
open(v);

fps = 20;

tini = datetime('now', 'Format', 'yyyy-MM-dd HH:mm:ss.SSS');

for k = 1:20 
   surf(sin(2*pi*k/20)*Z,Z)
   frame = getframe(gcf);
   writeVideo(v, frame);
   time = datetime('now', 'Format', 'yyyy-MM-dd HH:mm:ss.SSS') - tini;
   time.Format = 'hh:mm:ss.SSS';
   text(10, 10, -5, sprintf('%s', time), 'HorizontalAlignment','left','FontSize',8);
   pause(1/fps)
   xlabel('x')
   ylabel('y')
   zlabel('z')
end

close(v);