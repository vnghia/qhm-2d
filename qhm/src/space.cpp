#include "space.h"

#include <cmath>
#include <iostream>

#include "utils.h"

Space::Space(float xmin, float xmax, float ymin, float ymax, float zmin,
             float zmax)
    : xmin_(xmin),
      xmax_(xmax),
      ymin_(ymin),
      ymax_(ymax),
      zmin_(zmin),
      zmax_(zmax) {}

Space::Space(float xmin, float xmax, float ymin, float ymax)
    : Space(xmin, xmax, ymin, ymax, 0, 0) {}

Space::Space() : Space(0, 1, 0, 1) {}

void Space::AddPoint(const Point& p, const Coord& v) {
  AddPoint(p.coord.x, p.coord.y, p.coord.z, p.r(), p.m(), v.x, v.y, v.z);
}

void Space::AddPoint(float x, float y, float z, float r, float m, float vx,
                     float vy, float vz) {
  ps_.emplace_back(x, y, z, r, m);
  vs_.emplace_back(vx, vy, vz);
#ifdef QHM_ONE_COLLISION
  if (ps_.size() >= 2) {
    col_.push_back({});
    for (int i = 0; i < col_.size(); ++i) {
      col_[i].push_back(false);
    }
  }
#endif
}

void Space::VCollideX(std::size_t i) {
  const Point& p = ps_[i];
  if (xmin_ >= p.coord.x - p.r() && vs_[i].x < 0) {
    vs_[i].x = -vs_[i].x;
  } else if (xmax_ <= p.coord.x + p.r() && vs_[i].x > 0) {
    vs_[i].x = -vs_[i].x;
  }
}

void Space::VCollideY(std::size_t i) {
  const Point& p = ps_[i];
  if (ymin_ >= p.coord.y - p.r() && vs_[i].y < 0) {
    vs_[i].y = -vs_[i].y;
  } else if (ymax_ <= p.coord.y + p.r() && vs_[i].y > 0) {
    vs_[i].y = -vs_[i].y;
  }
}

void Space::VCollideZ(std::size_t i) {
  const Point& p = ps_[i];
  if (zmin_ >= p.coord.z - p.r() && vs_[i].z < 0) {
    vs_[i].z = -vs_[i].z;
  } else if (zmax_ <= p.coord.z + p.r() && vs_[i].z > 0) {
    vs_[i].z = -vs_[i].z;
  }
}

void Space::VCollide(std::size_t i, std::size_t j) {
  static int number_collision = 0;

  const Point& p1 = ps_[i];
  const Point& p2 = ps_[j];
  if (p1.IsCollide(p2)) {
#ifdef QHM_ONE_COLLISION
    if (!col_[i][j - i - 1]) {
#endif
      Coord& v1 = vs_[i];
      Coord& v2 = vs_[j];

      float n = std::pow(p1.coord.Distance(p2.coord), 2);
      float total_mass = p1.m() + p2.m();
      float c1 = -(2 * p2.m() / total_mass) *
                 Coord::Dot(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z,
                            p1.coord.x - p2.coord.x, p1.coord.y - p2.coord.y,
                            p1.coord.z - p2.coord.z) /
                 n;
      float c2 = -(2 * p1.m() / total_mass) *
                 Coord::Dot(v2.x - v1.x, v2.y - v1.y, v2.z - v1.z,
                            p2.coord.x - p1.coord.x, p2.coord.y - p1.coord.y,
                            p2.coord.z - p1.coord.z) /
                 n;

      v1.x += c1 * (p1.coord.x - p2.coord.x);
      v1.y += c1 * (p1.coord.y - p2.coord.y);
      v2.x += c2 * (p2.coord.x - p1.coord.x);
      v2.y += c2 * (p2.coord.y - p1.coord.y);

#ifdef QHM_ONE_COLLISION
      col_[i][j - i - 1] = true;
    }
  } else {
    if (col_[i][j - i - 1]) {
      col_[i][j - i - 1] = false;
    }
#endif
  }
}

void Space::Update(float dt) {
  for (int i = 0; i < ps_.size(); ++i) {
    VCollideX(i);
    VCollideY(i);
    VCollideZ(i);
    for (int j = i + 1; j < ps_.size(); ++j) {
      VCollide(i, j);
    }
  }

  for (int i = 0; i < ps_.size(); ++i) {
    ps_[i].Move(vs_[i], dt);
  }
}

const Point& Space::operator[](std::size_t i) const { return ps_[i]; }

const std::size_t Space::Size() const { return ps_.size(); }
