/*
 * MandelbrotFractal.hpp
 *
 *  Created on: 14 Nov 2015
 *      Author: sushkov
 */

#include "MandelbrotFractal.hpp"
#include "../math/Vector2.hpp"

#include <memory>

class MandelbrotFractal::MandelbrotFractalImpl {
  static constexpr double ESCAPE_THRESHOLD_2 = 2.0 * 2.0;

public:
  MandelbrotFractalImpl() {}
  virtual ~MandelbrotFractalImpl() {}

  int pointEscapeIterations(const Vector2 &point, unsigned maxIterations) const {
    Vector2 curVal(0.0, 0.0);
    for (unsigned i = 1; i <= maxIterations; i++) {
      curVal = nextIteration(curVal, point);
      if (curVal.length2() >= ESCAPE_THRESHOLD_2) {
        return i;
      }
    }

    return 0;
  }

private:

  Vector2 nextIteration(const Vector2 &z, const Vector2 &c) const {
    Vector2 z_sq = Vector2(z.x*z.x - z.y*z.y, 2.0*z.x*z.y);
    return z_sq + c;
  }

};


MandelbrotFractal::MandelbrotFractal() : impl(new MandelbrotFractalImpl()) {}
MandelbrotFractal::~MandelbrotFractal() = default;

int MandelbrotFractal::pointEscapeIterations(const Vector2 &point, unsigned maxIterations) const {
  return impl->pointEscapeIterations(point, maxIterations);
}
