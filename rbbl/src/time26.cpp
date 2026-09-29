// Author: ohmycode-cn
// Email: ohcode@163.com
// Date: 2026-09-29
// License: MIT
// Copyright: (c) 2026 ohmycode-cn, all rights reserved.

#include "time26.hpp"
#include <chrono>
#include <format>

namespace rbbl::tm26 {

    /**
     * @brief Generates a formatted local-time string in C++26 chrono style.
     *
     * @return Formatted timestamp string in "YYYY-MM-DD-HH-MM-SS" format.
     */
    auto get_time() -> type::str {
        auto now = std::chrono::floor<std::chrono::seconds>(
            std::chrono::system_clock::now());
        auto ltm = std::chrono::current_zone()->to_local(now);
        return std::format("{:%Y-%m-%d-%H-%M-%S}", ltm);
    }

} // namespace rbbl::tm26
