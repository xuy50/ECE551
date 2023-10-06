#include "circle.hpp"

#include <cmath>

void Circle::move(double dx, double dy) {
  this->center.move(dx, dy);
}

double Circle::intersectionArea(const Circle & otherCircle) {
  double d = this->center.distanceFrom(otherCircle.center);
  if (d >= (this->radius + otherCircle.radius)) {
    return 0;
  }
  double lRadius;
  double sRadius;
  if (this->radius >= otherCircle.radius) {
    lRadius = this->radius;
    sRadius = otherCircle.radius;
  }
  else {
    lRadius = otherCircle.radius;
    sRadius = this->radius;
  }
  if (lRadius - sRadius >= d) {
    return M_PI * std::pow(sRadius, 2.0);
  }
  else {
    double a1 =
        std::acos((sRadius * sRadius + d * d - lRadius * lRadius) / (2 * sRadius * d));
    double a2 =
        std::acos((lRadius * lRadius + d * d - sRadius * sRadius) / (2 * lRadius * d));
    return a1 * sRadius * sRadius + a2 * lRadius * lRadius - sRadius * d * std::sin(a1);
  }
}
