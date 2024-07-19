#ifndef SRC_SEGMENT3D_H_
#define SRC_SEGMENT3D_H_

#include <utility>

#include "vector3d.h"

class Segment3D {
 public:
  Segment3D(const Vector3D& start, const Vector3D& end)
      : start(start), end(end) {}
  Segment3D() : Segment3D(Vector3D(0, 0, 0), Vector3D(1, 0, 0)) {}
  ~Segment3D() = default;
  Vector3D getStart() const { return start; }
  Vector3D getEnd() const { return end; }
  void setStart(const Vector3D& start) { this->start = start; }
  void setEnd(const Vector3D& end) { this->end = end; }
  // get segment direction vector
  Vector3D Direction() const { return end - start; }
  // check if point is on segment
  bool IsPointOnSegment(const Vector3D& point,
                        const double deviation = EPSILON) const;
  // Find point of intersection between two segments
  std::pair<Vector3D, bool> Intersect(const Segment3D& other,
                                      const double deviation = EPSILON) const;

 private:
  Vector3D start;
  Vector3D end;
};

std::pair<Vector3D, bool> Intersect(const Segment3D& segment1,
                                    const Segment3D& segment2,
                                    const double deviation = EPSILON);

#endif  // SRC_SEGMENT3D_H_
