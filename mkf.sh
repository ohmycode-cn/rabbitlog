#!/bin/bash

# ******************************************************************
# * Author: ohmycode-cn
# * Email: ohcode@163.com
# * Date: 2026-09-28
# * License: MIT
# * Copyright: (c) 2026 ohmycode-cn, all rights reserved.
# * Description: create rabbitlog cpp/hpp files.
# * Bash Standard: Bash 5.3.0 +
# ******************************************************************

if [[ "${0}" != "${BASH_SOURCE[0]}" ]]; then
    echo -e "\033[31mERROR\033[0m: The standard safe practice is 'bash ${0}'"
    echo -e "\033[32mINFO\033[0m: You can obtain the usage instructions by executing \"bash ${0} --help\"!"
    return 1 &>/dev/null
fi

source .shared.sh

ROOT="rbbl"
INC_DIRECTORY="${ROOT}/include"
SRC_DIRECTORY="${ROOT}/src"
API_DIRECTORY="${ROOT}/api"
DATE=$(date +%Y-%m-%d)

# Description:
#   This function creates a pair of rabbitlog cpp/hpp source files with the
#   standard author banner and namespace scaffold. By default files are
#   written to rbbl/src (cpp) and rbbl/include (hpp); when --path api is
#   given, both files are written to rbbl/api. Files are created only when
#   neither the cpp nor the hpp file already exists.
# Args:
#   --f | --file <name> - The base file name without extension (required).
#   --p | --path <api>  - Optional output location. Only "api" is accepted;
#                         any other value is rejected. If omitted, default
#                         rbbl/src and rbbl/include directories are used.
# Returns:
#   1 if an unknown option is given, file name is missing, path is not
#   "api", or either target file already exists. 0 on success.
# Echo:
#   Nothing on success. On failure, an error log line describing the problem.
function initfiles() {
    local filename
    local filepath

    local author_name
    local author_email
    author_email=$(grep -E "EMAIL" .author | cut -d= -f2)
    author_name=$(grep -E "NAME" .author | cut -d= -f2)

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

    if [[ ! -z "${filepath}" && "api" != "${filepath}" && "api/lib" != "${filepath}" ]]; then
        error "File path parameter just support rbbl{api, src(default), include(default)} !"
        return 1 &>/dev/null
    elif [[ "api/lib" == "${filepath}" ]]; then
        INC_DIRECTORY="${API_DIRECTORY}/lib"
        SRC_DIRECTORY="${API_DIRECTORY}/lib"
    elif [[ "api" == "${filepath}" ]]; then
        INC_DIRECTORY=${API_DIRECTORY}
        SRC_DIRECTORY=${API_DIRECTORY}
    fi

    if [[ -e "${SRC_DIRECTORY}/${filename}.cpp" || -e "${INC_DIRECTORY}/${filename}.hpp" ]]; then
        error "File \"${filename}\" already exists, cpp and hpp must both be absent!"
        return 1 &>/dev/null
    fi

    local _pub_init_content=(
        "// Author: ${author_name}"
        "// Email: ${author_email}"
        "// Date: ${DATE}"
        "// License: MIT"
        "// Copyright: (c) 2026 ohmycode-cn, all rights reserved."
    )

    local _pub_init_namespace=(
        "namespace rbbl {"
        "} // namespace rbbl"
    )

    local cpp_init_content=(
        "${_pub_init_content[@]}"
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
        "#ifndef RBBL_${filename^^}_HPP"
        "#define RBBL_${filename^^}_HPP"
        ""
        "${_pub_init_namespace[@]}"
        ""
        "#endif // RBBL_${filename^^}_HPP"
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
