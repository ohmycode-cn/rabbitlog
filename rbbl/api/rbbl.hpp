// Author: ohmycode-cn
// Email: ohcode@163.com
// Date: 2026-09-29
// License: MIT
// Copyright: (c) 2026 ohmycode-cn, all rights reserved.

#pragma once
#ifndef RBBL_RBBL_HPP
#define RBBL_RBBL_HPP

// #include "renum.hpp"
#include "slog.hpp"

namespace rbbl::api {

    // PTR List.
    struct RbbLOpsL {
        lib::SingletonLog *slog{nullptr};
    };

    enum class RbbLMode {
        SINGLETON_LOG = 0,
        UNKNOWN
    };

    class RbbL {
      private: // Member constants, once determined, cannot be modified in any way.
        RbbLOpsL M_RBBL_OPS_L;
        RbbLMode M_MODE;

      private:
        auto drop_ptr() -> void;

      public:
        RbbL(RbbLMode mode = RbbLMode::SINGLETON_LOG);
        ~RbbL();
    };

} // namespace rbbl::api

#define RBBL_API_WRITE(level, message, file, line)

#define RBBL_INFO(message)
#define RBBL_WARNING(message)
#define RBBL_ERROR(message)
#define RBBL_FATAL(message)

#endif // RBBL_RBBL_HPP
