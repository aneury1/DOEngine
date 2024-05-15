#include "Color.h"
#include "Utils.h"
#include <gtest/gtest.h>

TEST(UtilsTests, DISABLED_GetPorcentageTestsInteger)
{
    int expected = 782U;
    EXPECT_EQ(expected, getPercentageFrom(78U, 1003U));

    expected = 224474U;
    EXPECT_EQ(expected, getPercentageFrom(65U, 345345U));

    expected = 11250U;
    EXPECT_EQ(expected, getPercentageFrom(150U, 7500U));
}

TEST(UtilsTests, GetRandomNumberIsBeetweenRangeInteger)
{
    int startRange = 1;
    int endRange = 123;

    int result = getRandomInt(startRange, endRange);

    ASSERT_LE(startRange, result);
    ASSERT_GE(endRange, result);

    startRange = -13;
    endRange = 5;

    result = getRandomInt(startRange, endRange);

    ASSERT_LE(startRange, result);
    ASSERT_GE(endRange, result);

    startRange = 7997;
    endRange = 10030;

    result = getRandomInt(startRange, endRange);

    ASSERT_LE(startRange, result);
    ASSERT_GE(endRange, result);

    long startRangeLong = 7997L;
    long endRangeLong = 10030L;

    long resultLong = getRandomInt(startRangeLong, endRangeLong);

    ASSERT_LE(startRangeLong, resultLong);
    ASSERT_GE(endRangeLong, resultLong);
}

TEST(UtilsTests, GetRandomNumberIsBeetweenRangeDouble)
{
    double startRange = 0.03;
    double endRange = 1.04;

    double result = getRandomReal(startRange, endRange);

    ASSERT_LE(startRange, result);
    ASSERT_GE(endRange, result);

    startRange = 2000.34;
    endRange = 10008.054;

    result = getRandomReal(startRange, endRange);

    ASSERT_LE(startRange, result);
    ASSERT_GE(endRange, result);

    startRange = -3.5;
    endRange = -1.4;

    result = getRandomReal(startRange, endRange);

    ASSERT_LE(startRange, result);
    ASSERT_GE(endRange, result);

    startRange = -3.5;
    endRange = 2.07;

    result = getRandomReal(startRange, endRange);

    ASSERT_LE(startRange, result);
    ASSERT_GE(endRange, result);

    float startRangeFloat = -3.5f;
    float endRangeFloat = 2.07f;

    float resultFloat = getRandomReal(startRangeFloat, endRangeFloat);

    ASSERT_LE(startRangeFloat, resultFloat);
    ASSERT_GE(endRangeFloat, resultFloat);
}

TEST(UtilsTests, ClampTests)
{
    double val = 0.03;
    double min = -0.3;
    double max = 1.4;
    double result = clamp(val, min, max);

    EXPECT_DOUBLE_EQ(val, result);

    val = 4.5;
    min = 5.4;
    max = 10.4;
    result = clamp(val, min, max);

    EXPECT_DOUBLE_EQ(min, result);

    val = 15.4;
    min = 5.4;
    max = 10.4;
    result = clamp(val, min, max);

    EXPECT_DOUBLE_EQ(max, result);
}
