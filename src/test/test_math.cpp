#include "gtest/gtest.h"

#include "jangine.h"

class Vec2Test : public ::testing::Test
{
protected:
    void SetUp() override
    {
    }

    jg::Vec2f v1;
    jg::Vec2f v2{ 2.0f };
    jg::Vec2f v3{ 5.0f, -1.0f };
};

TEST_F(Vec2Test, InitialValues)
{
    EXPECT_FLOAT_EQ(v1.x, 0.0f);
    EXPECT_FLOAT_EQ(v1.y, 0.0f);

    EXPECT_FLOAT_EQ(v2.x, 2.0f);
    EXPECT_FLOAT_EQ(v2.y, 2.0f);

    EXPECT_FLOAT_EQ(v3.x, 5.0f);
    EXPECT_FLOAT_EQ(v3.y, -1.0f);
}

TEST_F(Vec2Test, Add)
{
    auto out = v1 + v2;
    EXPECT_FLOAT_EQ(out.x, 2.0f);
    EXPECT_FLOAT_EQ(out.y, 2.0f);

    out = v2 + v3;
    EXPECT_FLOAT_EQ(out.x, 7.0f);
    EXPECT_FLOAT_EQ(out.y, 1.0f);
}
