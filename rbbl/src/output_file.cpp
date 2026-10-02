// Author: ohmycode-cn
// Email: ohcode@163.com
// Date: 2026-09-28
// License: MIT
// Copyright: (c) 2026 ohmycode-cn, all rights reserved.

#include "output_file.hpp"
#include <filesystem>
#include <iostream>
#include <syncstream>

namespace rbbl::ott {

    OutputFile::~OutputFile() {
        cfile();
    }

    auto OutputFile::ofile() -> bool {
        auto &f{m_param.fname};
        auto &p{m_param.fpath};
        auto fp = std::filesystem::path(p) / f;
        M_OFS = std::make_unique<std::ofstream>(fp, std::ios::out | std::ios::app | std::ios::binary);
        if (!M_OFS->is_open()) {
            return false;
        }
        return true;
    }

    auto OutputFile::cfile() -> bool {
        if (nullptr == M_OFS) {
            return true;
        }
        if (!M_OFS->is_open()) {

            // unsafe ! ! !
            if (m_write_item_count > 0) {
                M_OFS->flush(); // Write remaining items if not flushed yet
            }

            return true;
        }

        M_OFS->close();
        return true;
    }

    auto OutputFile::set_param(const OutputFileClassFunctionParameter &param) -> void {
        m_param = param;
    }

    auto OutputFile::init(const rbbl::type::str &fpath, const rbbl::type::str &fname) -> bool {
        m_param.fpath = fpath;
        m_param.fname = fname;
        return ofile();
    }

    auto OutputFile::flush_output(const int limit) -> void {
        if (m_write_item_count++; m_write_item_count >= limit) {
            m_write_item_count = 0;
            M_OFS->flush();
        }
    }

#if defined(USE_ATOMIC_THREAD_SPINLOCK_MODE)
    auto OutputFile::spinlock() -> void {
        while (m_atomicf.test_and_set(std::memory_order_acquire))
            ; // Spin until the lock is acquired
    }

    auto OutputFile::spinunlock() -> void {
        m_atomicf.clear(std::memory_order_release); // Release the lock
    }
#endif

    auto OutputFile::lightweight_output(const rbbl::type::str &logline) -> void {
#if defined(USE_ATOMIC_THREAD_SPINLOCK_MODE)
        spinlock();
        (*M_OFS) << logline << std::endl;
        spinunlock();
#else
        std::lock_guard<std::mutex> lock(M_MTX_OUTPUT_FILE);
        (*M_OFS) << logline << std::endl;
#endif
    }

    auto OutputFile::optimized_output(const rbbl::type::str &logline) -> void {
#if defined(USE_ATOMIC_THREAD_SPINLOCK_MODE)
        spinlock();
        (*M_OFS) << logline;
        spinunlock();
#else
        std::lock_guard<std::mutex> lock(M_MTX_OUTPUT_FILE);
        (*M_OFS) << logline;
#endif
        flush_output(m_param.write_item);
    }

    auto OutputFile::quick_output(const type::str &logline) -> void {
#if defined(USE_ATOMIC_THREAD_SPINLOCK_MODE)
        spinlock();
        (*M_OFS) << logline;
        spinunlock();
#else
        std::lock_guard<std::mutex> lock(M_MTX_OUTPUT_FILE);
        (*M_OFS) << logline;
#endif
        flush_output(M_WRITE_ITEM_COUNT_LIMIT);
    }

    auto OutputFile::rapid_output(const rbbl::type::str &logline) -> void {
        // Null todo !
    }

    auto OutputFile::output(const rbbl::type::str &logline) -> void {
        if (nullptr == M_OFS) {
            std::osyncstream(std::cerr) << "Error: OutputFile::output: M_OFS is nullptr !" << std::endl;
            return;
        }

        // Choose the output mode based on the optimization settings
        // Function: lightweight_output(...); unoptimized output !
        if (m_param.optimize) {
            switch (m_param.optimize_mode) {
            case OutputFileOptimizeMode::OPTIMIZED:
                optimized_output(logline);
                break;
            case OutputFileOptimizeMode::QUICK:
                quick_output(logline);
                break;
            case OutputFileOptimizeMode::RAPID:
                rapid_output(logline);
                break;
            default: // OutputFileOptimizeMode::LIGHTWEIGHT
                lightweight_output(logline);
                break;
            };
        } else {
            lightweight_output(logline);
        }
    }

} // namespace rbbl::ott
