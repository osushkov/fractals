/*
 * BinaryColorGenerator.hpp
 *
 *  Created on: 15 Nov 2015
 *      Author: osushkov
 */

#pragma once

#include <memory>
#include "ColorGenerator.hpp"

class BinaryColorGenerator : public ColorGenerator {
public:

  BinaryColorGenerator(const Color &inSetColor, const Color &outsideSetColor);
  virtual ~BinaryColorGenerator();

  Color colorPoint(const Vector2 &position, int escapeIterations) const override;

private:
  class BinaryColorGeneratorImpl;
  std::unique_ptr<BinaryColorGeneratorImpl> impl;
};
