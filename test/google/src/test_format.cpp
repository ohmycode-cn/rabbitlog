// Date Time: 2026-09-27-00-00-00
// Author: ohmycode-cn
// Email: ohcode@163.com
// Copyright (c) ohmycode-cn. All rights reserved.
// License: MIT

#include "test_format.hpp"

#include <gtest/gtest.h>
#include "format_text.hpp"
#include "format_xml.hpp"
#include "format_json.hpp"
#include "strmaps.hpp"

namespace {

    namespace logsys = rbbl::fmt;

    auto get_normal_map() -> rbbl::type::smp {
        return rbbl::get_token_map(false);
    }

    auto get_highlight_map() -> rbbl::type::smp {
        return rbbl::get_token_map(true);
    }

    // FormatText

    TEST(FormatTextTest, NonEmpty) {
        logsys::FormatText text;
        logsys::FormatArgs param{
            .time = "2026-09-27-00-00-00",
            .level = "INFO",
            .message = "test message",
            .token = get_normal_map(),
            .file = "test.cpp",
            .line = 42,
        };
        auto result = text.format(param);
        EXPECT_FALSE(result.empty());
    }

    TEST(FormatTextTest, ContainsTimestamp) {
        logsys::FormatText text;
        logsys::FormatArgs param{
            .time = "2026-09-27-00-00-00",
            .level = "DEBUG",
            .message = "hello",
            .token = get_normal_map(),
            .file = "main.cpp",
            .line = 1,
        };
        auto result = text.format(param);
        EXPECT_NE(result.find("2026-09-27-00-00-00"), std::string::npos);
    }

    TEST(FormatTextTest, ContainsMessage) {
        logsys::FormatText text;
        logsys::FormatArgs param{
            .time = "t",
            .level = "INFO",
            .message = "unique_payload_12345",
            .token = get_normal_map(),
            .file = "f.cpp",
            .line = 1,
        };
        auto result = text.format(param);
        EXPECT_NE(result.find("unique_payload_12345"), std::string::npos);
    }

    TEST(FormatTextTest, AllLevels) {
        logsys::FormatText text;
        const char *levels[] = {"DEBUG", "INFO", "WARNING", "ERROR", "FATAL"};
        for (int i = 0; i < 5; ++i) {
            logsys::FormatArgs param{
                .time = "t",
                .level = levels[i],
                .message = "msg",
                .token = get_normal_map(),
                .file = "f.cpp",
                .line = i,
            };
            auto result = text.format(param);
            EXPECT_FALSE(result.empty()) << "Level " << levels[i] << " produced empty output";
        }
    }

    // FormatXml

    TEST(FormatXmlTest, NonEmpty) {
        logsys::FormatXml xml;
        logsys::FormatArgs param{
            .time = "2026-09-27-00-00-00",
            .level = "ERROR",
            .message = "test message",
            .token = get_highlight_map(),
            .file = "test.cpp",
            .line = 99,
        };
        auto result = xml.format(param);
        EXPECT_FALSE(result.empty());
    }

    TEST(FormatXmlTest, ContainsRecordTag) {
        logsys::FormatXml xml;
        logsys::FormatArgs param{
            .time = "t",
            .level = "INFO",
            .message = "msg",
            .token = get_highlight_map(),
            .file = "f.cpp",
            .line = 1,
        };
        auto result = xml.format(param);
        EXPECT_NE(result.find("record"), std::string::npos);
    }

    TEST(FormatXmlTest, AllLevels) {
        logsys::FormatXml xml;
        const char *levels[] = {"DEBUG", "INFO", "WARNING", "ERROR", "FATAL"};
        for (int i = 0; i < 5; ++i) {
            logsys::FormatArgs param{
                .time = "t",
                .level = levels[i],
                .message = "msg",
                .token = get_highlight_map(),
                .file = "f.cpp",
                .line = i,
            };
            auto result = xml.format(param);
            EXPECT_FALSE(result.empty()) << "Level " << levels[i] << " produced empty output";
        }
    }

    // FormatJson

    TEST(FormatJsonTest, NonEmpty) {
        logsys::FormatJson json;
        logsys::FormatArgs param{
            .time = "2026-09-27-00-00-00",
            .level = "DEBUG",
            .message = "test message",
            .token = get_highlight_map(),
            .file = "test.cpp",
            .line = 55,
        };
        auto result = json.format(param);
        EXPECT_FALSE(result.empty());
    }

    TEST(FormatJsonTest, ContainsBrace) {
        logsys::FormatJson json;
        logsys::FormatArgs param{
            .time = "t",
            .level = "INFO",
            .message = "msg",
            .token = get_highlight_map(),
            .file = "f.cpp",
            .line = 1,
        };
        auto result = json.format(param);
        EXPECT_NE(result.find("{"), std::string::npos);
        EXPECT_NE(result.find("}"), std::string::npos);
    }

    TEST(FormatJsonTest, AllLevels) {
        logsys::FormatJson json;
        const char *levels[] = {"DEBUG", "INFO", "WARNING", "ERROR", "FATAL"};
        for (int i = 0; i < 5; ++i) {
            logsys::FormatArgs param{
                .time = "t",
                .level = levels[i],
                .message = "msg",
                .token = get_highlight_map(),
                .file = "f.cpp",
                .line = i,
            };
            auto result = json.format(param);
            EXPECT_FALSE(result.empty()) << "Level " << levels[i] << " produced empty output";
        }
    }

    // Cross-format

    TEST(CrossFormatTest, DifferentFormatsDifferentOutput) {
        logsys::FormatArgs param{
            .time = "t",
            .level = "INFO",
            .message = "msg",
            .token = get_normal_map(),
            .file = "f.cpp",
            .line = 1,
        };
        logsys::FormatText text;
        logsys::FormatXml xml;
        logsys::FormatJson json;
        auto t = text.format(param);
        param.token = get_highlight_map();
        auto x = xml.format(param);
        auto j = json.format(param);
        EXPECT_NE(t, x);
        EXPECT_NE(t, j);
        EXPECT_NE(x, j);
    }

} // anonymous namespace

namespace rbbl::test {

    auto test_format_main() -> int {
        std::cout << "func: test format" << std::endl;
        testing::InitGoogleTest();
        testing::GTEST_FLAG(filter) = "FormatTextTest.*:FormatXmlTest.*:FormatJsonTest.*:CrossFormatTest.*";
        return RUN_ALL_TESTS();
    }

} // namespace rbbl::test