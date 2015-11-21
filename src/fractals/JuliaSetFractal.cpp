/*
 * MandelbrotFractal.hpp
 *
 *  Created on: 14 Nov 2015
 *      Author: sushkov
 */

#include "JuliaSetFractal.hpp"
#include "../math/Vector2.hpp"

#include <memory>

class JuliaSetFractal::JuliaSetFractalImpl {
  static constexpr double ESCAPE_THRESHOLD_2 = 2.0 * 2.0;

  const Vector2 c;
  unsigned maxIterations;

public:
  JuliaSetFractalImpl(const Vector2 &c, unsigned maxIterations) :
      c(c), maxIterations(maxIterations) {}

  virtual ~JuliaSetFractalImpl() {}

  int pointEscapeIterations(const Vector2 &point) const {
    Vector2 curVal(point);
    for (unsigned i = 1; i <= maxIterations; i++) {
      curVal = nextIteration(curVal);
      if (curVal.length2() >= ESCAPE_THRESHOLD_2) {
        return i;
      }
    }

    return 0;
  }

  void setMaxIterations(unsigned maxIterations) {
    this->maxIterations = maxIterations;
  }

private:

  Vector2 nextIteration(const Vector2 &z) const {
    Vector2 z_sq = Vector2(z.x*z.x - z.y*z.y, 2.0*z.x*z.y);
    return z_sq + c;
  }
};


JuliaSetFractal::JuliaSetFractal(const Vector2 &c, unsigned maxIterations) :
    impl(new JuliaSetFractalImpl(c, maxIterations)) {}

JuliaSetFractal::~JuliaSetFractal() = default;

int JuliaSetFractal::pointEscapeIterations(const Vector2 &point) const {
  return impl->pointEscapeIterations(point);
}

void JuliaSetFractal::setMaxIterations(unsigned maxIterations) {
  impl->setMaxIterations(maxIterations);
}
