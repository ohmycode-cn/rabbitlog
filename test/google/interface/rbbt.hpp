// Date Time: 2026-09-26-22-11-03
// Author: ohmycode-cn
// Email: ohcode@163.com
// Copyright (c) ohmycode-cn. All rights reserved.
// License: MIT

#pragma once
#ifndef RBBL_TEST_RBBT_HPP
#define RBBL_TEST_RBBT_HPP

#include <string>

namespace rbbl::test {

    void test_true_run(bool &ret, int (*func)(), const std::string &file, const int line);

    auto exec_unit_test() -> void;

} // namespace rbbl::test

#endif // RBBL_TEST_RBBT_HPP
