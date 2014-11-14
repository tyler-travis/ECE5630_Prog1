x = importdata('data/x.dat');
xu = importdata('data/upsample.dat');
xf = importdata('data/filtered.dat');
y = importdata('data/y.dat');

N = 60632;

Fs = 11025;

% figure(1); plot(x); xlim([0 N/100]);
% figure(2); plot(xu); xlim([0 N*3/100]);
% figure(3); plot(xf); xlim([0 N*3/100]);
% figure(4); plot(y); xlim([0 100]);

X = fft(x);
nx = (1:N)/N;
figure(1); plot(nx, 20*log10(abs(X)));

Y = fft(y);
ny = (1:(N*3/4))/(N*3/4);
figure(2); plot(ny, 20*log10(abs(Y)));