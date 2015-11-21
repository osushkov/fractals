/*
 * BinaryColorGenerator.cpp
 *
 *  Created on: 15 Nov 2015
 *      Author: osushkov
 */

#include "GradientColorGenerator.hpp"
#include <iostream>
#include <cassert>


class GradientColorGenerator::GradientColorGeneratorImpl {
  const Color fromColor;
  const Color toColor;

  const unsigned cycleLength = 64;

public:

  GradientColorGeneratorImpl(const Color &fromColor, const Color &toColor, unsigned cycleLength) :
      fromColor(fromColor), toColor(toColor), cycleLength(cycleLength) {
    assert(cycleLength > 1);
  }

  virtual ~GradientColorGeneratorImpl() = default;

  Color colorPoint(const Vector2 &position, int escapeIterations) const {
    double cycleProgress = (escapeIterations % cycleLength) / (double) cycleLength;
    int cycleNum = escapeIterations / cycleLength;
    if (cycleNum%2 == 1) {
        cycleProgress = 1.0 - cycleProgress;
    }

    double from = cycleProgress;
    double to = (1.0 - from);
    return Color(
        fromColor.red*from + toColor.red*to,
        fromColor.green*from + toColor.green*to,
        fromColor.blue*from + toColor.blue*to,
        fromColor.alpha*from + toColor.alpha*to);
  }
};


GradientColorGenerator::GradientColorGenerator(
    const Color &fromColor, const Color &toColor, unsigned cycleLength) :
        impl(new GradientColorGeneratorImpl(fromColor, toColor, cycleLength)) {}

GradientColorGenerator::~GradientColorGenerator() = default;

Color GradientColorGenerator::colorPoint(const Vector2 &position, int escapeIterations) const {
  return impl->colorPoint(position, escapeIterations);
}
