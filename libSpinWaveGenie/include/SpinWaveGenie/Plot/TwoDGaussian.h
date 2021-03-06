//
//  TwoDGaussian.h
//  spin_wave_genie
//
//  Created by Hahn, Steven E. on 6/23/14.
//
//

#ifndef __spin_wave_genie__TwoDGaussian__
#define __spin_wave_genie__TwoDGaussian__

#include <iostream>
#include "SpinWaveGenie/Memory.h"
#include "SpinWaveGenie/Plot/OneDimensionalShapes.h"

namespace SpinWaveGenie
{

class TwoDGaussian : public OneDimensionalShapes
{
public:
  // void setFWHM(double InFWHM){};
  void setResolution(double aIn, double bIn, double cIn);
  void setU(double uIn);
  void setTolerance(double InTolerance) override;
  double getMinimumEnergy() override;
  double getMaximumEnergy() override;
  double getFunction(double frequency, double energy) override;
  std::unique_ptr<OneDimensionalShapes> clone() override;
  ~TwoDGaussian(){};

private:
  double getExponentialFactor();
  double FWHM, Tolerance;
  double a, b, c;
  double u;
};
}

#endif /* defined(__spin_wave_genie__TwoDGaussian__) */
