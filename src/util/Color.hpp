/*
 * Color.h
 *
 *  Created on: 04/12/2013
 *      Author: osushkov
 */

#pragma once

#include <iosfwd>

class Color {
public:

  const double red;
  const double green;
  const double blue;
  const double alpha;

  // Named convenience constructors.
  static Color RED(double intensity);
  static Color GREEN(double intensity);
  static Color BLUE(double intensity);
  static Color WHITE(double intensity);
  static Color BLACK();

  Color(double red, double green, double blue);
  Color(double red, double green, double blue, double alpha);
};

std::ostream& operator<<(std::ostream& stream, const Color& color);
