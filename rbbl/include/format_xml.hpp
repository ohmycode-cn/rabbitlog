// Author: ohmycode-cn
// Email: ohcode@163.com
// Date: 2026-09-28
// License: MIT
// Copyright: (c) 2026 ohmycode-cn, all rights reserved.

#pragma once
#ifndef RBBL_FORMAT_XML_HPP
#define RBBL_FORMAT_XML_HPP

#include <mutex>
#include "format.hpp"

namespace rbbl::fmt {

    class FormatXml : public Format {
      private:
        std::mutex M_MTX_FORMAT_XML;

      public:
        auto format(const FormatArgs &param) -> type::str override;
        FormatXml() = default;
        ~FormatXml() override = default;
    };

} // namespace rbbl::fmt

#endif // RBBL_FORMAT_XML_HPP
