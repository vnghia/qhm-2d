#ifndef _SPACE_H_
#define _SPACE_H_

#include <vector>

#include "point.h"

class Space {
 public:
  Space(float xll = 0, float xul = 2, float yll = 0, float yul = 2);

  void AddPoint(const Point& p, float xv, float yv);
  void Update(float dt);

  std::vector<Point> points;

 private:
  bool IsCollideXLower(int index);
  bool IsCollideXUpper(int index);
  bool IsCollideYLower(int index);
  bool IsCollideYUpper(int index);

  float xll_ = 0;
  float xul_ = 2;
  float yll_ = 0;
  float yul_ = 2;

  std::vector<float> xvs_;
  std::vector<float> yvs_;
};

#endif
