// Author: ohmycode-cn
// Email: ohcode@163.com
// Date: 2026-10-03
// License: MIT
// Copyright: (c) 2026 ohmycode-cn, all rights reserved.

#include "log_config_parser.hpp"
#include "type.hpp"

namespace rbbl::configuration {

    auto LogConfigParser::handle(const std::stringstream &ss) -> rbbl::type::smp {
        // TODO: Parse Logic ...
        // NULL DO NOTHING.
        return rbbl::type::smp();
    }

    auto LogConfigParser::parser(const std::stringstream &ss) -> rbbl::type::smp {
        /**
         * SAFETY:
         * ss.str() is not empty. trunc and return empty map.
         */
        if (ss.str().empty()) {
            rbbl::type::smp empty_map;
            return empty_map;
        }
        return handle(ss);
    }
} // namespace rbbl::configuration
