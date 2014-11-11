x = importdata('cosine.dat');
xu = importdata('upsample.dat');
xf = importdata('filtered.dat');
y = importdata('downsample.dat');

N = 17700;

figure(1); plot(x); xlim([0 N/100]);
figure(2); plot(xu); xlim([0 N*3/100]);
figure(3); plot(xf); xlim([0 N*3/100]);
figure(4); plot(y); xlim([0 100]);