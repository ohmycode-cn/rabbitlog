// Date Time: 2026-09-27-10-00-00
// Author: ohmycode-cn
// Email: ohcode@163.com
// Copyright (c) ohmycode-cn. All rights reserved.
// License: MIT

#include "test_output_file2.hpp"

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
    constexpr int THREAD_COUNT = 8;
    constexpr int ENTRY_WIDTH = 256;

    struct BenchmarkResult {
        rbbl::type::str label;
        long long target_bytes;
        long long bytes_written;
        long long entries_written;
        double seconds;
        double throughput_mbps;
    };

    std::vector<BenchmarkResult> g_results;

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

    auto format_entry(const rbbl::type::str &msg, int line) -> rbbl::type::str {
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

    auto run_single_thread(const rbbl::type::str &fname, long long target) -> BenchmarkResult {
        const rbbl::type::str fullpath = OUTPUT_DIR + "/" + fname;
        clear_file(fullpath);

        rbbl::ott::OutputFile of;
        of.init(OUTPUT_DIR, fname);

        auto entry = format_entry("benchmark single-thread", 1);

        auto t0 = std::chrono::steady_clock::now();
        long long total = 0;
        long long count = 0;
        while (total < target) {
            of.output(entry);
            total += static_cast<long long>(entry.size());
            ++count;
        }
        auto t1 = std::chrono::steady_clock::now();

        BenchmarkResult r{};
        r.target_bytes = target;
        r.bytes_written = total;
        r.entries_written = count;
        r.seconds = std::chrono::duration<double>(t1 - t0).count();
        r.throughput_mbps = (static_cast<double>(total) / (1024.0 * 1024.0)) / r.seconds;
        return r;
    }

    auto run_multi_thread(const rbbl::type::str &fname, long long target) -> BenchmarkResult {
        const rbbl::type::str fullpath = OUTPUT_DIR + "/" + fname;
        clear_file(fullpath);

        rbbl::ott::OutputFile of;
        of.init(OUTPUT_DIR, fname);

        const long long per_thread = target / THREAD_COUNT;

        auto t0 = std::chrono::steady_clock::now();

        std::vector<std::thread> threads;
        threads.reserve(THREAD_COUNT);
        for (int t = 0; t < THREAD_COUNT; ++t) {
            threads.emplace_back([&of, per_thread](int tid) {
                auto entry = format_entry("benchmark multi-thread tid=" + std::to_string(tid), tid);
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

        auto actual = file_size(fullpath);
        BenchmarkResult r{};
        r.target_bytes = target;
        r.bytes_written = actual;
        r.entries_written = actual / ENTRY_WIDTH;
        r.seconds = std::chrono::duration<double>(t1 - t0).count();
        r.throughput_mbps = (static_cast<double>(actual) / (1024.0 * 1024.0)) / r.seconds;
        return r;
    }

    auto size_label(long long bytes) -> rbbl::type::str {
        if (bytes >= 1024LL * 1024 * 1024) {
            return std::to_string(bytes / (1024LL * 1024 * 1024)) + "GB";
        }
        return std::to_string(bytes / (1024LL * 1024)) + "MB";
    }

    auto print_result(const BenchmarkResult &r) -> void {
        std::cout << std::fixed << std::setprecision(2);
        std::cout << "  " << std::left << std::setw(40) << r.label
                  << std::right << std::setw(10) << r.seconds << " s   "
                  << std::setw(10) << r.throughput_mbps << " MB/s   "
                  << r.entries_written << " entries\n";
    }

    auto run_benchmark(const rbbl::type::str &size_str, long long target) -> void {
        BenchmarkResult st = run_single_thread("bench_st_" + size_str + ".log", target);
        st.label = "Single-thread (" + size_str + ")";
        g_results.push_back(st);
        print_result(st);

        BenchmarkResult mt = run_multi_thread("bench_mt_" + size_str + ".log", target);
        mt.label = "Multi-thread x" + std::to_string(THREAD_COUNT) + " (" + size_str + ")";
        g_results.push_back(mt);
        print_result(mt);
    }

    TEST(OutputFileBenchmark, RunAll) {
        std::cout << "\n===== BENCHMARK: 32MB / 64MB / 128MB / 2GB =====\n\n";

        run_benchmark("32mb", 32LL * 1024 * 1024);
        run_benchmark("64mb", 64LL * 1024 * 1024);
        run_benchmark("128mb", 128LL * 1024 * 1024);
        run_benchmark("2gb", 2LL * 1024 * 1024 * 1024);

        std::cout << "\n===== SUMMARY =====\n\n";
        std::cout << std::left << std::setw(44) << "  Mode"
                  << std::right << std::setw(10) << "Time"
                  << "   " << std::setw(10) << "Throughput"
                  << "   Entries\n";
        std::cout << "  " << std::string(80, '-') << "\n";
        for (const auto &r : g_results) {
            print_result(r);
        }
        std::cout << std::endl;
    }

} // anonymous namespace

namespace rbbl::test {

    auto test_output_file2_main() -> int {
        std::cout << "func: benchmark output file" << std::endl;
        testing::InitGoogleTest();
        return RUN_ALL_TESTS();
    }

} // namespace rbbl::test