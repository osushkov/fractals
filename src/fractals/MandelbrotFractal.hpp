/*
 * MandelbrotFractal.hpp
 *
 *  Created on: 14 Nov 2015
 *      Author: sushkov
 */

#pragma once

#include "Fractal.hpp"
#include <memory>

class MandelbrotFractal : public Fractal {
public:
  MandelbrotFractal(unsigned maxIterations);
  virtual ~MandelbrotFractal();

  int pointEscapeIterations(const Vector2 &point) const override;
  void setMaxIterations(unsigned maxIterations) override;

private:
  class MandelbrotFractalImpl;
  std::unique_ptr<MandelbrotFractalImpl> impl;
};
