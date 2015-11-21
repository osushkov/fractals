/*
 * FractalRenderer.hpp
 *
 *  Created on: 15 Nov 2015
 *      Author: osushkov
 */

#pragma once

#include <memory>
#include <vector>

#include "FractalEscapeGenerator.hpp"
#include "ColorGenerator.hpp"
#include "../util/Color.hpp"
#include "../math/Vector2.hpp"


class FractalRenderer {
public:

  FractalRenderer(
      std::shared_ptr<FractalEscapeGenerator> pointGenerator,
      std::shared_ptr<ColorGenerator> colorGenerator);

  virtual ~FractalRenderer();

  std::vector<Color> renderPixels(
      const Vector2 &regionMin, const Vector2 &regionMax,
      unsigned samplesX, unsigned samplesY) const;

private:
  class FractalRendererImpl;
  std::unique_ptr<FractalRendererImpl> impl;
};
