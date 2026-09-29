// Author: ohmycode-cn
// Email: ohcode@163.com
// Date: 2026-09-28
// License: MIT
// Copyright: (c) 2026 ohmycode-cn, all rights reserved.

#pragma once
#ifndef RBBL_OUTPUT_CONSOLE_HPP
#define RBBL_OUTPUT_CONSOLE_HPP

#include "output.hpp"
#include <mutex>

namespace rbbl::ott {

    class OutputConsole : public Output {
      private:
        std::mutex M_MTX_OUTPUT_CONSOLE;

      public:
        auto output(const type::str &logline) -> void override;
        ~OutputConsole() override = default;
    };

} // namespace rbbl::ott

#endif // RBBL_OUTPUT_CONSOLE_HPP
