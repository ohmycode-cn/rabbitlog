// Author: ohmycode-cn
// Email: ohcode@163.com
// Date: 2026-09-29
// License: MIT
// Copyright: (c) 2026 ohmycode-cn, all rights reserved.

#pragma once
#ifndef RBBL_SLOG_HPP
#define RBBL_SLOG_HPP

#include "type.hpp"

namespace rbbl::api::lib {

    struct SingletonLogArgs {
        rbbl::type::str level;
        rbbl::type::str message;
        rbbl::type::str file;
        int line;
    };

    class SingletonLog {
      private:
        SingletonLog() = default;
        ~SingletonLog() = default;
        SingletonLog(const SingletonLog &) = delete;
        SingletonLog &operator=(const SingletonLog &) = delete;

      public:
        static auto instance() -> SingletonLog &;
        auto write(const SingletonLog &param) -> void;
    };

} // namespace rbbl::api::lib

#endif // RBBL_SLOG_HPP
