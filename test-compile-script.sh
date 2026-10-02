#!/bin/bash

# ******************************************************************
# * Author: ohmycode-cn
# * Email: ohcode@163.com
# * Date: 2026-10-02
# * License: MIT
# * Copyright: (c) 2026 ohmycode-cn, all rights reserved.
# * Description: argument-combination tests for compile-project.sh
# * Bash Standard: Bash 5.3.0 +
# ******************************************************************

if [[ "${0}" != "${BASH_SOURCE[0]}" ]]; then
    echo -e "\033[31mERROR\033[0m: The standard safe practice is 'bash ${0}'"
    echo -e "\033[32mINFO\033[0m: You can obtain the usage instructions by executing \"bash ${0} --help\"!"
    return 1 &>/dev/null
fi

source .shared.sh

PASS_COUNT=0
FAIL_COUNT=0

# Description:
#   This function runs compile-project.sh with the given arguments and
#   checks the exit code and output against the expected outcome.
# Args:
#   $1 - Test case name.
#   $2 - Expected outcome: "pass" or "fail".
#   $3 - Optional. Fixed-string pattern that must appear in the output.
#        Pass "" to skip the pattern check.
#   ${@:4} - Arguments forwarded to compile-project.sh.
# Returns:
#   0 if the case behaved as expected, 1 otherwise.
# Echo:
#   A PASS/FAIL line per case; on failure the tail of the captured output.
function run_case() {
    local name="${1}"
    local expect="${2}"
    local pattern="${3}"
    shift 3

    info "Running: ${name}"
    local output
    local rc=0
    output=$(bash compile-project.sh "${@}" 2>&1) || rc=$?

    local matched="no"
    if [[ "${expect}" == "pass" && "${rc}" -eq 0 ]]; then
        matched="yes"
    elif [[ "${expect}" == "fail" && "${rc}" -ne 0 ]]; then
        matched="yes"
    fi

    if [[ "${matched}" == "yes" && -n "${pattern}" ]]; then
        if ! echo "${output}" | grep -qF -- "${pattern}"; then
            matched="no"
            output="${output}"$'\n'"[pattern not found: ${pattern}]"
        fi
    fi

    if [[ "${matched}" == "yes" ]]; then
        ok "PASS: ${name}"
        PASS_COUNT=$((PASS_COUNT + 1))
    else
        error "FAIL: ${name} (rc=${rc}, expect=${expect})"
        echo "${output}" | tail -8
        FAIL_COUNT=$((FAIL_COUNT + 1))
    fi
}

# Description:
#   This function checks that a CMakeCache.txt entry matches the given
#   extended regular expression after a successful build.
# Args:
#   $1 - Test case name.
#   $2 - Extended regex (grep -E) that must match at least one cache line.
# Returns:
#   0 on match, 1 otherwise.
# Echo:
#   A PASS/FAIL line per case.
function check_cache() {
    local name="${1}"
    local pattern="${2}"

    if grep -qE "${pattern}" build/CMakeCache.txt 2>/dev/null; then
        ok "PASS: ${name}"
        PASS_COUNT=$((PASS_COUNT + 1))
    else
        error "FAIL: ${name} (cache pattern: ${pattern})"
        grep -E "ATOMIC" build/CMakeCache.txt 2>/dev/null
        FAIL_COUNT=$((FAIL_COUNT + 1))
    fi
}

# Description:
#   This function checks that no CMakeCache.txt entry matches the given
#   extended regular expression after a successful build.
# Args:
#   $1 - Test case name.
#   $2 - Extended regex (grep -E) that must NOT match any cache line.
# Returns:
#   0 when absent, 1 when present.
# Echo:
#   A PASS/FAIL line per case.
function check_cache_absent() {
    local name="${1}"
    local pattern="${2}"

    if grep -qE "${pattern}" build/CMakeCache.txt 2>/dev/null; then
        error "FAIL: ${name} (unexpected cache entry: ${pattern})"
        grep -E "${pattern}" build/CMakeCache.txt 2>/dev/null
        FAIL_COUNT=$((FAIL_COUNT + 1))
    else
        ok "PASS: ${name}"
        PASS_COUNT=$((PASS_COUNT + 1))
    fi
}

# Description:
#   This function runs the compile-project.sh argument-combination matrix:
#   invalid --atomic guard combinations must fail fast with a clear error,
#   valid combinations must build successfully and set the expected CMake
#   spinlock flags.
# Args:
#   None.
# Returns:
#   0 if every case passed, 1 otherwise.
# Echo:
#   Per-case PASS/FAIL lines and a final summary.
function main() {
    if [[ ! -f "CMakeLists.txt" || ! -f "compile-project.sh" ]]; then
        error "Run this script from the rabbitlog project root!"
        return 1 &>/dev/null
    fi

    info "===== compile-project.sh argument-combination tests ====="

    info "---- invalid combinations (expect fail) ----"
    run_case "spinlock without --atomic" "fail" \
        "must appear after --atomic" \
        --use-atomic-thread-spinlock
    run_case "spinlock before --atomic" "fail" \
        "must appear after --atomic" \
        --use-atomic-thread-spinlock --atomic
    run_case "--static after --atomic" "fail" \
        "After --atomic only optimization parameters are allowed" \
        --atomic --static
    run_case "--off-unit-test after --atomic" "fail" \
        "After --atomic only optimization parameters are allowed" \
        --atomic --off-unit-test
    run_case "--static after --atomic+spinlock" "fail" \
        "After --atomic only optimization parameters are allowed" \
        --atomic --use-atomic-thread-spinlock --static
    run_case "--static without --off-unit-test" "fail" \
        "--static must be used together with --off-unit-test" \
        --static
    run_case "unknown option" "fail" \
        "Unknown option" \
        --bogus-flag

    info "---- valid combinations (expect pass) ----"

    run_case "clear-build + spinlock" "pass" \
        "Build success" \
        --clear-build --off-unit-test --atomic --use-atomic-thread-spinlock
    check_cache "spinlock: ATOMIC_THREAD_SPINLOCK_MODE=ON" \
        "^ATOMIC_THREAD_SPINLOCK_MODE:.*=ON"
    check_cache_absent "no ATOMIC_THREAD_MODE in cache" \
        "^ATOMIC_THREAD_MODE:"

    run_case "--atomic alone (mutex default)" "pass" \
        "Build success" \
        --off-unit-test --atomic
    check_cache "mutex: ATOMIC_THREAD_SPINLOCK_MODE=OFF" \
        "^ATOMIC_THREAD_SPINLOCK_MODE:.*=OFF"

    run_case "static + spinlock (opts before --atomic)" "pass" \
        "Build success" \
        --off-unit-test --static --atomic --use-atomic-thread-spinlock
    check_cache "static spinlock: ATOMIC_THREAD_SPINLOCK_MODE=ON" \
        "^ATOMIC_THREAD_SPINLOCK_MODE:.*=ON"

    run_case "baseline release (no --atomic)" "pass" \
        "Build success" \
        --off-unit-test

    run_case "default unit-test + spinlock" "pass" \
        "Build success" \
        --atomic --use-atomic-thread-spinlock

    info "===== SUMMARY ====="
    info "Passed: ${PASS_COUNT}, Failed: ${FAIL_COUNT}"
    if [[ ${FAIL_COUNT} -gt 0 ]]; then
        error "Some compile-project.sh argument tests failed."
        return 1 &>/dev/null
    fi
    ok "All compile-project.sh argument tests passed."
    return 0
}

main "${@}"
exit ${?}
