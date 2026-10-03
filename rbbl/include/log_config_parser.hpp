// Author: ohmycode-cn
// Email: ohcode@163.com
// Date: 2026-10-03
// License: MIT
// Copyright: (c) 2026 ohmycode-cn, all rights reserved.

#pragma once
#ifndef RBBL_LOG_CONFIG_PARSER_HPP
#define RBBL_LOG_CONFIG_PARSER_HPP

#include "type.hpp"
#include <sstream>

namespace rbbl::configuration {

    class LogConfigParser {
      public:
        LogConfigParser() = default;
        ~LogConfigParser() = default;

      private:
        auto handle(const std::stringstream &ss) -> rbbl::type::smp;

      public:
        auto parser(const std::stringstream &ss) -> rbbl::type::smp;
    };

} // namespace rbbl::configuration

#endif // RBBL_LOG_CONFIG_PARSER_HPP
