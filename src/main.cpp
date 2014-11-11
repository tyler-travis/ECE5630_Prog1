#include <iostream>
#include <cmath>
#include <cstdlib>
#include <fstream>

const unsigned int M = 4;       // Downsample
const unsigned int L = 3;       // Upsample
const unsigned int Fs = 11025;  // Sample rate
const unsigned int N = 17700;   // Number of samples
const unsigned int Nf = 177;     // Size of lowpass filter

int main(int argc, char** argv)
{
  double coef[Nf];                  // filter coef
  std::ifstream input("coef.dat");  // data file
  double read;
  // Read in the filter data
  for(int i = 0; input >> read && i < Nf; ++i)
  {
    coef[i] = read;
    //std::cout << read << std::endl;
  }

  double f0 = 1.0/16;           // frequency
  float upSampled[N*L];         // Upsamled Array
  float downSampled[(N*L)/M];   // Upsampled + Downsampled Array
  float filtered[N*L+Nf];       // filtered signal
  float signal[N];              // input signal
  for(int n = 0; n < N; ++n)
  {
    signal[n] = cos(2*M_PI*f0*n);
  }

  // Upsample input signal
  for(int i = 0; i < N; ++i)
  {
    upSampled[i*L] = signal[i];
    upSampled[i*L+1] = 0;
    upSampled[i*L+2] = 0;
  }

  // Lowpass filter signal
  
  int j = 0;
  for(int i = 0; i < L*N; ++i)
  {
    int n = 0;
    float acc = 0;
    int m = j;
    for(; n < Nf; ++n)
    {
      acc += coef[n] * upSampled[m];
      m = (m+1) % Nf;
    }
    filtered[i] = acc;
    j = (j>0)?(j-1):(Nf-1);
    //std::cout << acc << std::endl;
  }

  // Downsample signal
  for(int i = 0; i < 3*N; i += 4)
  {
    downSampled[i/4] = filtered[i];
    std::cout << downSampled[i/4] << std::endl;
  }
  /*for(int n = 0; n < N; ++n)
  {
    std::cout << signal[n] << std::endl;
  }*/
  return 0;
}
