#ifndef SRC_LINE3D_H_
#define SRC_LINE3D_H_

#include <utility>

#include "vector3d.h"

class Line3D {
 public:
  Line3D(const Vector3D& point, const Vector3D& direction)
      : point_(point), direction_(direction) {}
  Line3D() : Line3D(Vector3D(0, 0, 0), Vector3D(1, 0, 0)) {}
  ~Line3D() = default;
  Vector3D getPoint() const { return point_; }
  Vector3D getDirection() const { return direction_; }
  void setPoint(const Vector3D& point) { point_ = point; }
  void setDirection(const Vector3D& direction) { direction_ = direction; }
  // check if line is parallel or equal.
  bool IsParallel(const Line3D& other, const double deviation = EPSILON) const {
    return direction_.IsCollinear(other.getDirection(), deviation);
  }
  // check if point is on line
  bool IsPointOnLine(const Vector3D& point,
                     const double deviation = EPSILON) const;
  // Find intersection point of two lines.
  std::pair<Vector3D, bool> Intersect(const Line3D& other,
                                      const double deviation = EPSILON) const;

 private:
  Vector3D point_;
  Vector3D direction_;
};

#endif  // SRC_LINE3D_H_
