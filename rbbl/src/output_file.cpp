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
                M_OFS->flush(); // Write remaining items
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

#if defined(UNLOCK_ATOMIC_THREAD_MODE)
#else
    auto OutputFile::lite_output(const rbbl::type::str &logline) -> void {
        std::lock_guard<std::mutex> lock(M_MTX_OUTPUT_FILE);
        (*M_OFS) << logline << std::endl;
    }

    auto OutputFile::optimized_output(const rbbl::type::str &logline) -> void {
        std::lock_guard<std::mutex> lock(M_MTX_OUTPUT_FILE);
        (*M_OFS) << logline;
        m_write_item_count++;
        if (m_write_item_count >= m_param.write_item) {
            m_write_item_count = 0;
            M_OFS->flush();
        }
    }

    auto OutputFile::rapid_output(const rbbl::type::str &logline) -> void {
        // Null todo !
    }
#endif

    auto OutputFile::output(const rbbl::type::str &logline) -> void {
        if (nullptr == M_OFS) {
            std::osyncstream(std::cerr) << "Error: OutputFile::output: M_OFS is nullptr !" << std::endl;
            return;
        }

#if defined(UNLOCK_ATOMIC_THREAD_MODE)
#else
        if (m_param.optimize) {
            optimized_output(logline);
        } else {
            lite_output(logline);
        }
#endif
    }

} // namespace rbbl::ott
