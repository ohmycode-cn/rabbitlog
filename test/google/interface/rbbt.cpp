// Date Time: 2026-09-26-22-11-03
// Author: ohmycode-cn
// Email: ohcode@163.com
// Copyright (c) ohmycode-cn. All rights reserved.
// License: MIT

#include "preview_format_output.hpp"
#include "rbbt.hpp"
#include "test_format.hpp"
#include "test_output_file.hpp"  // IWYU pragma: keep
#include "test_output_file2.hpp" // IWYU pragma: keep
#include "test_output_file3.hpp" // IWYU pragma: keep
#include "test_time26.hpp"

#include <iostream>
#include <sstream>
#include <syncstream>

namespace rbbl::test {

    /**
     * @brief Run a single test-suite entry point, chaining pass/fail state.
     *
     * @param ret   Cumulative result flag (pass-by-reference).
     *              Set to false on failure; when already false the
     *              function short-circuits and skips execution.
     * @param func  Pointer to a test-suite main function that returns
     *              0 on success, non-zero on failure.
     * @param file  Caller source file path (use __FILE__).
     * @param line  Caller source line number (use __LINE__).
     */
    void test_true_run(bool &ret, int (*func)(), const std::string &file, const int line) {

        if (ret == false) {
            {
                std::stringstream ss;
                ss << "test function failed: func is previous failed, file: " << file << ", line: " << line;
                std::osyncstream(std::cout) << ss.str() << std::endl;
            }
            return;
        }

        if (0 == func()) {
            ret = true;
        } else {
            ret = false;
        }
    }

    auto exec_unit_test() -> void {
        std::cout << "THIS IS GOOGLE TEST MASTER" << std::endl;
        bool ret = true;
        test_true_run(ret, test_time26_main, __FILE__, __LINE__);
        test_true_run(ret, test_format_main, __FILE__, __LINE__);
        test_true_run(ret, preview_format_output_main, __FILE__, __LINE__);
        // test_true_run(ret, test_output_file_main, __FILE__, __LINE__);
        // test_true_run(ret, test_output_file2_main, __FILE__, __LINE__);
        // test_true_run(ret, test_output_file3_main, __FILE__, __LINE__);
        if (ret == false) {
            std::cout << "TEST FAILED" << std::endl;
        } else {
            std::cout << "ALL TESTS PASSED" << std::endl;
        }
    }

} // namespace rbbl::test
