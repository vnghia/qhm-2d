#ifndef _POINT_H_
#define _POINT_H_

#include "coord.h"

class Point {
 public:
  Point(float x, float y, float z, float r, float m);
  Point(float x, float y, float z);
  Point(float x, float y, float r, float m);
  Point(float x, float y);
  Point();

  bool IsCollide(const Point& p) const;

  void Move(const Coord& v, float dt);
  void Move(float x, float y, float z, float dt);

  const float& r() const;
  const float& m() const;

  Coord coord;

 private:
  float r_;
  float m_;
};

#endif
