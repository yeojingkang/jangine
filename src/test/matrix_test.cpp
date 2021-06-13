#include "gtest/gtest.h"

#include "jangine.h"

TEST(Matrix, Placeholder)
{
    jg::Mat<float, 2, 3> a{2.0f, 3.0f};

    EXPECT_FLOAT_EQ(a.data[0], 2.0f);
    EXPECT_FLOAT_EQ(a.data[1], 3.0f);
    EXPECT_FLOAT_EQ(a.data[2], 0.0f);
    EXPECT_FLOAT_EQ(a[0].x, 2.0f);
    EXPECT_FLOAT_EQ(a[0].y, 3.0f);
    EXPECT_FLOAT_EQ(a[1].x, 0.0f);
    EXPECT_FLOAT_EQ(a[0][0], 2.0f);
    EXPECT_FLOAT_EQ(a[0][1], 3.0f);
    EXPECT_FLOAT_EQ(a[1][0], 0.0f);

    constexpr jg::Mat<float, 2, 3> b;
    for (auto i = 0; i < 6; ++i)
        EXPECT_FLOAT_EQ(b.data[i], 0.0f);

    jg::Mat<float, 2, 3> m1{
        1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f
    };
    jg::Mat<float, 3, 2> m2{
        1.0f, -1.0f, 2.0f, 1.0f, 5.0f, -3.0f
    };
    auto out = m1 * m2;
    EXPECT_FLOAT_EQ(out[0][0], 8.0f);
    EXPECT_FLOAT_EQ(out[0][1], 10.0f);
    EXPECT_FLOAT_EQ(out[1][0], 1.0f);
    EXPECT_FLOAT_EQ(out[1][1], 4.0f);

    jg::Mat<float, 3, 3> m3{
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        3.0f, 4.0f, 1.0f
    };
    jg::Vec3f v{ 0.0f, 0.0f, 1.0f };
    auto out2 = m3 * v;
    EXPECT_FLOAT_EQ(out2[0], 3.0f);
    EXPECT_FLOAT_EQ(out2[1], 4.0f);
    EXPECT_FLOAT_EQ(out2[2], 1.0f);
}
