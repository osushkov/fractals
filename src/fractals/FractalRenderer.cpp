/*
 * FractalRenderer.cpp
 *
 *  Created on: 15 Nov 2015
 *      Author: osushkov
 */

#include "FractalRenderer.hpp"

#include <cassert>
#include <iostream>


class FractalRenderer::FractalRendererImpl {

  std::shared_ptr<FractalEscapeGenerator> pointGenerator;
  std::shared_ptr<ColorGenerator> colorGenerator;

public:

  FractalRendererImpl(
      std::shared_ptr<FractalEscapeGenerator> pointGenerator,
      std::shared_ptr<ColorGenerator> colorGenerator) :
        pointGenerator(pointGenerator), colorGenerator(colorGenerator) {}

  virtual ~FractalRendererImpl() = default;

  std::vector<Color> renderPixels(
      const Vector2 &regionMin, const Vector2 &regionMax,
      unsigned samplesX, unsigned samplesY) const {

    assert(regionMin.x <= regionMax.x);
    assert(regionMin.y <= regionMax.y);

    std::vector<FractalPoint> points =
        pointGenerator->sampleRegion(regionMin, regionMax, samplesX, samplesY);

    std::vector<Color> result;
    for (auto p : points) {
      result.push_back(colorGenerator->colorPoint(p.position, p.escapeIterations));
    }
    return result;
  }
};


FractalRenderer::FractalRenderer(
    std::shared_ptr<FractalEscapeGenerator> pointGenerator,
    std::shared_ptr<ColorGenerator> colorGenerator) :
        impl(new FractalRendererImpl(pointGenerator, colorGenerator)) {}

FractalRenderer::~FractalRenderer() = default;

std::vector<Color> FractalRenderer::renderPixels(
    const Vector2 &regionMin, const Vector2 &regionMax,
    unsigned samplesX, unsigned samplesY) const {
  return impl->renderPixels(regionMin, regionMax, samplesX, samplesY);
}
