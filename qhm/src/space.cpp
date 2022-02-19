#include "space.h"

#include <cmath>
#include <iostream>

constexpr double PI = 3.14159265358979323846;

Space::Space(float xll, float xul, float yll, float yul)
    : xll_(xll), xul_(xul), yll_(yll), yul_(yul) {}

void Space::AddPoint(const Point& p, float xv, float yv) {
  points.push_back(p);
  xvs_.push_back(xv);
  yvs_.push_back(yv);
}

void Space::Update(float dt) {
  if (points[0].IsCollide(points[1])) {
    xvs_[0] = xvs_[1] * cos(PI / 6);
    yvs_[0] = xvs_[1] * cos(PI / 6);
    xvs_[1] = 0.0000005 * cos(PI / 3);
    yvs_[1] = -0.0000005 * cos(PI / 3);
  }

  for (int i = 0; i < points.size(); ++i) {
    if (IsCollideXLower(i)) {
      xvs_[i] = -xvs_[i];
    }
    if (IsCollideXUpper(i)) {
      xvs_[i] = -xvs_[i];
    }
    if (IsCollideYLower(i)) {
      yvs_[i] = -yvs_[i];
    }
    if (IsCollideYUpper(i)) {
      yvs_[i] = -yvs_[i];
    }
  }

  for (int i = 0; i < points.size(); ++i) {
    points[i].x += dt * xvs_[i];
    points[i].y += dt * yvs_[i];
  }
}

bool Space::IsCollideXLower(int index) {
  return points[index].x <= xll_ + points[index].r(1);
}

bool Space::IsCollideXUpper(int index) {
  return points[index].x >= xul_ - points[index].r(1);
}

bool Space::IsCollideYLower(int index) {
  return points[index].y <= yll_ + points[index].r(1);
}

bool Space::IsCollideYUpper(int index) {
  return points[index].y >= yul_ - points[index].r(1);
}
