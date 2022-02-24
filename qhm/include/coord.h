#ifndef _COORD_H_
#define _COORD_H_

class Coord {
 public:
  Coord(float x, float y, float z);
  Coord(float x, float y);
  Coord();

  void Add(const Coord& c);
  void Add(float x, float y, float z);

  float Dot(const Coord& c) const;
  float Dot(float x, float y, float z) const;
  static float Dot(float x1, float y1, float z1, float x2, float y2, float z2);

  float Norm() const;
  static float Norm(float x, float y, float z);

  float Distance(const Coord& c) const;
  float Distance(float x, float y, float z) const;
  static float Distance(float x1, float y1, float z1, float x2, float y2,
                        float z2);

  float Angle(const Coord& c) const;
  float Angle(float x, float y, float z) const;
  static float Angle(float x1, float y1, float z1, float x2, float y2,
                     float z2);

  float AngleToX() const;
  static float AngleToX(float x, float y, float z);

  float x;
  float y;
  float z;
};

#endif
