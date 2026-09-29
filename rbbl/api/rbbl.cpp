// Author: ohmycode-cn
// Email: ohcode@163.com
// Date: 2026-09-29
// License: MIT
// Copyright: (c) 2026 ohmycode-cn, all rights reserved.

#include "rbbl.hpp"

namespace rbbl::api {

    RbbL::RbbL(RbbLMode mode) {
        M_MODE = mode;
    }

    RbbL::~RbbL() {
        drop_ptr();
    }

    auto RbbL::drop_ptr() -> void {
        // SingletonLog is a static singleton — skip it, never delete or reset here.
        // Drop only owned (non-singleton) pointers below.
    }

} // namespace rbbl::api
