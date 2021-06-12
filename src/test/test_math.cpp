#include "gtest/gtest.h"

#include "jangine.h"

TEST(Math, Vector)
{
    jg::Vec2f v2a;
    EXPECT_FLOAT_EQ(v2a.x, 0.0f);
    EXPECT_FLOAT_EQ(v2a.y, 0.0f);

    jg::Vec2f v2b{ 2.0f };
    EXPECT_FLOAT_EQ(v2b.x, 2.0f);
    EXPECT_FLOAT_EQ(v2b.y, 2.0f);

    jg::Vec2f v2c{ 5.0f, -1.0f };
    EXPECT_FLOAT_EQ(v2c.x, 5.0f);
    EXPECT_FLOAT_EQ(v2c.y, -1.0f);
}
