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
  double coef[Nf];                  // filter coef
  std::ifstream input("coef.dat");  // data file
  double read;
  std::ofstream filter_dat("../filter.dat");
  // Read in the filter data
  for(int i = 0; input >> read && i < Nf; ++i)
  {
    coef[i] = read;
    filter_dat << read << std::endl;
  }
  std::ofstream cosine_dat("../cosine.dat");
  std::ofstream filtered_dat("../filtered.dat");
  std::ofstream upsample_dat("../upsample.dat");
  std::ofstream downsample_dat("../downsample.dat");

  double f0 = 1.0/8;            // frequency
  float upSampled[N*L];         // Upsamled Array
  float downSampled[(N*L)/M];   // Upsampled + Downsampled Array
  float filtered[N*L+Nf];       // filtered signal
  float signal[N];              // input signal
  for(int n = 0; n < N; ++n)
  {
    signal[n] = cos(2*M_PI*f0*n);
    cosine_dat << signal[n] << std::endl;
  }

  // Upsample input signal
  for(int i = 0; i < N; ++i)
  {
    upSampled[i*L] = signal[i];
    upSampled[i*L+1] = 0;
    upSampled[i*L+2] = 0;
  }
  for(int i = 0; i < N*L; ++i)
  {
    upsample_dat << upSampled[i] << std::endl;
  }

  // Lowpass filter signal
  for(int i = 0; i < L*N; ++i)
  {
    filtered[i] = 0;
    for(int j = 0; j < Nf; ++j)
    {
      filtered[i] += upSampled[i-j] * coef[j];
    }
    filtered_dat << filtered[i] << std::endl;
  }

  // Downsample signal
  for(int i = 0; i < 3*N; i += 4)
  {
    downSampled[i/4] = filtered[i];
    downsample_dat << downSampled[i/4] << std::endl;
  }
  return 0;
}
