// Date Time: 2026-09-27-10-30-00
// Author: ohmycode-cn
// Email: ohcode@163.com
// Copyright (c) ohmycode-cn. All rights reserved.
// License: MIT

#include "test_output_file3.hpp"

#include <gtest/gtest.h>
#include "format_text.hpp"
#include "strmaps.hpp"
#include "output_file.hpp"
#include "time26.hpp"

#include <chrono>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

namespace {

    namespace fs = std::filesystem;

    const rbbl::type::str OUTPUT_DIR = "/home/zhh/Engineering/rabbitlog/test/google/output";
    constexpr int ENTRY_WIDTH = 256;
    constexpr int THREAD_COUNT = 8;

    struct BenchResult {
        rbbl::type::str label;
        long long bytes;
        long long entries;
        double seconds;
        double mbps;
    };

    std::vector<BenchResult> g_results;

    auto get_map() -> rbbl::type::smp {
        return rbbl::get_token_map(false);
    }

    auto clear_file(const rbbl::type::str &path) -> void {
        std::ofstream ofs(path, std::ios::out | std::ios::trunc);
    }

    auto file_size(const rbbl::type::str &path) -> long long {
        std::error_code ec;
        auto sz = fs::file_size(path, ec);
        return ec ? 0 : static_cast<long long>(sz);
    }

    auto make_entry(const rbbl::type::str &msg, int line) -> rbbl::type::str {
        rbbl::fmt::FormatText text;
        rbbl::fmt::FormatArgs param{
            .time = rbbl::tm26::get_time(),
            .level = "INFO",
            .message = msg,
            .token = get_map(),
            .file = "benchmark.cpp",
            .line = line,
        };
        auto s = text.format(param);
        if (static_cast<int>(s.size()) < ENTRY_WIDTH) {
            s.append(ENTRY_WIDTH - s.size(), ' ');
        }
        s.append(1, '\n');
        return s;
    }

    auto print_row(const BenchResult &r) -> void {
        std::cout << std::fixed << std::setprecision(2);
        std::cout << "  " << std::left << std::setw(44) << r.label
                  << std::right << std::setw(10) << r.seconds << " s   "
                  << std::setw(10) << r.mbps << " MB/s   "
                  << r.entries << " entries\n";
    }

    auto run_single(const rbbl::type::str &tag, long long target, bool optimize, int write_item) -> BenchResult {
        const rbbl::type::str fname = "bench3_st_" + tag + ".log";
        const rbbl::type::str fullpath = OUTPUT_DIR + "/" + fname;
        clear_file(fullpath);

        long long count = 0;
        double elapsed = 0;

        {
            rbbl::ott::OutputFile of;
            of.set_param({.optimize = optimize, .write_item = write_item});
            of.init(OUTPUT_DIR, fname);

            auto entry = make_entry("bench3 single " + tag, 1);

            auto t0 = std::chrono::steady_clock::now();
            long long total = 0;
            while (total < target) {
                of.output(entry);
                total += static_cast<long long>(entry.size());
                ++count;
            }
            auto t1 = std::chrono::steady_clock::now();
            elapsed = std::chrono::duration<double>(t1 - t0).count();
        } // destructor flushes remaining entries

        auto actual = file_size(fullpath);
        BenchResult r{};
        r.bytes = actual;
        r.entries = count;
        r.seconds = elapsed;
        r.mbps = (static_cast<double>(actual) / (1024.0 * 1024.0)) / elapsed;
        return r;
    }

    auto run_multi(const rbbl::type::str &tag, long long target, bool optimize, int write_item) -> BenchResult {
        const rbbl::type::str fname = "bench3_mt_" + tag + ".log";
        const rbbl::type::str fullpath = OUTPUT_DIR + "/" + fname;
        clear_file(fullpath);

        double elapsed = 0;

        {
            rbbl::ott::OutputFile of;
            of.set_param({.optimize = optimize, .write_item = write_item});
            of.init(OUTPUT_DIR, fname);

            const long long per_thread = target / THREAD_COUNT;

            auto t0 = std::chrono::steady_clock::now();

            std::vector<std::thread> threads;
            threads.reserve(THREAD_COUNT);
            for (int t = 0; t < THREAD_COUNT; ++t) {
                threads.emplace_back([&of, per_thread](int tid) {
                    auto entry = make_entry("bench3 mt tid=" + std::to_string(tid), tid);
                    long long total = 0;
                    while (total < per_thread) {
                        of.output(entry);
                        total += static_cast<long long>(entry.size());
                    }
                }, t);
            }
            for (auto &th : threads) {
                th.join();
            }

            auto t1 = std::chrono::steady_clock::now();
            elapsed = std::chrono::duration<double>(t1 - t0).count();
        } // destructor flushes remaining entries

        auto actual = file_size(fullpath);
        BenchResult r{};
        r.bytes = actual;
        r.entries = actual / ENTRY_WIDTH;
        r.seconds = elapsed;
        r.mbps = (static_cast<double>(actual) / (1024.0 * 1024.0)) / elapsed;
        return r;
    }

    auto size_str(long long bytes) -> rbbl::type::str {
        return std::to_string(bytes / (1024LL * 1024)) + "MB";
    }

    auto run_suite(const rbbl::type::str &mode_label, long long target, bool optimize, int write_item) -> void {
        auto sz = size_str(target);
        auto tag = mode_label + "_" + sz;

        BenchResult st = run_single(tag, target, optimize, write_item);
        st.label = "ST " + mode_label + " (" + sz + ")";
        g_results.push_back(st);
        print_row(st);

        BenchResult mt = run_multi(tag, target, optimize, write_item);
        mt.label = "MT x" + std::to_string(THREAD_COUNT) + " " + mode_label + " (" + sz + ")";
        g_results.push_back(mt);
        print_row(mt);
    }

    TEST(OutputFile3Benchmark, RunAll) {
        std::cout << "\n===== BENCHMARK: lite vs optimized (write_item=12) vs optimized (write_item=64) =====\n\n";

        long long sizes[] = {32LL * 1024 * 1024, 64LL * 1024 * 1024, 128LL * 1024 * 1024};

        for (auto sz : sizes) {
            run_suite("lite", sz, false, 12);
            run_suite("opt12", sz, true, 12);
            run_suite("opt64", sz, true, 64);
            std::cout << "\n";
        }

        std::cout << "===== SUMMARY =====\n\n";
        std::cout << std::left << std::setw(48) << "  Mode"
                  << std::right << std::setw(10) << "Time"
                  << "   " << std::setw(10) << "Throughput"
                  << "   Entries\n";
        std::cout << "  " << std::string(90, '-') << "\n";
        for (const auto &r : g_results) {
            print_row(r);
        }
        std::cout << std::endl;
    }

} // anonymous namespace

namespace rbbl::test {

    auto test_output_file3_main() -> int {
        std::cout << "func: benchmark output file3 (lite vs optimized)" << std::endl;
        testing::InitGoogleTest();
        return RUN_ALL_TESTS();
    }

} // namespace rbbl::test