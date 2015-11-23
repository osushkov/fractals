/*
 * CommonMath.cpp
 *
 *  Created on: 06/12/2013
 *      Author: osushkov
 */

#include "CommonMath.hpp"

#include <cstdlib>
#include <cmath>

#include "Vector2.hpp"

double CommonMath::randInterval(double s, double e) {
  return s + (e - s) * (rand() / (double) RAND_MAX);
}

double CommonMath::gaussianNoise(double mean, double sd) {
  // Taken from GSL Library Gaussian random distribution.
  double x, y, r2;

  do{
    // choose x,y in uniform square (-1,-1) to (+1,+1)
    x = -1 + 2 * randInterval(0.0, 1.0);
    y = -1 + 2 * randInterval(0.0, 1.0);

    // see if it is in the unit circle
    r2 = x * x + y * y;
  } while (r2 > 1.0 || r2 == 0);

  // Box-Muller transform
  return mean + sd * y * sqrt (-2.0 * log (r2) / r2);
}

Vector2 CommonMath::generateRandomPointInCircle(const Vector2 &centre, double radius) {
  while (true) {
    Vector2 result(randInterval(-radius, radius), randInterval(-radius, radius));
    if (result.length2() <= radius * radius) {
      return result + centre;
    }
  }

  return Vector2(); // Just to satisfy the warning.
}

double CommonMath::angleDiff(double angle0, double angle1) {
  return std::min(fabs(angle0 - angle1), fabs(fabs(angle0 - angle1) - 2.0*M_PI));
}

double CommonMath::clip(double var, double min, double max){
  if (var < min){
    return min;
  }
  else if (var > max){
    return max;
  }
  else {
    return var;
  }
}

bool CommonMath::pointInBox(const Vector2 &point, const Vector2 &boxTopLeft,
    const Vector2 &boxSize) {

  return point.x >= boxTopLeft.x && point.x <= (boxTopLeft.x + boxSize.x) &&
       point.y >= boxTopLeft.y && point.y <= (boxTopLeft.y + boxSize.y);
}
