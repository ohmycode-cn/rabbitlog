// Date Time: 2026-09-27-00-30-00
// Author: ohmycode-cn
// Email: ohcode@163.com
// Copyright (c) ohmycode-cn. All rights reserved.
// License: MIT

#include "test_output_file.hpp"

#include <gtest/gtest.h>
#include "format_text.hpp"
#include "format_json.hpp"
#include "format_xml.hpp"
#include "strmaps.hpp"
#include "output_file.hpp"
#include "time26.hpp"

#include <fstream>
#include <string>
#include <thread>
#include <vector>

namespace {

    using rbbl::type::str;
    using rbbl::type::smp;

    const str OUTPUT_DIR = "/home/zhh/Engineering/rabbitlog/test/google/output";

    auto get_map() -> smp {
        return rbbl::get_token_map(false);
    }

    auto clear_file(const str &path) -> void {
        std::ofstream ofs(path, std::ios::out | std::ios::trunc);
    }

    auto read_file(const str &path) -> str {
        std::ifstream ifs(path);
        if (!ifs.is_open()) {
            return "";
        }
        return {std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>()};
    }

    auto count_occurrences(const str &content, const str &needle) -> int {
        int count = 0;
        size_t pos = 0;
        while ((pos = content.find(needle, pos)) != str::npos) {
            ++count;
            pos += needle.size();
        }
        return count;
    }

    // Single-thread output

    TEST(OutputFileTest, TextOutput) {
        const str fname = "test_text.log";
        const str fpath = OUTPUT_DIR;
        clear_file(fpath + "/" + fname);

        rbbl::ott::OutputFile of;
        EXPECT_TRUE(of.init(fpath, fname));

        rbbl::fmt::FormatText text;
        rbbl::fmt::FormatArgs param{
            .time = rbbl::tm26::get_time(),
            .level = "INFO",
            .message = "Text output test",
            .token = get_map(),
            .file = "test_output_file.cpp",
            .line = 10,
        };
        of.output(text.format(param));

        param.level = "ERROR";
        param.message = "Something went wrong";
        param.line = 25;
        of.output(text.format(param));

        auto content = read_file(fpath + "/" + fname);
        EXPECT_FALSE(content.empty());
        EXPECT_NE(content.find("Text output test"), std::string::npos);
        EXPECT_NE(content.find("ERROR"), std::string::npos);
        std::cout << "\n===== TEXT -> " << fname << " =====\n"
                  << content << std::endl;
    }

    TEST(OutputFileTest, JsonOutput) {
        const str fname = "test_json.log";
        const str fpath = OUTPUT_DIR;
        clear_file(fpath + "/" + fname);

        rbbl::ott::OutputFile of;
        EXPECT_TRUE(of.init(fpath, fname));

        rbbl::fmt::FormatJson json;
        rbbl::fmt::FormatArgs param{
            .time = rbbl::tm26::get_time(),
            .level = "DEBUG",
            .message = "Json output test",
            .token = get_map(),
            .file = "test_output_file.cpp",
            .line = 77,
        };
        of.output(json.format(param));

        auto content = read_file(fpath + "/" + fname);
        EXPECT_FALSE(content.empty());
        EXPECT_NE(content.find("{"), std::string::npos);
        EXPECT_NE(content.find("Json output test"), std::string::npos);
        std::cout << "\n===== JSON -> " << fname << " =====\n"
                  << content << std::endl;
    }

    TEST(OutputFileTest, XmlOutput) {
        const str fname = "test_xml.log";
        const str fpath = OUTPUT_DIR;
        clear_file(fpath + "/" + fname);

        rbbl::ott::OutputFile of;
        EXPECT_TRUE(of.init(fpath, fname));

        rbbl::fmt::FormatXml xml;
        rbbl::fmt::FormatArgs param{
            .time = rbbl::tm26::get_time(),
            .level = "INFO",
            .message = "Xml output test",
            .token = get_map(),
            .file = "test_output_file.cpp",
            .line = 110,
        };
        of.output(xml.format(param));

        auto content = read_file(fpath + "/" + fname);
        EXPECT_FALSE(content.empty());
        EXPECT_NE(content.find("<record>"), std::string::npos);
        EXPECT_NE(content.find("Xml output test"), std::string::npos);
        std::cout << "\n===== XML -> " << fname << " =====\n"
                  << content << std::endl;
    }

    // Multi-thread output

    TEST(OutputFileTest, MultiThreadTextOutput) {
        const str fname = "test_mt_text.log";
        const str fpath = OUTPUT_DIR;
        clear_file(fpath + "/" + fname);

        rbbl::ott::OutputFile of;
        EXPECT_TRUE(of.init(fpath, fname));

        constexpr int THREAD_COUNT = 8;
        constexpr int LINES_PER_THREAD = 20;

        auto worker = [&of](int thread_id) {
            rbbl::fmt::FormatText text;
            auto map = get_map();
            for (int i = 0; i < LINES_PER_THREAD; ++i) {
                rbbl::fmt::FormatArgs param{
            .time = rbbl::tm26::get_time(),
            .level = "INFO",
            .message = "thread=" + std::to_string(thread_id) + " line=" + std::to_string(i),
            .token = map,
            .file = "test_output_file.cpp",
            .line = i,
                };
                of.output(text.format(param));
            }
        };

        std::vector<std::thread> threads;
        threads.reserve(THREAD_COUNT);
        for (int t = 0; t < THREAD_COUNT; ++t) {
            threads.emplace_back(worker, t);
        }
        for (auto &th : threads) {
            th.join();
        }

        auto content = read_file(fpath + "/" + fname);
        EXPECT_FALSE(content.empty());
        auto entries = count_occurrences(content, "thread=");
        EXPECT_EQ(entries, THREAD_COUNT * LINES_PER_THREAD);
        std::cout << "\n===== MULTI-THREAD TEXT -> " << fname
                  << " (" << entries << " entries) =====\n"
                  << std::endl;
    }

    TEST(OutputFileTest, MultiThreadJsonOutput) {
        const str fname = "test_mt_json.log";
        const str fpath = OUTPUT_DIR;
        clear_file(fpath + "/" + fname);

        rbbl::ott::OutputFile of;
        EXPECT_TRUE(of.init(fpath, fname));

        constexpr int THREAD_COUNT = 8;
        constexpr int LINES_PER_THREAD = 20;

        auto worker = [&of](int thread_id) {
            rbbl::fmt::FormatJson json;
            auto map = get_map();
            for (int i = 0; i < LINES_PER_THREAD; ++i) {
                rbbl::fmt::FormatArgs param{
            .time = rbbl::tm26::get_time(),
            .level = "DEBUG",
            .message = "thread=" + std::to_string(thread_id) + " line=" + std::to_string(i),
            .token = map,
            .file = "test_output_file.cpp",
            .line = i,
                };
                of.output(json.format(param));
            }
        };

        std::vector<std::thread> threads;
        threads.reserve(THREAD_COUNT);
        for (int t = 0; t < THREAD_COUNT; ++t) {
            threads.emplace_back(worker, t);
        }
        for (auto &th : threads) {
            th.join();
        }

        auto content = read_file(fpath + "/" + fname);
        EXPECT_FALSE(content.empty());
        auto entries = count_occurrences(content, "thread=");
        EXPECT_EQ(entries, THREAD_COUNT * LINES_PER_THREAD);
        std::cout << "\n===== MULTI-THREAD JSON -> " << fname
                  << " (" << entries << " entries) =====\n"
                  << std::endl;
    }

    TEST(OutputFileTest, MultiThreadXmlOutput) {
        const str fname = "test_mt_xml.log";
        const str fpath = OUTPUT_DIR;
        clear_file(fpath + "/" + fname);

        rbbl::ott::OutputFile of;
        EXPECT_TRUE(of.init(fpath, fname));

        constexpr int THREAD_COUNT = 8;
        constexpr int LINES_PER_THREAD = 20;

        auto worker = [&of](int thread_id) {
            rbbl::fmt::FormatXml xml;
            auto map = get_map();
            for (int i = 0; i < LINES_PER_THREAD; ++i) {
                rbbl::fmt::FormatArgs param{
            .time = rbbl::tm26::get_time(),
            .level = "INFO",
            .message = "thread=" + std::to_string(thread_id) + " line=" + std::to_string(i),
            .token = map,
            .file = "test_output_file.cpp",
            .line = i,
                };
                of.output(xml.format(param));
            }
        };

        std::vector<std::thread> threads;
        threads.reserve(THREAD_COUNT);
        for (int t = 0; t < THREAD_COUNT; ++t) {
            threads.emplace_back(worker, t);
        }
        for (auto &th : threads) {
            th.join();
        }

        auto content = read_file(fpath + "/" + fname);
        EXPECT_FALSE(content.empty());
        auto entries = count_occurrences(content, "thread=");
        EXPECT_EQ(entries, THREAD_COUNT * LINES_PER_THREAD);
        std::cout << "\n===== MULTI-THREAD XML -> " << fname
                  << " (" << entries << " entries) =====\n"
                  << std::endl;
    }

} // anonymous namespace

namespace rbbl::test {

    auto test_output_file_main() -> int {
        std::cout << "func: test output file" << std::endl;
        testing::InitGoogleTest();
        return RUN_ALL_TESTS();
    }

} // namespace rbbl::test