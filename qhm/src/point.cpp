#include "point.h"

#include <cmath>

Point::Point(float x, float y, float r, float m) : x(x), y(y), r_(r), m_(m) {}

bool Point::IsCollide(const Point& p) const {
  float d = std::sqrt(std::pow(x - p.x, 2) + std::pow(y - p.y, 2));
  return d <= r_ + p.r_;
}

float Point::r(int scale) const { return r_ * scale; }
