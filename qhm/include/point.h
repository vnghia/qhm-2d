#ifndef _POINT_H_
#define _POINT_H_

class Point {
 public:
  Point(float x, float y, float r, float m);

  bool IsCollide(const Point &p) const;

  // Only for ploting purpose !
  float r(int scale) const;

  float x;
  float y;

 private:
  float r_;
  float m_;
};

#endif
