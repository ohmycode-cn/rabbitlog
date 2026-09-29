// Author: ohmycode-cn
// Email: ohcode@163.com
// Date: 2026-09-28
// License: MIT
// Copyright: (c) 2026 ohmycode-cn, all rights reserved.

#pragma once
#ifndef RBBL_FORMAT_HPP
#define RBBL_FORMAT_HPP

#include "type.hpp"

namespace rbbl::fmt {

    struct FormatArgs {
        type::str time;
        type::str level;
        type::str message;
        type::smp token;
        type::str file;
        int line;
    };

    class Format {
      public:
        virtual auto format(const FormatArgs &parma) -> type::str = 0;
        virtual ~Format() = default;
    };

} // namespace rbbl::fmt

#endif // RBBL_FORMAT_HPP
