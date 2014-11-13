#include <iostream>
#include <cmath>
#include <cstdlib>
#include <fstream>

const int M = 4;       // Downsample
const int L = 3;       // Upsample
const int Fs = 11025;  // Sample rate
const int N = 17700;   // Number of samples
const int Nf = 177;     // Size of lowpass filter

int main(int argc, char** argv)
{
  double param = atof(argv[1]);
  double h[M*L][Nf/(M*L)+1];                     // filter coef
  std::ifstream input("coef.dat");  // data file
  double read;
  std::ofstream filter_dat("../data/filter.dat");
  // Read in the filter data
  // Setting up as a polyphase filter
  for(int i = 0; i < (Nf/(M*L)+1); ++i)
  {
    for(int j = 0; input >> read && j < M*L; ++j)
    {
      h[j][i] = read;
      filter_dat << j << ": " << read << std::endl;
    }
  }

  // files to write data to
  std::ofstream x_dat("../data/x.dat");
  std::ofstream y_dat("../data/y.dat");

  double f0 = 1.0/param;             // frequency
  double y[(N*L)/M];             // Upsampled + Downsampled Array
  double x[N];                   // input signal
  for(int n = 0; n < N; ++n)
  {
    x[n] = cos(2*M_PI*f0*n);
    x_dat << x[n] << std::endl;
  }
  double y0 = 0;
  double y1 = 0;
  double y2 = 0;
  int index = 0;

  // Loop through every sample in the signal
  for(int i = 0; i < N; i+=M)
  {
    y0 = 0;
    y1 = 0;
    y2 = 0;

    for(int j = 0; j < i && j < Nf/(L*M) + 1; ++j)
    {
      y0 += x[i-j]     * h[2][j];
      y0 += x[(i+1)-j] * h[1][j];
      y0 += x[(i+2)-j] * h[0][j];
      y0 += x[(i+3)-j] * h[3][j];

      y1 += x[i-j]     * h[7][j];
      y1 += x[(i+1)-j] * h[6][j];
      y1 += x[(i+2)-j] * h[5][j];
      y1 += x[(i+3)-j] * h[4][j];

      y2 += x[i-j]     * h[8][j];
      y2 += x[(i+1)-j] * h[11][j];
      y2 += x[(i+2)-j] * h[10][j];
      y2 += x[(i+3)-j] * h[9][j];
    }
    y_dat << y0 << std::endl;
    y_dat << y1 << std::endl;
    y_dat << y2 << std::endl;
    y[index++] = y0;
    y[index++] = y1;
    y[index++] = y2;
  }

  return 0;
}
