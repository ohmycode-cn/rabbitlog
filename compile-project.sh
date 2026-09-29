#!/bin/bash

# ******************************************************************
# * Author: ohmycode-cn
# * Email: ohcode@163.com
# * Date: 2026-09-28
# * License: MIT
# * Copyright: (c) 2026 ohmycode-cn, all rights reserved.
# * Description: compile script to build rabbitlog
# * Bash Standard: Bash 5.3.0 +
# ******************************************************************

if [[ "${0}" != "${BASH_SOURCE[0]}" ]]; then
    echo -e "\033[31mERROR\033[0m: The standard safe practice is 'bash ${0}'"
    echo -e "\033[32mINFO\033[0m: You can obtain the usage instructions by executing \"bash ${0} --help\"!"
    return 1 &>/dev/null
fi

source .shared.sh

# Description:
#   This function builds the rabbitlog project via CMake.
#   By default, unit tests are enabled (UNIT_TEST=ON).
#   Pass --off-unit-test to build a production binary.
#   Pass --clear-build to delete build/* before building.
#   Pass --static to build a statically linked binary (requires --off-unit-test).
# Args:
#   --off-unit-test - Optional. Disable unit tests and build release binary.
#   --clear-build   - Optional. Clear the build directory before building.
#   --static        - Optional. Static link the binary. Must be used with --off-unit-test.
# Returns:
#   0 on success, 1 on build failure.
# Echo:
#   Build progress and result messages.
function main() {
    local unit_test="ON"    # default: unit test enabled
    local clear_build="OFF" # default: do not clear build directory
    local static_build="OFF" # default: dynamic link

    if [[ "${OS}" == "Windows_NT" ]]; then
        error "Current build script does not support Windows!"
        return 1 &>/dev/null
    fi

    while [[ $# -gt 0 ]]; do
        case "${1}" in
        --off-unit-test)
            unit_test="OFF"
            shift
            ;;
        --clear-build)
            clear_build="ON"
            shift
            ;;
        --static)
            static_build="ON"
            shift
            ;;
        *)
            error "Unknown option \"${1}\"!"
            return 1 &>/dev/null
            ;;
        esac
    done

    if [[ "${static_build}" == "ON" && "${unit_test}" == "ON" ]]; then
        error "--static must be used together with --off-unit-test!"
        info "Example: bash ${0} --static --off-unit-test"
        return 1 &>/dev/null
    fi

    local build_dir="build"

    if [[ "${clear_build}" == "ON" ]]; then
        info "Build mode: Clearing build directory: ${build_dir}/*"
        rm -rf "${build_dir:?}"/*
        ls -lh "${build_dir:?}/"
    fi
    sleep 2

    if [[ "${unit_test}" == "ON" ]]; then
        info "Build mode: Debug (UNIT_TEST=ON)"
    else
        info "Build mode: Release (UNIT_TEST=OFF)"
    fi

    if [[ "${static_build}" == "ON" ]]; then
        info "Link mode: Static (STATIC=ON)"
    fi

    if [[ ! -f "CMakeLists.txt" ]]; then
        error "CMakeLists.txt not found. Please check the project directory: 'rabbitlog/CMakeLists.txt'"
        return 1 &>/dev/null
    fi

    info "Configuring CMake ..."

    if ! cmake -B "${build_dir}" -DUNIT_TEST="${unit_test}" -DSTATIC="${static_build}" 2>&1; then
        error "CMake configure failed."
        return 1 &>/dev/null
    fi

    ok "CMake configure done."
    info "Compiling ..."

    local nproc
    if command -v nproc &>/dev/null; then
        nproc=$(nproc)
    elif command -v sysctl &>/dev/null; then
        nproc=$(sysctl -n hw.ncpu 2>/dev/null || echo 4)
    else
        nproc=9
    fi

    if ! cmake --build "${build_dir}" -j "${nproc}" 2>&1; then
        error "Build failed."
        return 1 &>/dev/null
    fi

    ok "Build success."
    return 0
}

main "${@}"
exit ${?}
