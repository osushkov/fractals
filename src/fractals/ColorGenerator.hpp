/*
 * FractalColorGenerator.hpp
 *
 *  Created on: 14 Nov 2015
 *      Author: sushkov
 */

#pragma once

#include "../util/Color.hpp"
#include "../math/Vector2.hpp"

#include <vector>

class ColorGenerator {
public:

  virtual ~ColorGenerator() {}

  virtual Color colorPoint(const Vector2 &position, int escapeIterations) const = 0;
};
