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
  std::ofstream cosine_dat("../data/cosine.dat");
  std::ofstream filtered_dat("../data/filtered.dat");
  std::ofstream upsample_dat("../data/upsample.dat");
  std::ofstream downsample_dat("../data/downsample.dat");

  double f0 = 1.0/4;            // frequency
  float upSampled[N*L];         // Upsamled Array
  float y[(N*L)/M];             // Upsampled + Downsampled Array
  float filtered[N*L+Nf];       // filtered signal
  float x[N];                   // input signal
  for(int n = 0; n < N; ++n)
  {
    x[n] = cos(2*M_PI*f0*n);
    cosine_dat << x[n] << std::endl;
  }

  // Upsample input signal
  for(int i = 0; i < N; ++i)
  {
    upSampled[i*L] = x[i];
    upSampled[i*L+1] = 0;
    upSampled[i*L+2] = 0;
  }
  for(int i = 0; i < N*L; ++i)
  {
    upsample_dat << upSampled[i] << std::endl;
  }

  // Lowpass filter signal
  /*for(int i = 0; i < L*N; ++i)
  {
    filtered[i] = 0;
    for(int j = 0; j < Nf; ++j)
    {
      filtered[i] += upSampled[i-j] * h[j];
    }
    filtered_dat << filtered[i] << std::endl;
  }*/

  // Downsample signal
  for(int i = 0; i < 3*N; i += 4)
  {
    y[i/4] = filtered[i];
    downsample_dat << y[i/4] << std::endl;
  }
  return 0;
}
