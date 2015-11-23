/*
 * MultiThreadedEscapeGenerator.hpp
 *
 *  Created on: 18 Nov 2015
 *      Author: osushkov
 */

#pragma once

#include <memory>

#include "FractalEscapeGenerator.hpp"
#include "Fractal.hpp"

class MultiThreadedEscapeGenerator : public FractalEscapeGenerator {
public:

  MultiThreadedEscapeGenerator(std::shared_ptr<Fractal> fractal);
  virtual ~MultiThreadedEscapeGenerator();

  std::vector<FractalPoint> sampleRegion(
        const Vector2 &regionMin, const Vector2 &regionMax,
        unsigned samplesX, unsigned samplesY) const override;

  void setMaxIterations(unsigned maxIterations) override;

private:
  class MultiThreadedEscapeGeneratorImpl;
  std::unique_ptr<MultiThreadedEscapeGeneratorImpl> impl;
};
