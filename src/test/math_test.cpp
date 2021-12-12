#include "gtest/gtest.h"

#include "jangine.h"

TEST(Math, FloatingPoint)
{
    EXPECT_TRUE(jg::FP_EQ(0.0f, 0.0f));
    EXPECT_FALSE(jg::FP_EQ(0.0f, 1.0f));
    EXPECT_TRUE(jg::FP_EQ(0.0, 0.0));
    EXPECT_FALSE(jg::FP_EQ(0.0, 1.0));

    EXPECT_TRUE(jg::FP_IS_ZERO(0.0f));
    EXPECT_TRUE(jg::FP_IS_ZERO(0.0));
    EXPECT_FALSE(jg::FP_IS_ZERO(10.0f));
    EXPECT_FALSE(jg::FP_IS_ZERO(10.0));
}
