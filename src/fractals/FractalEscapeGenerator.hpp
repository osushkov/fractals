/*
 * FractalEscapeGenerator.hpp
 *
 *  Created on: 18 Nov 2015
 *      Author: osushkov
 */

#pragma once

#include <vector>
#include "../math/Vector2.hpp"

struct FractalPoint {
  const Vector2 position;
  const int escapeIterations;

  FractalPoint(const Vector2 &position, int escapeIterations) :
    position(position), escapeIterations(escapeIterations) {}
};

class FractalEscapeGenerator {
public:

  virtual ~FractalEscapeGenerator() {}

  virtual std::vector<FractalPoint> sampleRegion(
        const Vector2 &regionMin, const Vector2 &regionMax,
        unsigned samplesX, unsigned samplesY) const = 0;

  virtual void setMaxIterations(unsigned maxIterations) = 0;

  static double calculatePixelWidth(const Vector2 &regionMin, const Vector2 &regionMax, unsigned samplesX);
  static double calculatePixelHeight(const Vector2 &regionMin, const Vector2 &regionMax, unsigned samplesY);
  static Vector2 getFirstPixelPos(const Vector2 &regionMin, double pWidth, double pHeight);
};
