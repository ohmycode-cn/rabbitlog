// Author: ohmycode-cn
// Email: ohcode@163.com
// Date: 2026-09-28
// License: MIT
// Copyright: (c) 2026 ohmycode-cn, all rights reserved.

#pragma once
#ifndef RBBL_TYPE_HPP
#define RBBL_TYPE_HPP

#include <unordered_map>
#include <string>

namespace rbbl::type {

    using cnt = int; // This count type. If the type is not long enough, you can modify it.
    using str = std::string;
    using smp = std::unordered_map<str, str>;
    using uit = unsigned int;

} // namespace rbbl::type

#endif // RBBL_TYPE_HPP
