/*
 * SingleThreadedEscapeGenerator.cpp
 *
 *  Created on: 18 Nov 2015
 *      Author: osushkov
 */

#include "SingleThreadedEscapeGenerator.hpp"
#include <cassert>


class SingleThreadedEscapeGenerator::SingleThreadedEscapeGeneratorImpl {

  std::shared_ptr<Fractal> fractal;

public:
  SingleThreadedEscapeGeneratorImpl(std::shared_ptr<Fractal> fractal) :
    fractal(fractal) {}

  virtual ~SingleThreadedEscapeGeneratorImpl() = default;

  std::vector<FractalPoint> sampleRegion(
      const Vector2 &regionMin, const Vector2 &regionMax,
      unsigned samplesX, unsigned samplesY) const {
    assert(regionMin.x <= regionMax.x);
    assert(regionMin.y <= regionMax.y);

    double pWidth = FractalEscapeGenerator::calculatePixelWidth(regionMin, regionMax, samplesX);
    double pHeight = FractalEscapeGenerator::calculatePixelHeight(regionMin, regionMax, samplesY);
    Vector2 minPixel = FractalEscapeGenerator::getFirstPixelPos(regionMin, pWidth, pHeight);

    std::vector<FractalPoint> points;
    for (unsigned y = 0; y < samplesY; y++) {
      for (unsigned x = 0; x < samplesX; x++) {
        Vector2 pixelPos(minPixel + Vector2(x*pWidth, y*pHeight));
        int fractalIters = fractal->pointEscapeIterations(pixelPos);
        points.push_back(FractalPoint(pixelPos, fractalIters));
      }
    }

    return points;
  }
};


SingleThreadedEscapeGenerator::SingleThreadedEscapeGenerator(std::shared_ptr<Fractal> fractal) :
    impl(new SingleThreadedEscapeGeneratorImpl(fractal)) {}

SingleThreadedEscapeGenerator::~SingleThreadedEscapeGenerator() = default;

std::vector<FractalPoint> SingleThreadedEscapeGenerator::sampleRegion(
    const Vector2 &regionMin, const Vector2 &regionMax,
    unsigned samplesX, unsigned samplesY) const {

  return impl->sampleRegion(regionMin, regionMax, samplesX, samplesY);
}
