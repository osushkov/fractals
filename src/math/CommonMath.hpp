/*
 * CommonMath.h
 *
 *  Created on: 06/12/2013
 *      Author: osushkov
 */

#pragma once

#include <vector>

struct Vector2;
template<class T> class Maybe;

namespace CommonMath {

  static const double EPSILON = 0.0001;

  /**
   * Generate a random number in the given range using a uniform distribution.
   */
  double randInterval(double s, double e);

  /**
   * Generate a random variable using a Gaussian distribution with the given mean and standard
   * deviation.
   */
  double gaussianNoise(double mean, double sd);

  /**
   * Generate a random point in a circle.
   */
  Vector2 generateRandomPointInCircle(const Vector2 &centre, double radius);

  /**
   * The shortest angle between given two angles, in radians.
   */
  double angleDiff(double angle0, double angle1);

  double clip(double var, double min, double max);

  /**
   * Checks whether a point is inside an axis-aligned box.
   */
  bool pointInBox(const Vector2 &point, const Vector2 &boxTopLeft,
      const Vector2 &boxSize);

}
