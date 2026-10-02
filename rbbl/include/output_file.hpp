// Author: ohmycode-cn
// Email: ohcode@163.com
// Date: 2026-09-28
// License: MIT
// Copyright: (c) 2026 ohmycode-cn, all rights reserved.

#pragma once
#ifndef RBBL_OUTPUT_FILE_HPP
#define RBBL_OUTPUT_FILE_HPP

#include "output.hpp"
#include "type.hpp"

#include <fstream>
#include <memory>

#if defined(USE_ATOMIC_THREAD_SPINLOCK_MODE)
#include <atomic>
#else
#include <mutex>
#endif

namespace rbbl::ott {

    enum class OutputFileOptimizeMode {
        LIGHTWEIGHT = 0,
        OPTIMIZED,
        QUICK,
        RAPID
    };

    struct OutputFileClassFunctionParameter {
        type::str fname;
        type::str fpath;
        bool optimize{false};
        OutputFileOptimizeMode optimize_mode{OutputFileOptimizeMode::LIGHTWEIGHT};
        int write_item{12};
    };

    class OutputFile : public Output {
      private:
        static constexpr int M_WRITE_ITEM_COUNT_LIMIT{32};
        OutputFileClassFunctionParameter m_param;

#if defined(USE_ATOMIC_THREAD_SPINLOCK_MODE)
        std::atomic_flag m_atomicf{ATOMIC_FLAG_INIT};
#else
        std::mutex M_MTX_OUTPUT_FILE;
#endif
        std::unique_ptr<std::ofstream> M_OFS;
        int m_write_item_count{0};

      private:
        auto flush_output(const int limit) -> void;
#if defined(USE_ATOMIC_THREAD_SPINLOCK_MODE)
      private:
        auto spinlock() -> void;   // Spinlock for atomic thread mode
        auto spinunlock() -> void; // Spinunlock for atomic thread mode
#endif
        auto lightweight_output(const type::str &logline) -> void;
        auto optimized_output(const type::str &logline) -> void;
        auto quick_output(const type::str &logline) -> void;
        auto rapid_output(const type::str &logline) -> void;

      public:
        auto output(const type::str &logline) -> void override;
        OutputFile() = default;
        ~OutputFile() override;

      private:
        auto ofile() -> bool;
        auto cfile() -> bool;

      public:
        auto set_param(const OutputFileClassFunctionParameter &param) -> void;
        auto init(const type::str &fpath, const type::str &fname) -> bool;
    };

} // namespace rbbl::ott

#endif // RBBL_OUTPUT_FILE_HPP
