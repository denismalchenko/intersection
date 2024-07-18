#ifndef SRC_VECTOR3D_H_
#define SRC_VECTOR3D_H_

#define EPSILON 1e-7

class Vector3D {
 public:
  Vector3D(double x, double y, double z) : X(x), Y(y), Z(z) {}
  Vector3D() : Vector3D(0, 0, 0) {}
  ~Vector3D() = default;
  double getX() const { return X; }
  double getY() const { return Y; }
  double getZ() const { return Z; }
  void setX(const double x) { X = x; }
  void setY(const double y) { Y = y; }
  void setZ(const double z) { Z = z; }
  Vector3D operator+(const Vector3D& other) const {
    return Vector3D(X + other.X, Y + other.Y, Z + other.Z);
  }
  Vector3D operator-(const Vector3D& other) const {
    return Vector3D(X - other.X, Y - other.Y, Z - other.Z);
  }
  Vector3D operator*(double scalar) const {
    return Vector3D(X * scalar, Y * scalar, Z * scalar);
  }

  bool IsZero(const double deviation = EPSILON) const {
    return std::abs(X) <= deviation && std::abs(Y) <= deviation &&
           std::abs(Z) <= deviation;
  }

  bool IsCollinear(const Vector3D& other,
                   const double deviation = EPSILON) const;

  bool IsCollinearNotZero(const Vector3D& other,
                          const double deviation = EPSILON) const;

  bool IsCoDirectional(const Vector3D& other,
                       const double deviation = EPSILON) const;

  bool IsCoDirectionalNotZero(const Vector3D& other,
                              const double deviation = EPSILON) const;

 private:
  double X;
  double Y;
  double Z;
};

Vector3D operator*(double scalar, const Vector3D& other) {
  return other * scalar;
}

#endif  // SRC_VECTOR3D_H_
