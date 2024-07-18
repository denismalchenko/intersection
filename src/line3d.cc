#include "line3d.h"

#include <cmath>

bool Line3D::IsPointOnLine(const Vector3D& point,
                           const double deviation = EPSILON) const {
  if (direction_.IsZero(deviation)) {
    return (point - point_).IsZero(deviation);
  } else {
    return (point - point_).IsCollinear(direction_, deviation);
  }
}

std::pair<Vector3D, bool> Line3D::Intersect(
    const Line3D& other, const double deviation = EPSILON) const {
  if (IsParallel(other, deviation)) {
    if (direction_.IsZero(deviation)) {
      if (other.direction_.IsZero(deviation)) {
        if ((point_ - other.point_).IsZero(deviation)) {
          return std::make_pair(point_, true);
        } else {
          return std::make_pair(Vector3D(NAN, NAN, NAN), false);
        }
      } else {
        if ((point_ - other.point_).IsCollinear(other.direction_, deviation)) {
          return std::make_pair(point_, true);
        } else {
          return std::make_pair(Vector3D(NAN, NAN, NAN), false);
        }
      }
    } else if (other.direction_.IsZero(deviation)) {
      if ((point_ - other.point_).IsCollinear(direction_, deviation)) {
        return std::make_pair(other.point_, true);
      } else {
        return std::make_pair(Vector3D(NAN, NAN, NAN), false);
      }
    } else {
      return std::make_pair(Vector3D(INFINITY, INFINITY, INFINITY), false);
    }
  }
  Vector3D points_vector = other.getPoint() - point_;
  double t = (other.getDirection().getX() * points_vector.getY() -
              other.getDirection().getY() * points_vector.getX()) /
             (other.getDirection().getX() * direction_.getY() -
              other.getDirection().getY() * direction_.getX());
  return std::make_pair(point_ + direction_ * t, true);
}
