#include "segment3d.h"

#include "line3d.h"

bool Segment3D::IsPointOnSegment(const Vector3D& point,
                                 const double deviation) const {
  if ((point - start).IsZero(deviation) || (point - end).IsZero(deviation)) {
    return true;
  } else if (Direction().IsZero(deviation)) {
    return false;
  } else {
    return (point - start).IsCoDirectionalNotZero(Direction(), deviation) !=
           (point - end).IsCoDirectionalNotZero(Direction(), deviation);
  }
}

std::pair<Vector3D, bool> Segment3D::Intersect(const Segment3D& other,
                                               const double deviation) const {
  Line3D line1 = Line3D(start, Direction());
  Line3D line2 = Line3D(other.start, other.Direction());
  std::pair<Vector3D, bool> result = line1.Intersect(line2, deviation);
  if (result.second) {
    // Если соотвствующие прямые пересекаются в одной точке, то осталось
    // проверить, что эта точка принадлежит обоим отрезкам
    if (IsPointOnSegment(result.first, deviation) &&
        other.IsPointOnSegment(result.first, deviation)) {
      return std::make_pair(result.first, true);
    } else {
      return std::make_pair(Vector3D(NAN, NAN, NAN), false);
    }
  } else {
    if (std::isnan(result.first.getX())) {
      // Если у нас хотя бы отрезок-точка, который не пересекает прямую
      return std::make_pair(result.first, false);
    } else {
      // либо прямые параллельны или совпадают
      if (line1.IsPointOnLine(other.start, deviation)) {
        // Прямые совпадают. Нужно проверить совпадение концов отрезков
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
          // Концы отрезков не совпадают, нужно проверить лежат ли концы внутри.
          // Достаточно проверить 3 конца.
        } else if (IsPointOnSegment(other.start, deviation) ||
                   IsPointOnSegment(other.end, deviation) ||
                   other.IsPointOnSegment(start, deviation)) {
          return std::make_pair(Vector3D(INFINITY, INFINITY, INFINITY), false);
        } else {
          return std::make_pair(Vector3D(NAN, NAN, NAN), false);
        }
      } else {
        // Прямые параллельны
        return std::make_pair(Vector3D(NAN, NAN, NAN), false);
      }
    }
  }
}

std::pair<Vector3D, bool> Intersect(const Segment3D& segment1,
                                    const Segment3D& segment2,
                                    const double deviation) {
  return segment1.Intersect(segment2, deviation);
}
