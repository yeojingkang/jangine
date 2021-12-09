#include "gtest/gtest.h"

#include "jangine.h"

TEST(Matrix, General)
{
    // Ctors & operator[]
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

    // Mat * Mat
    jg::Mat<float, 2, 3> m1{
        1.0f, 2.0f,
        3.0f, 4.0f,
        5.0f, 6.0f
    };
    jg::Mat<float, 3, 2> m2{
        1.0f, -1.0f, 2.0f,
        1.0f, 5.0f, -3.0f
    };
    auto out = m1 * m2;
    EXPECT_FLOAT_EQ(out[0][0], 8.0f);
    EXPECT_FLOAT_EQ(out[0][1], 10.0f);
    EXPECT_FLOAT_EQ(out[1][0], 1.0f);
    EXPECT_FLOAT_EQ(out[1][1], 4.0f);

    // Mat * Vec
    jg::Mat<float, 3, 3> m3{
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        3.0f, 4.0f, 1.0f
    };
    constexpr jg::Vec3f v{ 7.0f, 2.0f, 1.0f };
    auto vOut = m3 * v;
    EXPECT_FLOAT_EQ(vOut[0], 10.0f);
    EXPECT_FLOAT_EQ(vOut[1], 6.0f);
    EXPECT_FLOAT_EQ(vOut[2], 1.0f);

    // Mat * Scalar
    auto out2 = m1 * 2.0f;
    EXPECT_FLOAT_EQ(out2[0][0], 2.0f);
    EXPECT_FLOAT_EQ(out2[0][1], 4.0f);
    EXPECT_FLOAT_EQ(out2[1][0], 6.0f);
    EXPECT_FLOAT_EQ(out2[1][1], 8.0f);
    EXPECT_FLOAT_EQ(out2[2][0], 10.0f);
    EXPECT_FLOAT_EQ(out2[2][1], 12.0f);

    // Basic operations
    jg::Mat<float, 2, 1> m4{ 2.0f, 4.0f };
    jg::Mat<float, 2, 1> m5{ 7.0f, 3.0f };

    auto out3 = -m4;
    EXPECT_FLOAT_EQ(out3[0][0], -2.0f);
    EXPECT_FLOAT_EQ(out3[0][1], -4.0f);

    out3 = m4 + m5;
    EXPECT_FLOAT_EQ(out3[0][0], 9.0f);
    EXPECT_FLOAT_EQ(out3[0][1], 7.0f);

    out3 = m4 - m5;
    EXPECT_FLOAT_EQ(out3[0][0], -5.0f);
    EXPECT_FLOAT_EQ(out3[0][1], 1.0f);
}

TEST(Matrix, Transpose)
{
    jg::Mat<float, 5, 5> m1{
         1.0f,  2.0f,  3.0f,  4.0f,  5.0f,
         6.0f,  7.0f,  8.0f,  9.0f, 10.0f,
        11.0f, 12.0f, 13.0f, 14.0f, 15.0f,
        16.0f, 17.0f, 18.0f, 19.0f, 20.0f,
        21.0f, 22.0f, 23.0f, 24.0f, 25.0f
    };

    const auto transposed = jg::Transpose(m1);
    EXPECT_FLOAT_EQ(transposed[0][0], 1.0f);
    EXPECT_FLOAT_EQ(transposed[0][1], 6.0f);
    EXPECT_FLOAT_EQ(transposed[0][2], 11.0f);
    EXPECT_FLOAT_EQ(transposed[0][3], 16.0f);
    EXPECT_FLOAT_EQ(transposed[0][4], 21.0f);
    EXPECT_FLOAT_EQ(transposed[1][0], 2.0f);
    EXPECT_FLOAT_EQ(transposed[1][1], 7.0f);
    EXPECT_FLOAT_EQ(transposed[1][2], 12.0f);
    EXPECT_FLOAT_EQ(transposed[1][3], 17.0f);
    EXPECT_FLOAT_EQ(transposed[1][4], 22.0f);
    EXPECT_FLOAT_EQ(transposed[2][0], 3.0f);
    EXPECT_FLOAT_EQ(transposed[2][1], 8.0f);
    EXPECT_FLOAT_EQ(transposed[2][2], 13.0f);
    EXPECT_FLOAT_EQ(transposed[2][3], 18.0f);
    EXPECT_FLOAT_EQ(transposed[2][4], 23.0f);
    EXPECT_FLOAT_EQ(transposed[3][0], 4.0f);
    EXPECT_FLOAT_EQ(transposed[3][1], 9.0f);
    EXPECT_FLOAT_EQ(transposed[3][2], 14.0f);
    EXPECT_FLOAT_EQ(transposed[3][3], 19.0f);
    EXPECT_FLOAT_EQ(transposed[3][4], 24.0f);
    EXPECT_FLOAT_EQ(transposed[4][0], 5.0f);
    EXPECT_FLOAT_EQ(transposed[4][1], 10.0f);
    EXPECT_FLOAT_EQ(transposed[4][2], 15.0f);
    EXPECT_FLOAT_EQ(transposed[4][3], 20.0f);
    EXPECT_FLOAT_EQ(transposed[4][4], 25.0f);
}

class Mat3 : public ::testing::Test
{
protected:
    void SetUp() override
    {
        m1 = jg::Mat3f{
            5.0f, 0.0f, 0.0f,
            0.0f, 5.0f, 0.0f,
            3.0f, 7.0f, 1.0f
        };
        m2 = jg::Mat3f{
            8.0f, 3.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            2.0f, 4.0f, 1.0f
        };
    }

    jg::Mat3f m1, m2;

    void CheckMatValues(const jg::Mat3f& m,
        float x0, float y0, float z0,
        float x1, float y1, float z1,
        float x2, float y2, float z2)
    {
        EXPECT_FLOAT_EQ(m[0][0], x0);
        EXPECT_FLOAT_EQ(m[0][1], y0);
        EXPECT_FLOAT_EQ(m[0][2], z0);
        EXPECT_FLOAT_EQ(m[1][0], x1);
        EXPECT_FLOAT_EQ(m[1][1], y1);
        EXPECT_FLOAT_EQ(m[1][2], z1);
        EXPECT_FLOAT_EQ(m[2][0], x2);
        EXPECT_FLOAT_EQ(m[2][1], y2);
        EXPECT_FLOAT_EQ(m[2][2], z2);
    }
};

TEST_F(Mat3, Constructors)
{
    constexpr jg::Mat3f a;
    for (auto i = 0; i < 9; ++i)
        EXPECT_FLOAT_EQ(a.data[0], 0.0f);
    EXPECT_FLOAT_EQ(a[0][0], 0.0f);

    constexpr jg::Mat3f b{
        2.0f, 7.0f, -5.0f,
        1.0f, 3.0f, 7.0f,
        -20.0f, 2.0f, 9.0f
    };
    CheckMatValues(b,
        2.0f, 7.0f, -5.0f,
        1.0f, 3.0f, 7.0f,
        -20.0f, 2.0f, 9.0f);
}

TEST_F(Mat3, BasicOperations)
{
    // Negate
    constexpr jg::Mat3f cm{
        1.0f, 2.0f, 3.0f,
        4.0f, 5.0f, 6.0f,
        7.0f, 8.0f, 9.0f
    };
    constexpr auto cneg = -cm;
    CheckMatValues(cneg,
        -1.0f, -2.0f, -3.0f,
        -4.0f, -5.0f, -6.0f,
        -7.0f, -8.0f, -9.0f);

    auto out = -m1;
    CheckMatValues(out,
        -5.0f, 0.0f, 0.0f,
        0.0f, -5.0f, 0.0f,
        -3.0f, -7.0f, -1.0f);

    // Add
    out = m1 + m2;
    CheckMatValues(out,
        13.0f, 3.0f, 0.0f,
        0.0f, 6.0f, 0.0f,
        5.0f, 11.0f, 2.0f);

    // Subtract
    out = m1 - m2;
    CheckMatValues(out,
        -3.0f, -3.0f, 0.0f,
        0.0f, 4.0f, 0.0f,
        1.0f, 3.0f, 0.0f);

    // Mat * Mat
    out = m1 * m2;
    CheckMatValues(out,
        40.0f, 15.0f, 0.0f,
        0.0f, 5.0f, 0.0f,
        13.0f, 27.0f, 1.0f);

    constexpr auto t = jg::Mat3f::Translation(1.0f, 2.0f);
    constexpr auto s = jg::Mat3f::Scale(3.0f, 4.0f);
    out = t * s;
    CheckMatValues(out,
        3.0f, 0.0f, 0.0f,
        0.0f, 4.0f, 0.0f,
        1.0f, 2.0f, 1.0f);

    // Mat * Vec
    constexpr jg::Vec3f vec{ 7.0f, 7.0f, 1.0f };
    auto vOut = m1 * vec;
    EXPECT_FLOAT_EQ(vOut[0], 38.0f);
    EXPECT_FLOAT_EQ(vOut[1], 42.0f);
    EXPECT_FLOAT_EQ(vOut[2], 1.0f);

    // Mat * Scalar
    out = m1 * 2.0f;
    CheckMatValues(out,
        10.0f, 0.0f, 0.0f,
        0.0f, 10.0f, 0.0f,
        6.0f, 14.0f, 2.0f);

    out = 3.0f * m2;
    CheckMatValues(out,
        24.0f, 9.0f, 0.0f,
        0.0f, 3.0f, 0.0f,
        6.0f, 12.0f, 3.0f);
}

TEST_F(Mat3, HomogenousMatrix)
{
    constexpr auto iden = jg::Mat3f::Identity();
    CheckMatValues(iden,
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f);

    constexpr auto tran = jg::Mat3f::Translation(8.0f, 7.0f);
    CheckMatValues(tran,
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        8.0f, 7.0f, 1.0f);

    constexpr auto scale = jg::Mat3f::Scale(-9.0f, 3.0f);
    CheckMatValues(scale,
        -9.0f, 0.0f, 0.0f,
        0.0f, 3.0f, 0.0f,
        0.0f, 0.0f, 1.0f);

    auto rot = jg::Mat3f::Rotation(0.5f * jg::HALF_PI);
    CheckMatValues(rot,
        0.7071067812f, 0.7071067812f, 0.0f,
        -0.7071067812f, 0.7071067812f, 0.0f,
        0.0f, 0.0f, 1.0f);
}

TEST_F(Mat3, Transpose)
{
    constexpr jg::Mat3f mat{
        1.0f, 2.0f, 3.0f,
        4.0f, 5.0f, 6.0f,
        7.0f, 8.0f, 9.0f,
    };

    constexpr auto transposed = jg::Transpose(mat);
    EXPECT_FLOAT_EQ(transposed[0][0], 1.0f);
    EXPECT_FLOAT_EQ(transposed[0][1], 4.0f);
    EXPECT_FLOAT_EQ(transposed[0][2], 7.0f);
    EXPECT_FLOAT_EQ(transposed[1][0], 2.0f);
    EXPECT_FLOAT_EQ(transposed[1][1], 5.0f);
    EXPECT_FLOAT_EQ(transposed[1][2], 8.0f);
    EXPECT_FLOAT_EQ(transposed[2][0], 3.0f);
    EXPECT_FLOAT_EQ(transposed[2][1], 6.0f);
    EXPECT_FLOAT_EQ(transposed[2][2], 9.0f);
}

TEST_F(Mat3, Determinant)
{
    constexpr auto det1 = jg::Determinant(jg::Mat3f::Identity());
    EXPECT_FLOAT_EQ(det1, 1.0f);

    constexpr auto det2 = jg::Determinant(jg::Mat3f::Scale(2.0f, 3.0f));
    EXPECT_FLOAT_EQ(det2, 6.0f);

    EXPECT_FLOAT_EQ(jg::Determinant(m1), 25.0f);
    EXPECT_FLOAT_EQ(jg::Determinant(m2), 8.0f);
}

TEST_F(Mat3, Inverse)
{
    constexpr jg::Mat3f s = jg::Mat3f::Scale(2.0f, 4.0f);
    const auto si = jg::Inverse(s);
    CheckMatValues(si,
        0.5f, 0.0f, 0.0f,
        0.0f, 0.25f, 0.0f,
        0.0f, 0.0f, 1.0f);

    constexpr jg::Mat3f t = jg::Mat3f::Translation(3.0f, 1.0f);
    const auto ti = jg::Inverse(t);
    CheckMatValues(ti,
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        -3.0f, -1.0f, 1.0f);
}
