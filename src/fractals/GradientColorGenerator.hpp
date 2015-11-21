/*
 * BinaryColorGenerator.hpp
 *
 *  Created on: 15 Nov 2015
 *      Author: osushkov
 */

#pragma once

#include <memory>
#include "ColorGenerator.hpp"

class GradientColorGenerator : public ColorGenerator {
public:

  GradientColorGenerator(const Color &fromColor, const Color &toColor, unsigned cycleLength);
  virtual ~GradientColorGenerator();

  Color colorPoint(const Vector2 &position, int escapeIterations) const override;

private:
  class GradientColorGeneratorImpl;
  std::unique_ptr<GradientColorGeneratorImpl> impl;
};
