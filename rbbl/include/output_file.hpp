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

#if defined(UNLOCK_ATOMIC_THREAD_MODE)
#else
#include <mutex>
#endif

namespace rbbl::ott {

    struct OutputFileClassFunctionParameter {
        type::str fname;
        type::str fpath;
        bool optimize{false};
        int write_item{12};
    };

    class OutputFile : public Output {
      private:
        OutputFileClassFunctionParameter m_param;

#if defined(UNLOCK_ATOMIC_THREAD_MODE)
#else
        std::mutex M_MTX_OUTPUT_FILE;
#endif
        std::unique_ptr<std::ofstream> M_OFS;
        int m_write_item_count{0};

      private:
#if defined(UNLOCK_ATOMIC_THREAD_MODE)
#else
        auto lite_output(const type::str &logline) -> void;
        auto optimized_output(const type::str &logline) -> void;
        auto rapid_output(const type::str &logline) -> void;
#endif

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
