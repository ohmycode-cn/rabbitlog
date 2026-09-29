// Author: ohmycode-cn
// Email: ohcode@163.com
// Date: 2026-09-28
// License: MIT
// Copyright: (c) 2026 ohmycode-cn, all rights reserved.

#pragma once
#ifndef RBBL_PATH_MANAGEMENT_HPP
#define RBBL_PATH_MANAGEMENT_HPP

namespace rbbl::path::management::read {

    constexpr auto fname = "rstdlog.conf";
#if defined(_WIN32) || defined(_WIN64)
    constexpr auto fpath{"C:\\Users\\Public\\Documents\\etc\\config\\rstdlog"};
#else
    constexpr auto fpath{"/etc/config/rstdlog"};
#endif

} // namespace rbbl::path::management::read

namespace rbbl::path::management::write {

    constexpr auto fname = "rstdlog.log";
#if defined(_WIN32) || defined(_WIN64)
    constexpr auto fpath{"C:\\Users\\Public\\Documents\\var\\log\\rstdlog"};
#else
    constexpr auto fpath{"/var/log/rstdlog"};
#endif

} // namespace rbbl::path::management::write

#endif // RBBL_PATH_MANAGEMENT_HPP
