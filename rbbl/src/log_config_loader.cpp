// Author: ohmycode-cn
// Email: ohcode@163.com
// Date: 2026-10-03
// License: MIT
// Copyright: (c) 2026 ohmycode-cn, all rights reserved.

#include "log_config_loader.hpp"
#include "log_config_parser.hpp"
#include <filesystem>
#include <fstream>
#include <sstream>

namespace rbbl::configuration {

    Loader::Loader(const rbbl::type::str &fpath, const rbbl::type::str &fname) {
        m_fpath = fpath;
        m_fname = fname;
    }

    Loader::~Loader() {
        m_strmp.clear();
    }

    auto Loader::call(bool &flag, bool (Loader::*func)()) -> void {
        if (!flag) {
            return;
        }
        if (!(this->*func)()) {
            flag = false;
        }
    }

    auto Loader::init() -> bool {
        /**
         * SAFETY:
         * @brief This function check user transform parameter (fpath, fname) whether valid.
         * @brief This function body content is cross-platform.
         */
        if (m_fpath.empty() || m_fname.empty()) {
            return false;
        }
        return std::filesystem::exists(std::filesystem::path(m_fpath) / m_fname);
    }

    auto Loader::load() -> bool {
        /**
         * SAFETY:
         * @brief This function load log file content to memory.
         * @brief This function body content is cross-platform.
         */
        std::ifstream file(std::filesystem::path(m_fpath) / m_fname, std::ios::binary);
        if (!file.is_open()) {
            return false;
        }
        std::stringstream ss;
        ss << file.rdbuf();
        file.close();

        { // _start:
            /**
             * SAFETY:
             * @brief LogConfigParser is scoped to this block and destroyed at the closing brace;
             * it must not outlive the call to parser().
             */
            LogConfigParser parser;
            m_strmp = parser.parser(ss);
        }; // _endof;

        return true;
    }

    auto Loader::getter() -> rbbl::type::smp {

        /**
         * SAFETY:
         * @brief This function use strict mode, if any member function failed, it will return empty map.
         * @return rbbl::type::smp -> std::unordered_map<std::string, std::string>
         */
        rbbl::type::smp map;
        bool local_flag{true};
        call(local_flag, &Loader::init);
        call(local_flag, &Loader::load);
        if (!local_flag) {
            return {};
        }

        return m_strmp;
    }

} // namespace rbbl::configuration
