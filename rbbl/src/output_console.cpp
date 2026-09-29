// Author: ohmycode-cn
// Email: ohcode@163.com
// Date: 2026-09-28
// License: MIT
// Copyright: (c) 2026 ohmycode-cn, all rights reserved.

#include "output_console.hpp"
#include <iostream>
#include <syncstream>

namespace rbbl::ott {

    auto OutputConsole::output(const type::str &logline) -> void {
        std::lock_guard<std::mutex> lock(M_MTX_OUTPUT_CONSOLE);
        std::osyncstream(std::cout) << logline << std::endl;
    }

} // namespace rbbl::ott
