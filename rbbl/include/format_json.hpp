// Author: ohmycode-cn
// Email: ohcode@163.com
// Date: 2026-09-28
// License: MIT
// Copyright: (c) 2026 ohmycode-cn, all rights reserved.

#pragma once
#ifndef RBBL_FORMAT_JSON_HPP
#define RBBL_FORMAT_JSON_HPP

#include <mutex>
#include "format.hpp"

namespace rbbl::fmt {

    class FormatJson : public Format {
      private:
        std::mutex M_MTX_FORMAT_JSON;

      public:
        auto format(const FormatArgs &param) -> type::str override;
        FormatJson() = default;
        ~FormatJson() override = default;
    };

} // namespace rbbl::fmt

#endif // RBBL_FORMAT_JSON_HPP
