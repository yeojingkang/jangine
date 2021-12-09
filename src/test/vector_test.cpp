#include "gtest/gtest.h"

#include "jangine.h"

// TODO: Add unit tests for non-specialized vector sizes

class Vec2 : public ::testing::Test
{
protected:
    void SetUp() override
    {
        v1 = jg::Vec2f{};
        v2 = jg::Vec2f{ 2.0f };
        v3 = jg::Vec2f{ 5.0f, -1.0f };
    }

    jg::Vec2f v1, v2, v3;
};

TEST_F(Vec2, Constructors)
{
    constexpr jg::Vec2f a;
    EXPECT_FLOAT_EQ(a.x, 0.0f);
    EXPECT_FLOAT_EQ(a.y, 0.0f);

    constexpr jg::Vec2f b{ 1.0f };
    EXPECT_FLOAT_EQ(b.x, 1.0f);
    EXPECT_FLOAT_EQ(b.y, 1.0f);

    jg::Vec2f c{ 2.0f, -3.0f };
    EXPECT_FLOAT_EQ(c[0], 2.0f);
    EXPECT_FLOAT_EQ(c[1], -3.0f);
}

TEST_F(Vec2, BasicOperations)
{
    // Negate
    auto out = -v2;
    EXPECT_FLOAT_EQ(out.x, -2.0f);
    EXPECT_FLOAT_EQ(out.y, -2.0f);

    // Add
    out = v1 + v2;
    EXPECT_FLOAT_EQ(out.x, 2.0f);
    EXPECT_FLOAT_EQ(out.y, 2.0f);

    out = v2 + v3;
    EXPECT_FLOAT_EQ(out.x, 7.0f);
    EXPECT_FLOAT_EQ(out.y, 1.0f);

    // Sub
    out = v1 - v2;
    EXPECT_FLOAT_EQ(out.x, -2.0f);
    EXPECT_FLOAT_EQ(out.y, -2.0f);

    out = v3 - v2;
    EXPECT_FLOAT_EQ(out.x, 3.0f);
    EXPECT_FLOAT_EQ(out.y, -3.0f);

    // Multiply
    out = v2 * 4.0f;
    EXPECT_FLOAT_EQ(out.x, 8.0f);
    EXPECT_FLOAT_EQ(out.y, 8.0f);

    out = 4.0f * v3;
    EXPECT_FLOAT_EQ(out.x, 20.0f);
    EXPECT_FLOAT_EQ(out.y, -4.0f);

    // Divide
    out = v2 / 4.0f;
    EXPECT_FLOAT_EQ(out.x, 0.5f);
    EXPECT_FLOAT_EQ(out.y, 0.5f);
}

TEST_F(Vec2, Dot)
{
    EXPECT_FLOAT_EQ(jg::Dot(v1, v2), 0.0f);
    EXPECT_FLOAT_EQ(jg::Dot(v2, v3), 8.0f);
}

TEST_F(Vec2, Length)
{
    EXPECT_FLOAT_EQ(jg::LengthSq(v1), 0.0f);
    EXPECT_FLOAT_EQ(jg::Length(v1), 0.0f);
    EXPECT_FLOAT_EQ(jg::LengthSq(v2), 8.0f);
    EXPECT_FLOAT_EQ(jg::Length(v2), 2.8284271f);
    EXPECT_FLOAT_EQ(jg::LengthSq(v3), 26.0f);
    EXPECT_FLOAT_EQ(jg::Length(v3), 5.0990195f);
}

TEST_F(Vec2, Normalize)
{
    auto out = jg::Normalize(v2);
    EXPECT_FLOAT_EQ(jg::LengthSq(out), 1.0f);
    EXPECT_FLOAT_EQ(out.x, 0.7071067812f);
    EXPECT_FLOAT_EQ(out.y, 0.7071067812f);
    out = jg::Normalize(v3);
    EXPECT_FLOAT_EQ(jg::LengthSq(out), 1.0f);
    EXPECT_FLOAT_EQ(out.x, 0.9805806757f);
    EXPECT_FLOAT_EQ(out.y, -0.1961161351f);
}



class Vec3 : public ::testing::Test
{
protected:
    void SetUp() override
    {
        v1 = jg::Vec3f{};
        v2 = jg::Vec3f{ 2.0f };
        v3 = jg::Vec3f{ 5.0f, -1.0f, 4.0f };
    }

    jg::Vec3f v1, v2, v3;
};

TEST_F(Vec3, Constructor)
{
    constexpr jg::Vec3f a;
    EXPECT_FLOAT_EQ(a.x, 0.0f);
    EXPECT_FLOAT_EQ(a.y, 0.0f);
    EXPECT_FLOAT_EQ(a.z, 0.0f);

    constexpr jg::Vec3f b{ 1.0f };
    EXPECT_FLOAT_EQ(b.x, 1.0f);
    EXPECT_FLOAT_EQ(b.y, 1.0f);
    EXPECT_FLOAT_EQ(b.z, 1.0f);

    jg::Vec3f c{ 2.0f, -3.0f, 4.0f };
    EXPECT_FLOAT_EQ(c[0], 2.0f);
    EXPECT_FLOAT_EQ(c[1], -3.0f);
    EXPECT_FLOAT_EQ(c[2], 4.0f);
}

TEST_F(Vec3, BasicOperations)
{
    // Negate
    auto out = -v2;
    EXPECT_FLOAT_EQ(out.x, -2.0f);
    EXPECT_FLOAT_EQ(out.y, -2.0f);
    EXPECT_FLOAT_EQ(out.z, -2.0f);

    // Add
    out = v1 + v2;
    EXPECT_FLOAT_EQ(out.x, 2.0f);
    EXPECT_FLOAT_EQ(out.y, 2.0f);
    EXPECT_FLOAT_EQ(out.z, 2.0f);

    out = v2 + v3;
    EXPECT_FLOAT_EQ(out.x, 7.0f);
    EXPECT_FLOAT_EQ(out.y, 1.0f);
    EXPECT_FLOAT_EQ(out.z, 6.0f);

    // Sub
    out = v1 - v2;
    EXPECT_FLOAT_EQ(out.x, -2.0f);
    EXPECT_FLOAT_EQ(out.y, -2.0f);
    EXPECT_FLOAT_EQ(out.z, -2.0f);

    out = v3 - v2;
    EXPECT_FLOAT_EQ(out.x, 3.0f);
    EXPECT_FLOAT_EQ(out.y, -3.0f);
    EXPECT_FLOAT_EQ(out.z, 2.0f);

    // Multiply
    out = v2 * 4.0f;
    EXPECT_FLOAT_EQ(out.x, 8.0f);
    EXPECT_FLOAT_EQ(out.y, 8.0f);
    EXPECT_FLOAT_EQ(out.z, 8.0f);

    out = 4.0f * v3;
    EXPECT_FLOAT_EQ(out.x, 20.0f);
    EXPECT_FLOAT_EQ(out.y, -4.0f);
    EXPECT_FLOAT_EQ(out.z, 16.0f);

    // Divide
    out = v2 / 4.0f;
    EXPECT_FLOAT_EQ(out.x, 0.5f);
    EXPECT_FLOAT_EQ(out.y, 0.5f);
    EXPECT_FLOAT_EQ(out.z, 0.5f);
}

TEST_F(Vec3, Dot)
{
    EXPECT_FLOAT_EQ(jg::Dot(v1, v2), 0.0f);
    EXPECT_FLOAT_EQ(jg::Dot(v2, v3), 16.0f);
}

TEST_F(Vec3, Length)
{
    EXPECT_FLOAT_EQ(jg::LengthSq(v1), 0.0f);
    EXPECT_FLOAT_EQ(jg::Length(v1), 0.0f);
    EXPECT_FLOAT_EQ(jg::LengthSq(v2), 12.0f);
    EXPECT_FLOAT_EQ(jg::Length(v2), 3.464101615f);
    EXPECT_FLOAT_EQ(jg::LengthSq(v3), 42.0f);
    EXPECT_FLOAT_EQ(jg::Length(v3), 6.480740698f);
}

TEST_F(Vec3, Normalize)
{
    auto out = jg::Normalize(v2);
    EXPECT_FLOAT_EQ(jg::LengthSq(out), 1.0f);
    EXPECT_FLOAT_EQ(out.x, 0.5773502692f);
    EXPECT_FLOAT_EQ(out.y, 0.5773502692f);
    EXPECT_FLOAT_EQ(out.z, 0.5773502692f);

    out = jg::Normalize(v3);
    EXPECT_FLOAT_EQ(jg::LengthSq(out), 1.0f);
    EXPECT_FLOAT_EQ(out.x, 0.7715167498f);
    EXPECT_FLOAT_EQ(out.y, -0.15430335f);
    EXPECT_FLOAT_EQ(out.z, 0.6172133998f);
}

TEST_F(Vec3, Cross)
{
    auto out = jg::Cross(v2, v3);
    EXPECT_FLOAT_EQ(out.x, 10.0f);
    EXPECT_FLOAT_EQ(out.y, 2.0f);
    EXPECT_FLOAT_EQ(out.z, -12.0f);

    out = jg::Cross(v3, v2);
    EXPECT_FLOAT_EQ(out.x, -10.0f);
    EXPECT_FLOAT_EQ(out.y, -2.0f);
    EXPECT_FLOAT_EQ(out.z, 12.0f);
}



class Vec4 : public ::testing::Test
{
protected:
    void SetUp() override
    {
        v1 = jg::Vec4f{};
        v2 = jg::Vec4f{ 2.0f };
        v3 = jg::Vec4f{ 5.0f, -1.0f, 4.0f, -3.0f };
    }

    jg::Vec4f v1, v2, v3;
};

TEST_F(Vec4, Constructors)
{
    constexpr jg::Vec4f a;
    EXPECT_FLOAT_EQ(a.x, 0.0f);
    EXPECT_FLOAT_EQ(a.y, 0.0f);
    EXPECT_FLOAT_EQ(a.z, 0.0f);
    EXPECT_FLOAT_EQ(a.w, 0.0f);

    constexpr jg::Vec4f b{ 1.0f };
    EXPECT_FLOAT_EQ(b.x, 1.0f);
    EXPECT_FLOAT_EQ(b.y, 1.0f);
    EXPECT_FLOAT_EQ(b.z, 1.0f);
    EXPECT_FLOAT_EQ(b.w, 1.0f);

    jg::Vec4f c{ 2.0f, -3.0f, 4.0f, -5.0f };
    EXPECT_FLOAT_EQ(c[0], 2.0f);
    EXPECT_FLOAT_EQ(c[1], -3.0f);
    EXPECT_FLOAT_EQ(c[2], 4.0f);
    EXPECT_FLOAT_EQ(c[3], -5.0f);
}

TEST_F(Vec4, BasicOperations)
{
    // Negate
    auto out = -v2;
    EXPECT_FLOAT_EQ(out.x, -2.0f);
    EXPECT_FLOAT_EQ(out.y, -2.0f);
    EXPECT_FLOAT_EQ(out.z, -2.0f);
    EXPECT_FLOAT_EQ(out.w, -2.0f);

    // Add
    out = v1 + v2;
    EXPECT_FLOAT_EQ(out.x, 2.0f);
    EXPECT_FLOAT_EQ(out.y, 2.0f);
    EXPECT_FLOAT_EQ(out.z, 2.0f);
    EXPECT_FLOAT_EQ(out.w, 2.0f);

    out = v2 + v3;
    EXPECT_FLOAT_EQ(out.x, 7.0f);
    EXPECT_FLOAT_EQ(out.y, 1.0f);
    EXPECT_FLOAT_EQ(out.z, 6.0f);
    EXPECT_FLOAT_EQ(out.w, -1.0f);

    // Sub
    out = v1 - v2;
    EXPECT_FLOAT_EQ(out.x, -2.0f);
    EXPECT_FLOAT_EQ(out.y, -2.0f);
    EXPECT_FLOAT_EQ(out.z, -2.0f);
    EXPECT_FLOAT_EQ(out.w, -2.0f);

    out = v3 - v2;
    EXPECT_FLOAT_EQ(out.x, 3.0f);
    EXPECT_FLOAT_EQ(out.y, -3.0f);
    EXPECT_FLOAT_EQ(out.z, 2.0f);
    EXPECT_FLOAT_EQ(out.w, -5.0f);

    // Multiply
    out = v2 * 4.0f;
    EXPECT_FLOAT_EQ(out.x, 8.0f);
    EXPECT_FLOAT_EQ(out.y, 8.0f);
    EXPECT_FLOAT_EQ(out.z, 8.0f);
    EXPECT_FLOAT_EQ(out.w, 8.0f);

    out = 4.0f * v3;
    EXPECT_FLOAT_EQ(out.x, 20.0f);
    EXPECT_FLOAT_EQ(out.y, -4.0f);
    EXPECT_FLOAT_EQ(out.z, 16.0f);
    EXPECT_FLOAT_EQ(out.w, -12.0f);

    // Divide
    out = v2 / 4.0f;
    EXPECT_FLOAT_EQ(out.x, 0.5f);
    EXPECT_FLOAT_EQ(out.y, 0.5f);
    EXPECT_FLOAT_EQ(out.z, 0.5f);
    EXPECT_FLOAT_EQ(out.w, 0.5f);
}

TEST_F(Vec4, Dot)
{
    EXPECT_FLOAT_EQ(jg::Dot(v1, v2), 0.0f);
    EXPECT_FLOAT_EQ(jg::Dot(v2, v3), 10.0f);
}

TEST_F(Vec4, Length)
{
    EXPECT_FLOAT_EQ(jg::LengthSq(v1), 0.0f);
    EXPECT_FLOAT_EQ(jg::Length(v1), 0.0f);
    EXPECT_FLOAT_EQ(jg::LengthSq(v2), 16.0f);
    EXPECT_FLOAT_EQ(jg::Length(v2), 4.0f);
    EXPECT_FLOAT_EQ(jg::LengthSq(v3), 51.0f);
    EXPECT_FLOAT_EQ(jg::Length(v3), 7.141428429f);
}

TEST_F(Vec4, Normalize)
{
    auto out = jg::Normalize(v2);
    EXPECT_FLOAT_EQ(jg::LengthSq(out), 1.0f);
    EXPECT_FLOAT_EQ(out.x, 0.5f);
    EXPECT_FLOAT_EQ(out.y, 0.5f);
    EXPECT_FLOAT_EQ(out.z, 0.5f);
    EXPECT_FLOAT_EQ(out.w, 0.5f);

    out = jg::Normalize(v3);
    EXPECT_FLOAT_EQ(jg::LengthSq(out), 1.0f);
    EXPECT_FLOAT_EQ(out.x, 0.700140042f);
    EXPECT_FLOAT_EQ(out.y, -0.1400280084f);
    EXPECT_FLOAT_EQ(out.z, 0.5601120336f);
    EXPECT_FLOAT_EQ(out.w, -0.4200840252f);
}
