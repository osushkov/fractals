/*
 * SingleThreadedEscapeGenerator.hpp
 *
 *  Created on: 18 Nov 2015
 *      Author: osushkov
 */

#pragma once

#include <memory>

#include "FractalEscapeGenerator.hpp"
#include "Fractal.hpp"

class SingleThreadedEscapeGenerator : public FractalEscapeGenerator {
public:
  
  SingleThreadedEscapeGenerator(std::shared_ptr<Fractal> fractal);
  virtual ~SingleThreadedEscapeGenerator();

  std::vector<FractalPoint> sampleRegion(
        const Vector2 &regionMin, const Vector2 &regionMax,
        unsigned samplesX, unsigned samplesY) const override;

private:
  class SingleThreadedEscapeGeneratorImpl;
  std::unique_ptr<SingleThreadedEscapeGeneratorImpl> impl;
};
