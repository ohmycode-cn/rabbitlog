// Date Time: 2026-09-27-00-10-00
// Author: ohmycode-cn
// Email: ohcode@163.com
// Copyright (c) ohmycode-cn. All rights reserved.
// License: MIT

#include "preview_format_output.hpp"

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

    TEST(PreviewFormatOutput, TextNormal) {
        logsys::FormatText text;
        logsys::FormatArgs param{
            .time = "2026-09-27-00-10-00",
            .level = "INFO",
            .message = "Application started successfully",
            .token = get_normal_map(),
            .file = "main.cpp",
            .line = 42,
        };
        auto result = text.format(param);
        std::cout << "\n===== TEXT (normal) =====\n"
                  << result << "\n"
                  << std::endl;
        EXPECT_FALSE(result.empty());
    }

    TEST(PreviewFormatOutput, TextHighlight) {
        logsys::FormatText text;
        logsys::FormatArgs param{
            .time = "2026-09-27-00-10-00",
            .level = "ERROR",
            .message = "Failed to open config file",
            .token = get_highlight_map(),
            .file = "config.cpp",
            .line = 128,
        };
        auto result = text.format(param);
        std::cout << "\n===== TEXT (highlight) =====\n"
                  << result << "\n"
                  << std::endl;
        EXPECT_FALSE(result.empty());
    }

    TEST(PreviewFormatOutput, JsonNormal) {
        logsys::FormatJson json;
        logsys::FormatArgs param{
            .time = "2026-09-27-00-10-00",
            .level = "DEBUG",
            .message = "Loading module: network",
            .token = get_normal_map(),
            .file = "loader.cpp",
            .line = 56,
        };
        auto result = json.format(param);
        std::cout << "\n===== JSON (normal) =====\n"
                  << result << "\n"
                  << std::endl;
        EXPECT_FALSE(result.empty());
    }

    TEST(PreviewFormatOutput, JsonHighlight) {
        logsys::FormatJson json;
        logsys::FormatArgs param{
            .time = "2026-09-27-00-10-00",
            .level = "WARNING",
            .message = "Deprecated API call detected",
            .token = get_highlight_map(),
            .file = "api.cpp",
            .line = 200,
        };
        auto result = json.format(param);
        std::cout << "\n===== JSON (highlight) =====\n"
                  << result << "\n"
                  << std::endl;
        EXPECT_FALSE(result.empty());
    }

    TEST(PreviewFormatOutput, XmlNormal) {
        logsys::FormatXml xml;
        logsys::FormatArgs param{
            .time = "2026-09-27-00-10-00",
            .level = "FATAL",
            .message = "Out of memory",
            .token = get_normal_map(),
            .file = "allocator.cpp",
            .line = 1024,
        };
        auto result = xml.format(param);
        std::cout << "\n===== XML (normal) =====\n"
                  << result << "\n"
                  << std::endl;
        EXPECT_FALSE(result.empty());
    }

    TEST(PreviewFormatOutput, XmlHighlight) {
        logsys::FormatXml xml;
        logsys::FormatArgs param{
            .time = "2026-09-27-00-10-00",
            .level = "WARNING",
            .message = "Connection timeout, retrying...",
            .token = get_highlight_map(),
            .file = "network.cpp",
            .line = 88,
        };
        auto result = xml.format(param);
        std::cout << "\n===== XML (highlight) =====\n"
                  << result << "\n"
                  << std::endl;
        EXPECT_FALSE(result.empty());
    }

} // anonymous namespace

namespace rbbl::test {

    auto preview_format_output_main() -> int {
        std::cout << "func: preview format output" << std::endl;
        testing::InitGoogleTest();
        testing::GTEST_FLAG(filter) = "PreviewFormatOutput.*";
        return RUN_ALL_TESTS();
    }

} // namespace rbbl::test