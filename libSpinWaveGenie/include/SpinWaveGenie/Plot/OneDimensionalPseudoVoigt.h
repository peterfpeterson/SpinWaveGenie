//
//  OneDimensionalPseudoVoigt.h
//  spin_wave_genie
//
//  Created by Hahn, Steven E. on 2/6/14.
//
//

#ifndef __OneDimensionalPseudoVoigt__
#define __OneDimensionalPseudoVoigt__

#include <iostream>
#include "SpinWaveGenie/Memory.h"
#include "SpinWaveGenie/Plot/OneDimensionalShapes.h"
#include "SpinWaveGenie/Plot/OneDimensionalLorentzian.h"
#include "SpinWaveGenie/Plot/OneDimensionalGaussian.h"

namespace SpinWaveGenie
{

class OneDimensionalPseudoVoigt : public OneDimensionalShapes
{
public:
  OneDimensionalPseudoVoigt();
  OneDimensionalPseudoVoigt(const OneDimensionalPseudoVoigt &other)
      : eta(other.eta), tolerance(other.tolerance), Lorentzian(other.Lorentzian->clone()),
        Gaussian(other.Gaussian->clone()){};
  void setEta(double InEta);
  void setFWHM(double InFWHM);
  void setTolerance(double InTolerance) override;
  double getMinimumEnergy() override;
  double getMaximumEnergy() override;
  double getFunction(double frequency, double energy) override;
  std::unique_ptr<OneDimensionalShapes> clone() override;
  ~OneDimensionalPseudoVoigt(){};

private:
  double eta, tolerance;
  std::unique_ptr<OneDimensionalShapes> Lorentzian, Gaussian;
};
}
#endif /* defined(__OneDimensionalPseudoVoigt__) */
