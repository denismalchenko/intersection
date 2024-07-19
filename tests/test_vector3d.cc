#include <gtest/gtest.h>

// #include "../src/functions.h"
#include "../src/vector3d.h"

TEST(Vector3DTest, IsZero) {
  const Vector3D zero(0, 0, 0);
  const Vector3D almost_zero(1e-10, 1e-10, -1e-10);
  const Vector3D one(1, 1, 1);
  const Vector3D minus_one(-1, -1, -1);
  EXPECT_TRUE(zero.IsZero());
  EXPECT_TRUE(almost_zero.IsZero());
  EXPECT_FALSE(one.IsZero());
  EXPECT_FALSE(minus_one.IsZero());
}

TEST(Vector3DTest, IsNAV) {
  const Vector3D zero(0, 0, 0);
  const Vector3D one(1, 1, 1);
  const Vector3D nav(NAN, NAN, NAN);
  EXPECT_FALSE(zero.IsNAV());
  EXPECT_FALSE(one.IsNAV());
  EXPECT_TRUE(nav.IsNAV());
}

TEST(Vector3DTest, Equal) {
  const Vector3D a(1, 2, 3);
  const Vector3D b(1, 2, 3);
  const Vector3D c(0, 0, 0);
  const Vector3D nav1(NAN, NAN, NAN);
  const Vector3D nav2(NAN, NAN, NAN);
  EXPECT_FALSE(a == c);
  EXPECT_FALSE(c == a);
  EXPECT_TRUE(a == b);
  EXPECT_TRUE(b == a);
  EXPECT_TRUE(nav1 == nav2);
  EXPECT_TRUE(nav2 == nav1);
  EXPECT_FALSE(nav1 == a);
  EXPECT_FALSE(nav1 == b);
  EXPECT_FALSE(nav2 == a);
  EXPECT_FALSE(c == nav1);
}

TEST(Vector3DTest, Add1) {
  const Vector3D a(1, 2, 3);
  const Vector3D b(4, 5, 6);
  EXPECT_EQ(a + b, Vector3D(5, 7, 9));
  EXPECT_EQ(b + a, Vector3D(5, 7, 9));
}

TEST(Vector3DTest, Add2) {
  const Vector3D a(1, -2, 3);
  const Vector3D b(-4, 5, 0);
  EXPECT_EQ(a + b, Vector3D(-3, 3, 3));
  EXPECT_EQ(b + a, Vector3D(-3, 3, 3));
}

TEST(Vector3DTest, Add3) {
  const Vector3D a(1, 2, 3);
  const Vector3D b(0, 0, 0);
  EXPECT_EQ(a + b, Vector3D(1, 2, 3));
  EXPECT_EQ(b + a, Vector3D(1, 2, 3));
}

TEST(Vector3DTest, Sub1) {
  const Vector3D a(1, 2, 3);
  const Vector3D b(4, 5, 6);
  EXPECT_EQ(a - b, Vector3D(-3, -3, -3));
  EXPECT_EQ(b - a, Vector3D(3, 3, 3));
}

TEST(Vector3DTest, Sub2) {
  const Vector3D a(1, -2, 3);
  const Vector3D b(-4, 5, 0);
  EXPECT_EQ(a - b, Vector3D(5, -7, 3));
  EXPECT_EQ(b - a, Vector3D(-5, 7, -3));
}

TEST(Vector3DTest, Sub3) {
  const Vector3D a(1, 2, 3);
  const Vector3D b(0, 0, 0);
  EXPECT_EQ(a - b, Vector3D(1, 2, 3));
  EXPECT_EQ(b - a, Vector3D(-1, -2, -3));
}

TEST(Vector3DTest, Mult1) {
  const Vector3D a(1, 2, 3);
  EXPECT_EQ(a * 2, Vector3D(2, 4, 6));
  EXPECT_EQ(2 * a, Vector3D(2, 4, 6));
}

TEST(Vector3DTest, Mult2) {
  const Vector3D a(1, 2, 3);
  EXPECT_EQ(a * -3, Vector3D(-3, -6, -9));
  EXPECT_EQ(-3 * a, Vector3D(-3, -6, -9));
}

TEST(Vector3DTest, Mult3) {
  const Vector3D a(1, 2, 3);
  EXPECT_EQ(a * 0, Vector3D(0, 0, 0));
  EXPECT_EQ(0 * a, Vector3D(0, 0, 0));
}

TEST(Vector3DTest, IsCollinearNotZeroTrue) {
  const Vector3D a(1, 2, 3);
  const Vector3D b(1.5, 3, 4.5);
  const Vector3D c(-3, -6, -9);
  EXPECT_TRUE(a.IsCollinearNotZero(b));
  EXPECT_TRUE(b.IsCollinearNotZero(a));
  EXPECT_TRUE(a.IsCollinearNotZero(c));
  EXPECT_TRUE(c.IsCollinearNotZero(a));
  EXPECT_TRUE(c.IsCollinearNotZero(b));
  EXPECT_TRUE(b.IsCollinearNotZero(c));
  EXPECT_TRUE(a.IsCollinearNotZero(a));
  EXPECT_TRUE(b.IsCollinearNotZero(b));
  EXPECT_TRUE(c.IsCollinearNotZero(c));
}

TEST(Vector3DTest, IsCollinearNotZeroFalse) {
  const Vector3D a(1, 2, 3);
  const Vector3D b(4, 5, 6);
  const Vector3D c(-1, 2, 3);
  EXPECT_FALSE(a.IsCollinearNotZero(b));
  EXPECT_FALSE(b.IsCollinearNotZero(a));
  EXPECT_FALSE(a.IsCollinearNotZero(c));
  EXPECT_FALSE(c.IsCollinearNotZero(a));
  EXPECT_FALSE(c.IsCollinearNotZero(b));
  EXPECT_FALSE(b.IsCollinearNotZero(c));
}

TEST(Vector3DTest, IsCollinearTrue) {
  const Vector3D a(1, 2, 3);
  const Vector3D b(1.5, 3, 4.5);
  const Vector3D c(-3, -6, -9);
  const Vector3D zero(0, 0, 0);
  EXPECT_TRUE(a.IsCollinear(b));
  EXPECT_TRUE(b.IsCollinear(a));
  EXPECT_TRUE(a.IsCollinear(c));
  EXPECT_TRUE(c.IsCollinear(a));
  EXPECT_TRUE(c.IsCollinear(b));
  EXPECT_TRUE(b.IsCollinear(c));
  EXPECT_TRUE(a.IsCollinear(zero));
  EXPECT_TRUE(zero.IsCollinear(a));
  EXPECT_TRUE(b.IsCollinear(zero));
  EXPECT_TRUE(zero.IsCollinear(b));
  EXPECT_TRUE(c.IsCollinear(zero));
  EXPECT_TRUE(zero.IsCollinear(c));
  EXPECT_TRUE(a.IsCollinear(a));
  EXPECT_TRUE(b.IsCollinear(b));
  EXPECT_TRUE(c.IsCollinear(c));
  EXPECT_TRUE(zero.IsCollinear(zero));
}

TEST(Vector3DTest, IsCollinearFalse) {
  const Vector3D a(1, 2, 3);
  const Vector3D b(4, 5, 6);
  const Vector3D c(-1, 2, 3);
  EXPECT_FALSE(a.IsCollinear(b));
  EXPECT_FALSE(b.IsCollinear(a));
  EXPECT_FALSE(a.IsCollinear(c));
  EXPECT_FALSE(c.IsCollinear(a));
  EXPECT_FALSE(c.IsCollinear(b));
  EXPECT_FALSE(b.IsCollinear(c));
}

TEST(Vector3DTest, IsCoDirectionalNotZeroTrue) {
  const Vector3D a(1, 2, 3);
  const Vector3D b(1.5, 3, 4.5);
  EXPECT_TRUE(a.IsCoDirectionalNotZero(b));
  EXPECT_TRUE(b.IsCoDirectionalNotZero(a));
  EXPECT_TRUE(a.IsCoDirectionalNotZero(a));
  EXPECT_TRUE(b.IsCoDirectionalNotZero(b));
}

TEST(Vector3DTest, IsCoDirectionalNotZeroFalse) {
  const Vector3D a(1, 2, 3);
  const Vector3D b(4, 5, 6);
  const Vector3D c(-3, -6, -9);
  EXPECT_FALSE(a.IsCoDirectionalNotZero(b));
  EXPECT_FALSE(b.IsCoDirectionalNotZero(a));
  EXPECT_FALSE(a.IsCoDirectionalNotZero(c));
  EXPECT_FALSE(c.IsCoDirectionalNotZero(a));
  EXPECT_FALSE(c.IsCoDirectionalNotZero(b));
  EXPECT_FALSE(b.IsCoDirectionalNotZero(c));
}

TEST(Vector3DTest, IsCoDirectionalTrue) {
  const Vector3D a(1, 2, 3);
  const Vector3D b(1.5, 3, 4.5);
  const Vector3D zero(0, 0, 0);
  EXPECT_TRUE(a.IsCoDirectional(b));
  EXPECT_TRUE(b.IsCoDirectional(a));
  EXPECT_TRUE(a.IsCoDirectional(zero));
  EXPECT_TRUE(zero.IsCoDirectional(a));
  EXPECT_TRUE(zero.IsCoDirectional(b));
  EXPECT_TRUE(b.IsCoDirectional(zero));
  EXPECT_TRUE(a.IsCoDirectional(a));
  EXPECT_TRUE(b.IsCoDirectional(b));
  EXPECT_TRUE(zero.IsCoDirectional(zero));
}

TEST(Vector3DTest, IsCoDirectionalFalse) {
  const Vector3D a(1, 2, 3);
  const Vector3D b(4, 5, 6);
  const Vector3D c(-3, -6, -9);
  EXPECT_FALSE(a.IsCoDirectional(b));
  EXPECT_FALSE(b.IsCoDirectional(a));
  EXPECT_FALSE(a.IsCoDirectional(c));
  EXPECT_FALSE(c.IsCoDirectional(a));
  EXPECT_FALSE(c.IsCoDirectional(b));
  EXPECT_FALSE(b.IsCoDirectional(c));
}