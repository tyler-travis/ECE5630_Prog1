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
    }
  }

  for(int i = 0; i < M*L; ++i)
  {
    for(int j = 0; j < (Nf/(M*L))+1; ++j)
    {
      filter_dat << "h[" << i << "][" << j << "] = " << h[i][j] << std::endl;
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
      y2 += x[i] * h[8][j]; // time 0
      y2 += (i-1 >= 0)?(x[i-1] * h[9][j]):0;
      y2 += (i-2 >= 0)?(x[i-2] * h[10][j]):0;
      y2 += (i-3 >= 0)?(x[i-3] * h[11][j]):0;

      y1 += (i-1 >= 0)?(x[i-1] * h[4][j]):0;
      y1 += (i-2 >= 0)?(x[i-2] * h[5][j]):0;
      y1 += (i-3 >= 0)?(x[i-3] * h[6][j]):0;
      y1 += (i-4 >= 0)?(x[i-4] * h[7][j]):0;

      y0 += (i-2 >= 0)?(x[i-2] * h[0][j]):0;
      y0 += (i-3 >= 0)?(x[i-3] * h[1][j]):0;
      y0 += (i-4 >= 0)?(x[i-4] * h[2][j]):0;
      y0 += (i-5 >= 0)?(x[i-5] * h[3][j]):0;
    }
    std::cout << "i ==================== " << i << std::endl;
    std::cout << "y0: " << y0 << std::endl;
    std::cout << "y1: " << y1 << std::endl;
    std::cout << "y2: " << y2 << std::endl;
    y[index++] = y0;
    y[index++] = y2;
    y[index++] = y1;
  }
  for(int i = 0; i < N*L/M; ++i)
  {
    y_dat << y[i] << std::endl;
  }
  return 0;
}
