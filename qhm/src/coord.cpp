#include "coord.h"

#include <cmath>
#include <iostream>

Coord::Coord(float x, float y, float z) : x(x), y(y), z(z) {}
Coord::Coord(float x, float y) : Coord(x, y, 0) {}
Coord::Coord() : Coord(0, 0) {}

void Coord::Add(const Coord& c) { return Add(c.x, c.y, c.z); }
void Coord::Add(float x, float y, float z) {
  this->x += x;
  this->y += y;
  this->z += z;
}

float Coord::Dot(const Coord& c) const { return Dot(c.x, c.y, c.z); }
float Coord::Dot(float x, float y, float z) const {
  return Dot(this->x, this->y, this->z, x, y, z);
}
float Coord::Dot(float x1, float y1, float z1, float x2, float y2, float z2) {
  return x1 * x2 + y1 * y2 + z1 * z2;
}

float Coord::Norm() const { return std::sqrt(Dot(*this)); }
float Coord::Norm(float x, float y, float z) {
  return std::sqrt(Dot(x, y, z, x, y, z));
}

float Coord::Distance(const Coord& c) const { return Distance(c.x, c.y, c.z); }
float Coord::Distance(float x, float y, float z) const {
  return Distance(this->x, this->y, this->z, x, y, z);
}
float Coord::Distance(float x1, float y1, float z1, float x2, float y2,
                      float z2) {
  return Norm(x1 - x2, y1 - y2, z1 - z2);
}

float Coord::Angle(const Coord& c) const { return Angle(c.x, c.y, c.z); }
float Coord::Angle(float x, float y, float z) const {
  return Angle(this->x, this->y, this->z, x, y, z);
}
float Coord::Angle(float x1, float y1, float z1, float x2, float y2, float z2) {
  // If one of these coordinates is zero, we switch to calculate the angle from
  // the x-axis.
  if (x1 == 0 && y1 == 0 && z1 == 0) {
    x1 = 1;
  }
  if (x2 == 0 && y2 == 0 && z2 == 0) {
    x2 = 1;
  }
  return acos(Dot(x1, y1, z1, x2, y2, z2) /
              (Norm(x1, y1, z1) * Norm(x2, y2, z2)));
}

float Coord::AngleToX() const { return AngleToX(x, y, z); }
float Coord::AngleToX(float x, float y, float z) {
  float a = Angle(x, y, z, 1, 0, 0);
  if (x > 0) {
    a = -a;
  }
  return a;
}
