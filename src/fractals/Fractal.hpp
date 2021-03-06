/*
 * Fractal.hpp
 *
 *  Created on: 14 Nov 2015
 *      Author: sushkov
 */

#pragma once

class Vector2;

class Fractal {
public:

  virtual ~Fractal() {}

  // Returns 0 if point never escapes.
  virtual int pointEscapeIterations(const Vector2 &point, unsigned maxIterations) const = 0;

};
