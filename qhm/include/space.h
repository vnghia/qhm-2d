#ifndef _SPACE_H_
#define _SPACE_H_

#include <vector>

#include "coord.h"
#include "point.h"

class Space {
 public:
  Space(float xmin, float xmax, float ymin, float ymax, float zmin, float zmax);
  Space(float xmin, float xmax, float ymin, float ymax);
  Space();

  void AddPoint(const Point& p = Point(), const Coord& v = Coord());
  void AddPoint(float x, float y, float z, float r, float m, float vx, float vy,
                float vz);

  void Update(float dt);

  const Point& operator[](std::size_t i) const;
  const std::size_t Size() const;

 private:
  void VCollideX(std::size_t i);
  void VCollideY(std::size_t i);
  void VCollideZ(std::size_t i);

  void VCollide(std::size_t i, std::size_t j);

  float xmin_;
  float xmax_;
  float ymin_;
  float ymax_;
  float zmin_;
  float zmax_;

  std::vector<Point> ps_;
  std::vector<Coord> vs_;
#ifdef QHM_ONE_COLLISION
  std::vector<std::vector<bool>> col_;
#endif
};

#endif
