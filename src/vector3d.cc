#include "vector3d.h"

#define SAME_SIGN(x, y) (x < 0 ? y < 0 : (x == 0 ? y == 0 : y > 0))

bool Vector3D::IsCollinearNotZero(const Vector3D& other,
                                  const double deviation) const {
  return std::abs(X * other.Y - Y * other.X) <= deviation &&
         std::abs(X * other.Z - Z * other.X) <= deviation;
}

bool Vector3D::IsCollinear(const Vector3D& other,
                           const double deviation) const {
  return IsZero(deviation) || other.IsZero(deviation) ||
         IsCollinearNotZero(other, deviation);
}

bool Vector3D::IsCoDirectionalNotZero(const Vector3D& other,
                                      const double deviation) const {
  if (IsCollinearNotZero(other, deviation)) {
    return SAME_SIGN(X, other.X) && SAME_SIGN(Y, other.Y) &&
           SAME_SIGN(Z, other.Z);
  } else {
    return false;
  }
}

bool Vector3D::IsCoDirectional(const Vector3D& other,
                               const double deviation) const {
  return IsZero(deviation) || other.IsZero(deviation) ||
         IsCoDirectionalNotZero(other, deviation);
}

Vector3D operator*(double scalar, const Vector3D& other) {
  return other * scalar;
}