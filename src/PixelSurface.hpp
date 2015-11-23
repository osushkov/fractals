/*
 * PixelSurface.hpp
 *
 *  Created on: 11 Nov 2015
 *      Author: sushkov
 */

#pragma once

#include <memory>
#include <vector>

#include <SDL2/SDL.h>
#include "util/Color.hpp"


class PixelSurface {
public:

  PixelSurface(SDL_Renderer *renderer, unsigned width, unsigned height);
  virtual ~PixelSurface();

  unsigned getWidth(void) const;
  unsigned getHeight(void) const;

  void renderPixels(const std::vector<Color> &pixels);

private:
  class PixelSurfaceImpl;
  std::unique_ptr<PixelSurfaceImpl> impl;
};
