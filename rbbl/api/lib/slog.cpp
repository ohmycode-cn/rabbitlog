// Author: ohmycode-cn
// Email: ohcode@163.com
// Date: 2026-09-29
// License: MIT
// Copyright: (c) 2026 ohmycode-cn, all rights reserved.

#include "slog.hpp"

namespace rbbl::api::lib {

    auto SingletonLog::instance() -> SingletonLog & {
        static SingletonLog sg;
        return sg;
    }

    auto SingletonLog::write(const SingletonLog &param) -> void {
    }

} // namespace rbbl::api::lib
