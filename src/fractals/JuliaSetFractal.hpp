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
  JuliaSetFractal(const Vector2 &c);
  virtual ~JuliaSetFractal();

  int pointEscapeIterations(const Vector2 &point, unsigned maxIterations) const override;

private:
  class JuliaSetFractalImpl;
  std::unique_ptr<JuliaSetFractalImpl> impl;
};
