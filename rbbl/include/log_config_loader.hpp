// Author: ohmycode-cn
// Email: ohcode@163.com
// Date: 2026-10-03
// License: MIT
// Copyright: (c) 2026 ohmycode-cn, all rights reserved.

#pragma once
#ifndef RBBL_LOG_CONFIG_LOADER_HPP
#define RBBL_LOG_CONFIG_LOADER_HPP

#include "type.hpp"

namespace rbbl::configuration {

    class Loader {
      private:
        rbbl::type::str m_fpath;
        rbbl::type::str m_fname;
        rbbl::type::smp m_strmp;

      public:
        Loader(const rbbl::type::str &fpath, const rbbl::type::str &fname);
        ~Loader();

      private:
        auto call(bool &flag, bool (Loader::*func)()) -> void;
        auto init() -> bool;
        auto load() -> bool;

      public:
        auto getter() -> rbbl::type::smp;
    };

} // namespace rbbl::configuration

#endif // RBBL_LOG_CONFIG_LOADER_HPP
