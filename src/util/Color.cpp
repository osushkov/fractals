/*
 * Color.cpp
 *
 *  Created on: 10/12/2013
 *      Author: osushkov
 */

#include "Color.hpp"
#include <ostream>
#include <cassert>

Color Color::RED(double intensity) {
  return Color(intensity, 0.0, 0.0);
}

Color Color::GREEN(double intensity) {
  return Color(0.0, intensity, 0.0);
}

Color Color::BLUE(double intensity) {
  return Color(0.0, 0.0, intensity);
}

Color Color::WHITE(double intensity) {
  return Color(intensity, intensity, intensity);
}

Color Color::BLACK() {
  return Color(0.0, 0.0, 0.0);
}

Color::Color(double red, double green, double blue) :
    Color(red, green, blue, 1.0) {}

Color::Color(double red, double green, double blue, double alpha) :
    red(red), green(green), blue(blue), alpha(alpha) {
  assert(red >= 0.0);
  assert(green >= 0.0);
  assert(blue >= 0.0);
  assert(alpha >= 0.0);
}

std::ostream& operator<<(std::ostream& stream, const Color& color) {
  stream << "Color("
      << color.red << ","
      << color.green << ","
      << color.blue << ","
      << color.alpha
      << ")";
  return stream;
}
