#include "point.h"

#include <cmath>

Point::Point(float x, float y, float z, float r, float m)
    : coord(Coord(x, y, z)), r_(r), m_(m) {}
Point::Point(float x, float y, float z) : Point(x, y, z, 1, 1) {}
Point::Point(float x, float y, float r, float m) : Point(x, y, 0, r, m) {}
Point::Point(float x, float y) : Point(x, y, 0) {}
Point::Point() : Point(0, 0) {}

bool Point::IsCollide(const Point& p) const {
  return coord.Distance(p.coord) <= r_ + p.r_;
}

void Point::Move(const Coord& v, float dt) { Move(v.x, v.y, v.z, dt); }
void Point::Move(float x, float y, float z, float dt) {
  coord.x += x * dt;
  coord.y += y * dt;
  coord.z += z * dt;
}

const float& Point::r() const { return r_; }
const float& Point::m() const { return m_; }
