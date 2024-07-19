#include <gtest/gtest.h>

#include <cmath>

#include "../src/line3d.h"

TEST(Line3DTest, IsParallelTrue) {
  Line3D a = Line3D(Vector3D(0, 0, 0), Vector3D(1, 2, 3));
  Line3D b = Line3D(Vector3D(2, 4, 6), Vector3D(1.5, 3, 4.5));
  Line3D c = Line3D(Vector3D(3, 2, 1), Vector3D(-3, -6, -9));
  Line3D zero = Line3D(Vector3D(-1.25, 1.25, 0), Vector3D(0, 0, 0));
  EXPECT_TRUE(a.IsParallel(b));
  EXPECT_TRUE(b.IsParallel(a));
  EXPECT_TRUE(a.IsParallel(c));
  EXPECT_TRUE(c.IsParallel(a));
  EXPECT_TRUE(b.IsParallel(c));
  EXPECT_TRUE(c.IsParallel(b));
  EXPECT_TRUE(zero.IsParallel(a));
  EXPECT_TRUE(a.IsParallel(zero));
  EXPECT_TRUE(zero.IsParallel(b));
  EXPECT_TRUE(b.IsParallel(zero));
  EXPECT_TRUE(zero.IsParallel(c));
  EXPECT_TRUE(c.IsParallel(zero));
  EXPECT_TRUE(a.IsParallel(a));
  EXPECT_TRUE(b.IsParallel(b));
  EXPECT_TRUE(c.IsParallel(c));
  EXPECT_TRUE(zero.IsParallel(zero));
}

TEST(Line3DTest, IsParallelFalse) {
  Line3D a = Line3D(Vector3D(0, 0, 0), Vector3D(1, 2, 3));
  Line3D b = Line3D(Vector3D(2, 4, 6), Vector3D(4, 5, 6));
  Line3D c = Line3D(Vector3D(3, 2, 1), Vector3D(-1, 2, 3));
  EXPECT_FALSE(a.IsParallel(b));
  EXPECT_FALSE(b.IsParallel(a));
  EXPECT_FALSE(a.IsParallel(c));
  EXPECT_FALSE(c.IsParallel(a));
  EXPECT_FALSE(b.IsParallel(c));
  EXPECT_FALSE(c.IsParallel(b));
}

TEST(Line3DTest, IsPointOnLineTrue) {
  Line3D a = Line3D(Vector3D(0, 0, 0), Vector3D(1, 2, 3));
  Line3D zero = Line3D(Vector3D(2, 4, 6), Vector3D(0, 0, 0));
  EXPECT_TRUE(a.IsPointOnLine(Vector3D(0, 0, 0)));
  EXPECT_TRUE(a.IsPointOnLine(Vector3D(-3, -6, -9)));
  EXPECT_TRUE(zero.IsPointOnLine(Vector3D(2, 4, 6)));
}

TEST(Line3DTest, IsPointOnLineFalse) {
  Line3D a = Line3D(Vector3D(0, 0, 0), Vector3D(1, 2, 3));
  Line3D zero = Line3D(Vector3D(2, 4, 6), Vector3D(0, 0, 0));
  EXPECT_FALSE(a.IsPointOnLine(Vector3D(3, 2, 1)));
  EXPECT_FALSE(zero.IsPointOnLine(Vector3D(0, 0, 0)));
  EXPECT_FALSE(zero.IsPointOnLine(Vector3D(1, 2, 3)));
}

TEST(Line3DTest, IntersectNotZero) {
  Line3D a = Line3D(Vector3D(0, 0, 0), Vector3D(1, 2, 3));
  Line3D b = Line3D(Vector3D(0, 0, 0), Vector3D(4, 5, 6));
  Line3D c = Line3D(Vector3D(-1, -2, -3), Vector3D(-4, -5, -6));
  std::pair<Vector3D, bool> result1 = a.Intersect(b);
  std::pair<Vector3D, bool> result2 = b.Intersect(a);
  std::pair<Vector3D, bool> result3 = a.Intersect(c);
  std::pair<Vector3D, bool> result4 = c.Intersect(a);
  std::pair<Vector3D, bool> result5 = b.Intersect(c);
  std::pair<Vector3D, bool> result6 = c.Intersect(b);
  std::pair<Vector3D, bool> result7 = a.Intersect(a);
  EXPECT_TRUE(result1.second);
  EXPECT_TRUE(result2.second);
  EXPECT_TRUE(result3.second);
  EXPECT_TRUE(result4.second);
  EXPECT_FALSE(result5.second);
  EXPECT_FALSE(result6.second);
  EXPECT_FALSE(result7.second);
  EXPECT_EQ(result1.first, Vector3D(0, 0, 0));
  EXPECT_EQ(result2.first, Vector3D(0, 0, 0));
  EXPECT_EQ(result3.first, Vector3D(-1, -2, -3));
  EXPECT_EQ(result4.first, Vector3D(-1, -2, -3));
  EXPECT_EQ(result5.first, Vector3D(INFINITY, INFINITY, INFINITY));
  EXPECT_EQ(result6.first, Vector3D(INFINITY, INFINITY, INFINITY));
  EXPECT_EQ(result7.first, Vector3D(INFINITY, INFINITY, INFINITY));
}

TEST(Line3DTest, IntersectZero) {
  Line3D a = Line3D(Vector3D(0, 0, 0), Vector3D(1, 2, 3));
  Line3D b = Line3D(Vector3D(0, 0, 0), Vector3D(0, 0, 0));
  Line3D c = Line3D(Vector3D(-1, -2, -3), Vector3D(0, 0, 0));
  Line3D d = Line3D(Vector3D(3, 2, 1), Vector3D(0, 0, 0));
  std::pair<Vector3D, bool> result1 = a.Intersect(b);
  std::pair<Vector3D, bool> result2 = b.Intersect(a);
  std::pair<Vector3D, bool> result3 = a.Intersect(c);
  std::pair<Vector3D, bool> result4 = c.Intersect(a);
  std::pair<Vector3D, bool> result5 = b.Intersect(c);
  std::pair<Vector3D, bool> result6 = c.Intersect(b);
  std::pair<Vector3D, bool> result7 = a.Intersect(d);
  std::pair<Vector3D, bool> result8 = d.Intersect(a);
  std::pair<Vector3D, bool> result9 = d.Intersect(d);
  EXPECT_TRUE(result1.second);
  EXPECT_TRUE(result2.second);
  EXPECT_TRUE(result3.second);
  EXPECT_TRUE(result4.second);
  EXPECT_FALSE(result5.second);
  EXPECT_FALSE(result6.second);
  EXPECT_FALSE(result7.second);
  EXPECT_FALSE(result8.second);
  EXPECT_TRUE(result9.second);
  EXPECT_EQ(result1.first, Vector3D(0, 0, 0));
  EXPECT_EQ(result2.first, Vector3D(0, 0, 0));
  EXPECT_EQ(result3.first, Vector3D(-1, -2, -3));
  EXPECT_EQ(result4.first, Vector3D(-1, -2, -3));
  EXPECT_TRUE(result5.first.IsNAV());
  EXPECT_TRUE(result6.first.IsNAV());
  EXPECT_TRUE(result7.first.IsNAV());
  EXPECT_TRUE(result8.first.IsNAV());
  EXPECT_EQ(result9.first, Vector3D(3, 2, 1));
}