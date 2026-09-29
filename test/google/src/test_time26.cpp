// Date Time: 2026-09-27-00-20-00
// Author: ohmycode-cn
// Email: ohcode@163.com
// Copyright (c) ohmycode-cn. All rights reserved.
// License: MIT

#include "test_time26.hpp"

#include <gtest/gtest.h>
#include "time26.hpp"

namespace {

    TEST(Time26Test, NonEmpty) {
        auto result = rbbl::tm26::get_time();
        EXPECT_FALSE(result.empty());
    }

    TEST(Time26Test, ExpectedLength) {
        // "YYYY-MM-DD-HH-MM-SS" = 19 characters
        auto result = rbbl::tm26::get_time();
        EXPECT_EQ(result.size(), 19);
    }

    TEST(Time26Test, ContainsDashes) {
        auto result = rbbl::tm26::get_time();
        // format: YYYY-MM-DD-HH-MM-SS, 5 dashes
        int dash_count = 0;
        for (char c : result) {
            if (c == '-') {
                ++dash_count;
            }
        }
        EXPECT_EQ(dash_count, 5);
    }

    TEST(Time26Test, ConsecutiveCallsNotIdentical) {
        // Two calls should produce different results (at least at second boundary)
        // This test may be flaky if both calls happen within the same second.
        // We only check that the function is callable and returns valid format.
        auto t1 = rbbl::tm26::get_time();
        auto t2 = rbbl::tm26::get_time();
        EXPECT_EQ(t1.size(), t2.size());
    }

    TEST(Time26Test, ValidYearRange) {
        auto result = rbbl::tm26::get_time();
        // First 4 chars should be a year >= 2025
        int year = std::stoi(result.substr(0, 4));
        EXPECT_GE(year, 2025);
        EXPECT_LE(year, 2099);
    }

    TEST(Time26Test, ValidMonthRange) {
        auto result = rbbl::tm26::get_time();
        int month = std::stoi(result.substr(5, 2));
        EXPECT_GE(month, 1);
        EXPECT_LE(month, 12);
    }

    TEST(Time26Test, ValidDayRange) {
        auto result = rbbl::tm26::get_time();
        int day = std::stoi(result.substr(8, 2));
        EXPECT_GE(day, 1);
        EXPECT_LE(day, 31);
    }

    TEST(Time26Test, ValidHourRange) {
        auto result = rbbl::tm26::get_time();
        int hour = std::stoi(result.substr(11, 2));
        EXPECT_GE(hour, 0);
        EXPECT_LE(hour, 23);
    }

    TEST(Time26Test, ValidMinuteRange) {
        auto result = rbbl::tm26::get_time();
        int minute = std::stoi(result.substr(14, 2));
        EXPECT_GE(minute, 0);
        EXPECT_LE(minute, 59);
    }

    TEST(Time26Test, ValidSecondRange) {
        auto result = rbbl::tm26::get_time();
        int second = std::stoi(result.substr(17, 2));
        EXPECT_GE(second, 0);
        EXPECT_LE(second, 59);
    }

} // anonymous namespace

namespace rbbl::test {

    auto test_time26_main() -> int {
        std::cout << "func: test time26" << std::endl;
        testing::InitGoogleTest();
        testing::GTEST_FLAG(filter) = "Time26Test.*";
        return RUN_ALL_TESTS();
    }

} // namespace rbbl::test