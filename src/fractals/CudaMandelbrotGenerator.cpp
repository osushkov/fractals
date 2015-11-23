/*
 * SingleThreadedEscapeGenerator.cpp
 *
 *  Created on: 18 Nov 2015
 *      Author: osushkov
 */

#include "CudaMandelbrotGenerator.hpp"
#include "../cuda/MandelbrotKernel.hpp"

#include <cassert>


class CudaMandelbrotGenerator::CudaMandelbrotGeneratorImpl {

  unsigned maxIterations = 256;

public:
  CudaMandelbrotGeneratorImpl() = default;
  virtual ~CudaMandelbrotGeneratorImpl() = default;

  std::vector<FractalPoint> sampleRegion(
      const Vector2 &regionMin, const Vector2 &regionMax,
      unsigned samplesX, unsigned samplesY) const {
    assert(regionMin.x <= regionMax.x);
    assert(regionMin.y <= regionMax.y);

    double pWidth = FractalEscapeGenerator::calculatePixelWidth(regionMin, regionMax, samplesX);
    double pHeight = FractalEscapeGenerator::calculatePixelHeight(regionMin, regionMax, samplesY);
    Vector2 minPixel = FractalEscapeGenerator::getFirstPixelPos(regionMin, pWidth, pHeight);

    std::vector<Vector2> samplePoints;
    for (unsigned y = 0; y < samplesY; y++) {
      for (unsigned x = 0; x < samplesX; x++) {
        samplePoints.push_back(Vector2(minPixel + Vector2(x*pWidth, y*pHeight)));
      }
    }

    std::vector<int> escapeIters = MandelbrotKernel::calculateIterationsPerPixel(
        samplesX, samplesY, pWidth, pHeight, cuVector2(minPixel.x, minPixel.y), maxIterations);

    assert(escapeIters.size() == samplePoints.size());
    std::vector<FractalPoint> resultPoints;
    for (unsigned i = 0; i < escapeIters.size(); i++) {
      resultPoints.push_back(FractalPoint(samplePoints[i], escapeIters[i]));
    }

    return resultPoints;
  }

  void setMaxIterations(unsigned maxIterations) {
    assert(maxIterations > 0);
    this->maxIterations = maxIterations;
  }
};


CudaMandelbrotGenerator::CudaMandelbrotGenerator() :
    impl(new CudaMandelbrotGeneratorImpl()) {}

CudaMandelbrotGenerator::~CudaMandelbrotGenerator() = default;

std::vector<FractalPoint> CudaMandelbrotGenerator::sampleRegion(
    const Vector2 &regionMin, const Vector2 &regionMax,
    unsigned samplesX, unsigned samplesY) const {

  return impl->sampleRegion(regionMin, regionMax, samplesX, samplesY);
}

void CudaMandelbrotGenerator::setMaxIterations(unsigned maxIterations) {
  impl->setMaxIterations(maxIterations);
}
