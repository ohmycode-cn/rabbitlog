// Author: ohmycode-cn
// Email: ohcode@163.com
// Date: 2026-09-28
// License: MIT
// Copyright: (c) 2026 ohmycode-cn, all rights reserved.

#pragma once
#ifndef RBBL_OUTPUT_HPP
#define RBBL_OUTPUT_HPP

#include "type.hpp"

namespace rbbl::ott {

    class Output {
      public:
        virtual auto output(const type::str &sline) -> void = 0;
        virtual ~Output() = default;
    };

} // namespace rbbl::ott

#endif // RBBL_OUTPUT_HPP
