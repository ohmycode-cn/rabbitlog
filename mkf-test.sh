#!/bin/bash

# ******************************************************************
# * Author: ohmycode-cn
# * Email: ohcode@163.com
# * Date: 2026-09-28
# * License: MIT
# * Copyright: (c) 2026 ohmycode-cn, all rights reserved.
# * Description: create google unit test cpp/hpp files.
# * Bash Standard: Bash 5.3.0 +
# ******************************************************************

if [[ "${0}" != "${BASH_SOURCE[0]}" ]]; then
    echo -e "\033[31mERROR\033[0m: The standard safe practice is 'bash ${0}'"
    echo -e "\033[32mINFO\033[0m: You can obtain the usage instructions by executing \"bash ${0} --help\"!"
    return 1 &>/dev/null
fi

source .shared.sh

ROOT="test/google"
INC_DIRECTORY="${ROOT}/include"
SRC_DIRECTORY="${ROOT}/src"
INTERFACE_DIRECTORY="${ROOT}/interface"
DATE=$(date +%Y-%m-%d)

# Description:
#   This function creates a pair of google unit test cpp/hpp files with the
#   standard author banner, include guards and namespace scaffold. By default
#   files are written to test/google/src (cpp) and test/google/include (hpp);
#   when --path interface is given, both files are written to
#   test/google/interface, which is the api test interface directory and
#   mirrors rbbl/api. Files are created only when neither the cpp nor the
#   hpp file already exists.
# Args:
#   --f | --file <name>      - The base file name without extension (required).
#   --p | --path <interface> - Optional output location. Only "interface" or "ife" is
#                              accepted; any other value is rejected. If
#                              omitted, default test/google/src and
#                              test/google/include directories are used.
# Returns:
#   1 if an unknown option is given, file name is missing, path is not
#   "interface"/"ife", or either target file already exists. 0 on success.
# Echo:
#   Nothing on success. On failure, an error log line describing the problem.
function initfiles() {
    local filename
    local filepath
    while [[ $# -gt 0 ]]; do
        case "${1}" in
        --f | --file)
            filename="${2}"
            shift 2
            ;;
        --p | --path)
            filepath="${2}"
            shift 2
            ;;
        *)
            error "Unknown option \"${1}\"!"
            return 1 &>/dev/null
            ;;
        esac
    done

    if [[ -z "${filename}" ]]; then
        error "File name parameter is required!"
        return 1 &>/dev/null
    fi

    if [[ ! -z "${filepath}" && "interface" != "${filepath}" && "ife" != "${filepath}" ]]; then
        error "File path parameter just support google{interface, ife, src(default), include(default)} !"
        return 1 &>/dev/null
    elif [[ "interface" == "${filepath}" || "ife" == "${filepath}" ]]; then
        INC_DIRECTORY=${INTERFACE_DIRECTORY}
        SRC_DIRECTORY=${INTERFACE_DIRECTORY}
    fi

    if [[ -e "${SRC_DIRECTORY}/${filename}.cpp" || -e "${INC_DIRECTORY}/${filename}.hpp" ]]; then
        error "File \"${filename}\" already exists, cpp and hpp must both be absent!"
        return 1 &>/dev/null
    fi

    local _pub_init_content=(
        "// Author: ohmycode-cn"
        "// Email: ohcode@163.com"
        "// Date: ${DATE}"
        "// License: MIT"
        "// Copyright: (c) 2026 ohmycode-cn, all rights reserved."
    )

    local _pub_init_namespace=(
        "namespace rbbl::test {"
        "} // namespace rbbl::test"
    )

    local cpp_init_content=(
        "${_pub_init_content[@]}"
        ""
        "#include <gtest/gtest.h>"
        ""
        "#include \"${filename}.hpp\""
        ""
        "${_pub_init_namespace[@]}"
        ""
    )

    local hpp_init_content=(
        "${_pub_init_content[@]}"
        ""
        "#pragma once"
        "#ifndef RBBL_TEST_${filename^^}_HPP"
        "#define RBBL_TEST_${filename^^}_HPP"
        ""
        "#include <gtest/gtest.h>"
        ""
        "${_pub_init_namespace[@]}"
        ""
        "#endif // RBBL_TEST_${filename^^}_HPP"
    )

    printf "%s\n" "${cpp_init_content[@]}" >"${SRC_DIRECTORY}/${filename}.cpp"
    printf "%s\n" "${hpp_init_content[@]}" >"${INC_DIRECTORY}/${filename}.hpp"
}

# Description:
#   This function is the entry point of the script and forwards all command
#   line arguments to initfiles.
# Args:
#   $@ - All command line arguments passed to the script.
# Returns:
#   The return value of initfiles: 1 on failure, 0 on success.
# Echo:
#   The output produced by initfiles (error log lines on failure).
function main() {
    initfiles "${@}"
}

main "${@}"
exit 0
