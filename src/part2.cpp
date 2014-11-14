#include <iostream>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

const int M = 4;       // Downsample
const int L = 3;       // Upsample
const int Fs = 11025;  // Sample rate
const int N = 55200;   // Number of samples
const int Nf = 552;     // Size of lowpass filter

int main(int argc, char** argv)
{
  double param = atof(argv[1]);
  //double h[Nf];                     // filter
  double hs[M*L][Nf/(M*L)];       // subfilters
  std::ifstream input("coef_new.dat");  // data file
  double read;
  std::ofstream h0_dat("../data/h0.dat");
  std::ofstream h1_dat("../data/h1.dat");
  std::ofstream h2_dat("../data/h2.dat");
  std::ofstream h3_dat("../data/h3.dat");
  std::ofstream h4_dat("../data/h4.dat");
  std::ofstream h5_dat("../data/h5.dat");
  std::ofstream h6_dat("../data/h6.dat");
  std::ofstream h7_dat("../data/h7.dat");
  std::ofstream h8_dat("../data/h8.dat");
  std::ofstream h9_dat("../data/h9.dat");
  std::ofstream h10_dat("../data/h10.dat");
  std::ofstream h11_dat("../data/h11.dat");

  // Read in the filter data
  // Setting up as a polyphase filter
  int n = 0;
  int m = 0;

  while(!input.eof())
  {
    input >> read;
    hs[n][m] = read;
    n++;
    if(n == M*L)
    {
      n = 0;
      m++;
    }
  }
  for(int i = 0; i < Nf/(M*L); ++i)
  {
    h0_dat << hs[0][i] << std::endl;
  }
  for(int i = 0; i < Nf/(M*L); ++i)
  {
    h1_dat << hs[1][i] << std::endl;
  }
  for(int i = 0; i < Nf/(M*L); ++i)
  {
    h2_dat << hs[2][i] << std::endl;
  }
  for(int i = 0; i < Nf/(M*L); ++i)
  {
    h3_dat << hs[3][i] << std::endl;
  }
  for(int i = 0; i < Nf/(M*L); ++i)
  {
    h4_dat << hs[4][i] << std::endl;
  }
  for(int i = 0; i < Nf/(M*L); ++i)
  {
    h5_dat << hs[5][i] << std::endl;
  }
  for(int i = 0; i < Nf/(M*L); ++i)
  {
    h6_dat << hs[6][i] << std::endl;
  }
  for(int i = 0; i < Nf/(M*L); ++i)
  {
    h7_dat << hs[7][i] << std::endl;
  }
  for(int i = 0; i < Nf/(M*L); ++i)
  {
    h8_dat << hs[8][i] << std::endl;
  }
  for(int i = 0; i < Nf/(M*L); ++i)
  {
    h9_dat << hs[9][i] << std::endl;
  }
  for(int i = 0; i < Nf/(M*L); ++i)
  {
    h10_dat << hs[10][i] << std::endl;
  }
  for(int i = 0; i < Nf/(M*L); ++i)
  {
    h11_dat << hs[11][i] << std::endl;
  }
  
  // files to write data to
  std::ofstream x_dat("../data/x.dat");
  std::ofstream y_dat("../data/y.dat");

  double f0 = 1.0/param;         // frequency
  double y[(N*L)/M];             // Upsampled + Downsampled Array
  double x0[N];                // input signal
  double x1[N];                // input signal
  double x2[N];                // input signal
  double x3[N];                // input signal
  double x4[N];                // input signal
  double x5[N];                // input signal
  double ds0[N/M];
  double ds1[N/M];
  double ds2[N/M];
  double ds3[N/M];
  double ds4[N/M];
  double ds5[N/M];
  for(int n = 0; n < N; ++n)
  {
    x0[n] = cos(2*M_PI*f0*n);
    x_dat << x0[n] << std::endl;
  }
  memcpy(x1 + 1, x0, sizeof(x1));
  memcpy(x2 + 2, x0, sizeof(x2));
  memcpy(x3 + 3, x0, sizeof(x3));
  memcpy(x4 + 4, x0, sizeof(x4));
  memcpy(x5 + 5, x0, sizeof(x5));

  double y0 = 0;
  double y1 = 0;
  double y2 = 0;
  unsigned int o_index = 0;


  // Loop through every sample in the signal
  for(int i = 0; i < N; i+=M)
  {
    ds0[i/M] = x0[i];
    ds1[i/M] = x1[i];
    ds2[i/M] = x2[i];
    ds3[i/M] = x3[i];
    ds4[i/M] = x4[i];
    ds5[i/M] = x5[i];
  }

  for(int i = 0; i < N/M; ++i)
  {
    y0 = 0;
    y1 = 0;
    y2 = 0;

    for(int j = 0; j < Nf/(L*M)-1; ++j)
    {
      y0 += ds2[i-j]*hs[0][j];
      y0 += ds3[i-j]*hs[3][j];
      y0 += ds4[i-j]*hs[6][j];
      y0 += ds5[i-j]*hs[9][j];

      y1 += ds1[i-j]*hs[1][j];
      y1 += ds2[i-j]*hs[4][j];
      y1 += ds3[i-j]*hs[7][j];
      y1 += ds4[i-j]*hs[10][j];

      y2 += ds0[i-j]*hs[2][j];
      y2 += ds1[i-j]*hs[5][j];
      y2 += ds2[i-j]*hs[8][j];
      y2 += ds3[i-j]*hs[11][j];
    }

    y_dat << y0 << std::endl;
    y_dat << y1 << std::endl;
    y_dat << y2 << std::endl;
    y[o_index++] = y0;
    y[o_index++] = y1;
    y[o_index++] = y2;
  }
  return 0;
}
