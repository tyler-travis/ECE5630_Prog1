x = importdata('data/x.dat');
xu = importdata('data/upsample.dat');
xf = importdata('data/filtered.dat');
y = importdata('data/y.dat');

N = 17700;

Fs = 11025;

% figure(1); plot(x); xlim([0 N/100]);
% figure(2); plot(xu); xlim([0 N*3/100]);
% figure(3); plot(xf); xlim([0 N*3/100]);
% figure(4); plot(y); xlim([0 100]);

X = fft(x);
nx = (1:N)/N;
figure(1); subplot(2,1,1); plot(x); xlim([0 N/100]);
figure(1); subplot(2,1,2); plot(nx, abs(X));

Y = fft(y);
ny = (1:(N*3/4))/(N*3/4);
figure(2); subplot(2,1,1); plot(y); xlim([0 100]);
figure(2); subplot(2,1,2); plot(ny, abs(Y));