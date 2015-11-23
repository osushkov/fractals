
#pragma once

struct CuVector2 {
  double x, y;
};

inline static CuVector2 cuVector2(double x, double y) {
  CuVector2 r;
  r.x = x;
  r.y = y;
  return r;
}
