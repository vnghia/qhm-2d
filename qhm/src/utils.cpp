#include "utils.h"

#include <cmath>

#define PRECISION 1e6

double rsin(double a) {
  return std::round(std::sin(a) * PRECISION) / PRECISION;
}

double rcos(double a) {
  return std::round(std::cos(a) * PRECISION) / PRECISION;
}
