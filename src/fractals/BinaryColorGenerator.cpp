/*
 * BinaryColorGenerator.cpp
 *
 *  Created on: 15 Nov 2015
 *      Author: osushkov
 */

#include "BinaryColorGenerator.hpp"

class BinaryColorGenerator::BinaryColorGeneratorImpl {
  const Color inSetColor;
  const Color outsideSetColor;

public:

  BinaryColorGeneratorImpl(const Color &inSetColor, const Color &outsideSetColor) :
      inSetColor(inSetColor), outsideSetColor(outsideSetColor) {}

  virtual ~BinaryColorGeneratorImpl() = default;

  Color colorPoint(const Vector2 &position, int escapeIterations) const {
    return escapeIterations == 0 ? inSetColor : outsideSetColor;
  }
};


BinaryColorGenerator::BinaryColorGenerator(const Color &inSetColor, const Color &outsideSetColor) :
    impl(new BinaryColorGeneratorImpl(inSetColor, outsideSetColor)) {}

BinaryColorGenerator::~BinaryColorGenerator() = default;

Color BinaryColorGenerator::colorPoint(const Vector2 &position, int escapeIterations) const {
  return impl->colorPoint(position, escapeIterations);
}
