#include <gtest/gtest.h>

#include <cmath>

#include "../src/segment3d.h"

TEST(Segment3DTest, Direction) {
  EXPECT_EQ(Segment3D(Vector3D(0, 0, 0), Vector3D(1, 2, 3)).Direction(),
            Vector3D(1, 2, 3));
  EXPECT_EQ(Segment3D(Vector3D(-1, -2, -3), Vector3D(1, 2, 3)).Direction(),
            Vector3D(2, 4, 6));
  EXPECT_EQ(Segment3D(Vector3D(2, 3, 4), Vector3D(2, 3, 4)).Direction(),
            Vector3D(0, 0, 0));
}

TEST(Segment3DTest, IsPointOnSegmentTrue) {
  Segment3D segment = Segment3D(Vector3D(0, 0, 0), Vector3D(1, 2, 3));
  EXPECT_TRUE(segment.IsPointOnSegment(Vector3D(0, 0, 0)));
  EXPECT_TRUE(segment.IsPointOnSegment(Vector3D(1, 2, 3)));
  EXPECT_TRUE(segment.IsPointOnSegment(Vector3D(0.5, 1, 1.5)));
  EXPECT_TRUE(segment.IsPointOnSegment(Vector3D(0.25, 0.5, 0.75)));
  EXPECT_TRUE(segment.IsPointOnSegment(Vector3D(0.75, 1.5, 2.25)));
}

TEST(Segment3DTest, IsPointOnSegmentFalse) {
  Segment3D segment = Segment3D(Vector3D(0, 0, 0), Vector3D(1, 2, 3));
  EXPECT_FALSE(segment.IsPointOnSegment(Vector3D(0, 0, 0.5)));
  EXPECT_FALSE(segment.IsPointOnSegment(Vector3D(1.25, 2, 3)));
  EXPECT_FALSE(segment.IsPointOnSegment(Vector3D(-3, -4, -5)));
  EXPECT_FALSE(segment.IsPointOnSegment(Vector3D(1.25, 2.5, 3.75)));
  EXPECT_FALSE(segment.IsPointOnSegment(Vector3D(-0.25, -0.5, -0.75)));
}

TEST(Segment3DTest, IntersectOnIntersetionAndParallelLines) {
  Segment3D a = Segment3D(Vector3D(0, 0, 0), Vector3D(1, 2, 3));
  Segment3D b = Segment3D(Vector3D(0, 0, 0), Vector3D(4, 5, 6));
  Segment3D c = Segment3D(Vector3D(4, 5, 6), Vector3D(1, 2, 3));
  Segment3D d = Segment3D(Vector3D(0.25, 0.5, 0.75), Vector3D(4.25, 5.5, 6.75));
  Segment3D e =
      Segment3D(Vector3D(-3.25, -3.5, -3.75), Vector3D(0.75, 1.5, 2.25));
  Segment3D f = Segment3D(Vector3D(-1.5, -1.5, -1.5), Vector3D(2.5, 3.5, 4.5));
  std::pair<Vector3D, bool> result_ab = Intersect(a, b);
  std::pair<Vector3D, bool> result_ac = Intersect(a, c);
  std::pair<Vector3D, bool> result_ad = Intersect(a, d);
  std::pair<Vector3D, bool> result_ae = Intersect(a, e);
  std::pair<Vector3D, bool> result_af = Intersect(a, f);
  std::pair<Vector3D, bool> result_bc = Intersect(b, c);
  std::pair<Vector3D, bool> result_bd = Intersect(b, d);
  std::pair<Vector3D, bool> result_be = Intersect(b, e);
  std::pair<Vector3D, bool> result_bf = Intersect(b, f);
  std::pair<Vector3D, bool> result_cd = Intersect(c, d);
  std::pair<Vector3D, bool> result_ce = Intersect(c, e);
  std::pair<Vector3D, bool> result_cf = Intersect(c, f);
  std::pair<Vector3D, bool> result_de = Intersect(d, e);
  std::pair<Vector3D, bool> result_df = Intersect(d, f);
  std::pair<Vector3D, bool> result_ef = Intersect(e, f);
  EXPECT_EQ(result_ab, b.Intersect(a));
  EXPECT_EQ(result_ac, c.Intersect(a));
  EXPECT_EQ(result_ad, d.Intersect(a));
  EXPECT_EQ(result_ae, e.Intersect(a));
  EXPECT_EQ(result_af, f.Intersect(a));
  EXPECT_EQ(result_bc, c.Intersect(b));
  EXPECT_EQ(result_bd, d.Intersect(b));
  EXPECT_EQ(result_be, e.Intersect(b));
  EXPECT_EQ(result_bf, f.Intersect(b));
  EXPECT_EQ(result_cd, d.Intersect(c));
  EXPECT_EQ(result_ce, e.Intersect(c));
  EXPECT_EQ(result_cf, f.Intersect(c));
  EXPECT_EQ(result_de, e.Intersect(d));
  EXPECT_EQ(result_df, f.Intersect(d));
  EXPECT_EQ(result_ef, f.Intersect(e));
  EXPECT_TRUE(result_ab.second);
  EXPECT_EQ(result_ab.first, Vector3D(0, 0, 0));
  EXPECT_TRUE(result_ac.second);
  EXPECT_EQ(result_ac.first, Vector3D(1, 2, 3));
  EXPECT_TRUE(result_ad.second);
  EXPECT_EQ(result_ad.first, Vector3D(0.25, 0.5, 0.75));
  EXPECT_TRUE(result_ae.second);
  EXPECT_EQ(result_ae.first, Vector3D(0.75, 1.5, 2.25));
  EXPECT_TRUE(result_af.second);
  EXPECT_EQ(result_af.first, Vector3D(0.5, 1, 1.5));
  EXPECT_TRUE(result_bc.second);
  EXPECT_EQ(result_bc.first, Vector3D(4, 5, 6));
  EXPECT_FALSE(result_bd.second);
  EXPECT_TRUE(result_bd.first.IsNAV());
  EXPECT_FALSE(result_be.second);
  EXPECT_TRUE(result_be.first.IsNAV());
  EXPECT_FALSE(result_bf.second);
  EXPECT_TRUE(result_bf.first.IsNAV());
  EXPECT_TRUE(result_cd.second);
  EXPECT_EQ(result_cd.first, Vector3D(3.25, 4.25, 5.25));
  EXPECT_FALSE(result_ce.second);
  EXPECT_TRUE(result_ce.first.IsNAV());
  EXPECT_TRUE(result_cf.second);
  EXPECT_EQ(result_cf.first, Vector3D(2.5, 3.5, 4.5));
  EXPECT_FALSE(result_de.second);
  EXPECT_TRUE(result_de.first.IsNAV());
  EXPECT_FALSE(result_df.second);
  EXPECT_TRUE(result_df.first.IsNAV());
  EXPECT_FALSE(result_ef.second);
  EXPECT_TRUE(result_ef.first.IsNAV());
}

TEST(Segment3DTest, IntersectOnOneLine) {
  Segment3D a = Segment3D(Vector3D(0, 0, 0), Vector3D(1, 2, 3));
  Segment3D b = Segment3D(Vector3D(1, 2, 3), Vector3D(2, 4, 6));
  Segment3D c = Segment3D(Vector3D(3, 6, 9), Vector3D(2, 4, 6));
  Segment3D d = Segment3D(Vector3D(0, 0, 0), Vector3D(3, 6, 9));
  Segment3D e = Segment3D(Vector3D(2, 4, 6), Vector3D(0, 0, 0));
  Segment3D f = Segment3D(Vector3D(1, 2, 3), Vector3D(3, 6, 9));
  std::pair<Vector3D, bool> result_ab = Intersect(a, b);
  std::pair<Vector3D, bool> result_ac = Intersect(a, c);
  std::pair<Vector3D, bool> result_ad = Intersect(a, d);
  std::pair<Vector3D, bool> result_ae = Intersect(a, e);
  std::pair<Vector3D, bool> result_af = Intersect(a, f);
  std::pair<Vector3D, bool> result_bc = Intersect(b, c);
  std::pair<Vector3D, bool> result_bd = Intersect(b, d);
  std::pair<Vector3D, bool> result_be = Intersect(b, e);
  std::pair<Vector3D, bool> result_bf = Intersect(b, f);
  std::pair<Vector3D, bool> result_cd = Intersect(c, d);
  std::pair<Vector3D, bool> result_ce = Intersect(c, e);
  std::pair<Vector3D, bool> result_cf = Intersect(c, f);
  std::pair<Vector3D, bool> result_de = Intersect(d, e);
  std::pair<Vector3D, bool> result_df = Intersect(d, f);
  std::pair<Vector3D, bool> result_ef = Intersect(e, f);
  EXPECT_EQ(result_ab, b.Intersect(a));
  EXPECT_EQ(result_ac, c.Intersect(a));
  EXPECT_EQ(result_ad, d.Intersect(a));
  EXPECT_EQ(result_ae, e.Intersect(a));
  EXPECT_EQ(result_af, f.Intersect(a));
  EXPECT_EQ(result_bc, c.Intersect(b));
  EXPECT_EQ(result_bd, d.Intersect(b));
  EXPECT_EQ(result_be, e.Intersect(b));
  EXPECT_EQ(result_bf, f.Intersect(b));
  EXPECT_EQ(result_cd, d.Intersect(c));
  EXPECT_EQ(result_ce, e.Intersect(c));
  EXPECT_EQ(result_cf, f.Intersect(c));
  EXPECT_EQ(result_de, e.Intersect(d));
  EXPECT_EQ(result_df, f.Intersect(d));
  EXPECT_EQ(result_ef, f.Intersect(e));
  EXPECT_TRUE(result_ab.second);
  EXPECT_EQ(result_ab.first, Vector3D(1, 2, 3));
  EXPECT_FALSE(result_ac.second);
  EXPECT_TRUE(result_ac.first.IsNAV());
  EXPECT_FALSE(result_ad.second);
  EXPECT_EQ(result_ad.first, Vector3D(INFINITY, INFINITY, INFINITY));
  EXPECT_FALSE(result_ae.second);
  EXPECT_EQ(result_ae.first, Vector3D(INFINITY, INFINITY, INFINITY));
  EXPECT_TRUE(result_af.second);
  EXPECT_EQ(result_af.first, Vector3D(1, 2, 3));
  EXPECT_TRUE(result_bc.second);
  EXPECT_EQ(result_bc.first, Vector3D(2, 4, 6));
  EXPECT_FALSE(result_bd.second);
  EXPECT_EQ(result_bd.first, Vector3D(INFINITY, INFINITY, INFINITY));
  EXPECT_FALSE(result_be.second);
  EXPECT_EQ(result_be.first, Vector3D(INFINITY, INFINITY, INFINITY));
  EXPECT_FALSE(result_bf.second);
  EXPECT_EQ(result_bf.first, Vector3D(INFINITY, INFINITY, INFINITY));
  EXPECT_FALSE(result_cd.second);
  EXPECT_EQ(result_cd.first, Vector3D(INFINITY, INFINITY, INFINITY));
  EXPECT_TRUE(result_ce.second);
  EXPECT_EQ(result_ce.first, Vector3D(2, 4, 6));
  EXPECT_FALSE(result_cf.second);
  EXPECT_EQ(result_cf.first, Vector3D(INFINITY, INFINITY, INFINITY));
  EXPECT_FALSE(result_de.second);
  EXPECT_EQ(result_de.first, Vector3D(INFINITY, INFINITY, INFINITY));
  EXPECT_FALSE(result_df.second);
  EXPECT_EQ(result_df.first, Vector3D(INFINITY, INFINITY, INFINITY));
  EXPECT_FALSE(result_ef.second);
  EXPECT_EQ(result_ef.first, Vector3D(INFINITY, INFINITY, INFINITY));
}

TEST(Segment3DTest, IntersectZero) {
  Segment3D a = Segment3D(Vector3D(0, 0, 0), Vector3D(1, 2, 3));
  Segment3D z1 = Segment3D(Vector3D(0, 0, 0), Vector3D(0, 0, 0));
  Segment3D z2 = Segment3D(Vector3D(1, 2, 3), Vector3D(1, 2, 3));
  Segment3D z3 =
      Segment3D(Vector3D(0.25, 0.5, 0.75), Vector3D(0.25, 0.5, 0.75));
  Segment3D z4 =
      Segment3D(Vector3D(1.25, 2.5, 3.75), Vector3D(1.25, 2.5, 3.75));
  Segment3D z5 = Segment3D(Vector3D(2, 3, 4), Vector3D(2, 3, 4));
  std::pair<Vector3D, bool> result1 = Intersect(a, z1);
  std::pair<Vector3D, bool> result2 = Intersect(a, z2);
  std::pair<Vector3D, bool> result3 = Intersect(a, z3);
  std::pair<Vector3D, bool> result4 = Intersect(a, z4);
  std::pair<Vector3D, bool> result5 = Intersect(a, z5);
  std::pair<Vector3D, bool> result12 = Intersect(z1, z2);
  std::pair<Vector3D, bool> result22 = Intersect(z2, z2);
  EXPECT_TRUE(result1.second);
  EXPECT_EQ(result1.first, Vector3D(0, 0, 0));
  EXPECT_TRUE(result2.second);
  EXPECT_EQ(result2.first, Vector3D(1, 2, 3));
  EXPECT_TRUE(result3.second);
  EXPECT_EQ(result3.first, Vector3D(0.25, 0.5, 0.75));
  EXPECT_FALSE(result4.second);
  EXPECT_TRUE(result4.first.IsNAV());
  EXPECT_FALSE(result5.second);
  EXPECT_TRUE(result5.first.IsNAV());
  EXPECT_FALSE(result12.second);
  EXPECT_TRUE(result4.first.IsNAV());
  EXPECT_TRUE(result22.second);
  EXPECT_EQ(result22.first, Vector3D(1, 2, 3));
}
