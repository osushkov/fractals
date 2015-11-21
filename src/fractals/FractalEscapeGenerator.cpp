/*
 * FractalEscapeGenerator.cpp
 *
 *  Created on: 19 Nov 2015
 *      Author: osushkov
 */

#include "FractalEscapeGenerator.hpp"
#include <cassert>

double FractalEscapeGenerator::calculatePixelWidth(
    const Vector2 &regionMin, const Vector2 &regionMax, unsigned samplesX) {
  assert(regionMin.x <= regionMax.x && regionMin.y <= regionMax.y);
  return (regionMax.x - regionMin.x) / samplesX;
}

double FractalEscapeGenerator::calculatePixelHeight(
    const Vector2 &regionMin, const Vector2 &regionMax, unsigned samplesY) {
  assert(regionMin.x <= regionMax.x && regionMin.y <= regionMax.y);
  return (regionMax.y - regionMin.y) / samplesY;
}

Vector2 FractalEscapeGenerator::getFirstPixelPos(
    const Vector2 &regionMin, double pWidth, double pHeight) {
  return Vector2(regionMin.x + pWidth/2.0, regionMin.y + pHeight/2.0);
}
