/*
 * SingleThreadedEscapeGenerator.hpp
 *
 *  Created on: 18 Nov 2015
 *      Author: osushkov
 */

#pragma once

#include <memory>
#include "FractalEscapeGenerator.hpp"

class CudaMandelbrotGenerator : public FractalEscapeGenerator {
public:

  CudaMandelbrotGenerator();
  virtual ~CudaMandelbrotGenerator();

  std::vector<FractalPoint> sampleRegion(
        const Vector2 &regionMin, const Vector2 &regionMax,
        unsigned samplesX, unsigned samplesY) const override;

  void setMaxIterations(unsigned maxIterations) override;

private:
  class CudaMandelbrotGeneratorImpl;
  std::unique_ptr<CudaMandelbrotGeneratorImpl> impl;
};
