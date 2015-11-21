/*
 * MandelbrotFractal.hpp
 *
 *  Created on: 14 Nov 2015
 *      Author: sushkov
 */

#pragma once

#include "Fractal.hpp"
#include "../math/Vector2.hpp"
#include <memory>

class JuliaSetFractal : public Fractal {
public:
  JuliaSetFractal(const Vector2 &c, unsigned maxIterations);
  virtual ~JuliaSetFractal();

  int pointEscapeIterations(const Vector2 &point) const override;
  void setMaxIterations(unsigned maxIterations) override;

private:
  class JuliaSetFractalImpl;
  std::unique_ptr<JuliaSetFractalImpl> impl;
};
