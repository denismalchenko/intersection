#include "segment3d.h"

#include <cmath>

#include "line3d.h"

bool Segment3D::IsPointOnSegment(const Vector3D& point,
                                 const double deviation = EPSILON) const {
  if ((point - start).IsZero(deviation) || (point - end).IsZero(deviation)) {
    return true;
  } else if (Direction().IsZero(deviation)) {
    return false;
  } else {
    return (point - start).IsCollinear(Direction(), deviation) !=
           (point - end).IsCollinear(Direction(), deviation);
  }
}

std::pair<Vector3D, bool> Segment3D::Intersect(
    const Segment3D& other, const double deviation = EPSILON) const {
  Line3D line1 = Line3D(start, Direction());
  Line3D line2 = Line3D(other.start, other.Direction());
  std::pair<Vector3D, bool> result = line1.Intersect(line2, deviation);
  if (result.second) {
    if (IsPointOnSegment(result.first, deviation) &&
        other.IsPointOnSegment(result.first, deviation)) {
      return std::make_pair(result.first, true);
    } else {
      return std::make_pair(Vector3D(NAN, NAN, NAN), false);
    }
  } else {
    if (std::isnan(result.first.getX())) {
      return std::make_pair(result.first, false);
    } else {
      if (line1.IsPointOnLine(other.start, deviation)) {
        if ((other.start - start).IsZero(deviation)) {
          if (IsPointOnSegment(other.end, deviation) ||
              other.IsPointOnSegment(end, deviation)) {
            return std::make_pair(Vector3D(INFINITY, INFINITY, INFINITY),
                                  false);
          } else {
            return std::make_pair(start, true);
          }
        } else if ((other.end - start).IsZero(deviation)) {
          if (IsPointOnSegment(other.start, deviation) ||
              other.IsPointOnSegment(end, deviation)) {
            return std::make_pair(Vector3D(INFINITY, INFINITY, INFINITY),
                                  false);
          } else {
            return std::make_pair(start, true);
          }
        } else if ((other.start - end).IsZero(deviation)) {
          if (IsPointOnSegment(other.end, deviation) ||
              other.IsPointOnSegment(start, deviation)) {
            return std::make_pair(Vector3D(INFINITY, INFINITY, INFINITY),
                                  false);
          } else {
            return std::make_pair(end, true);
          }
        } else if ((other.end - end).IsZero(deviation)) {
          if (IsPointOnSegment(other.start, deviation) ||
              other.IsPointOnSegment(start, deviation)) {
            return std::make_pair(Vector3D(INFINITY, INFINITY, INFINITY),
                                  false);
          } else {
            return std::make_pair(end, true);
          }
        } else if (IsPointOnSegment(other.start, deviation) ||
                   IsPointOnSegment(other.end, deviation) ||
                   other.IsPointOnSegment(start, deviation)) {
          return std::make_pair(Vector3D(INFINITY, INFINITY, INFINITY), false);
        } else {
          return std::make_pair(Vector3D(NAN, NAN, NAN), false);
        }
      } else {
        return std::make_pair(Vector3D(NAN, NAN, NAN), false);
      }
    }
  }
}
