#!/bin/bash

# ******************************************************************
# * Author: ohmycode-cn
# * Email: ohcode@163.com
# * Date: 2026-09-28
# * License: MIT
# * Copyright: (c) 2026 ohmycode-cn, all rights reserved.
# * Description: filter pure api framework code files and file structure
# *              this script will filter files uninclude in main.cpp and
# *              google test files.
# * Usage: bash filter.sh --d <target_dir> [-v] [-rm]
# *        bash filter.sh --help
# * Bash Standard: Bash 5.3.0 +
# ******************************************************************

if [[ "${0}" != "${BASH_SOURCE[0]}" ]]; then
    echo -e "\033[31mERROR\033[0m: The standard safe practice is 'bash ${0}'"
    echo -e "\033[32mINFO\033[0m: You can obtain the usage instructions by executing \"bash ${0} --help\"!"
    return 1 &>/dev/null
fi

source .shared.sh

# Description:
#   This function prints the usage instructions and available options.
# Args:
#   None
# Returns:
#   None
# Echo:
#   Formatted usage text with option descriptions and examples.
function usage() {
    echo -e "${CYAN}Usage:${RESET}  bash ${0} --d <target_dir> [options]"
    echo -e ""
    echo -e "${CYAN}Options:${RESET}"
    echo -e "  ${YELLOW}WARNING${RESET}:     ${RED}You must be using complete path to the target directory!${RESET}"
    echo -e "  ${GREEN}--d <dir>${RESET}    Target directory that will receive the filtered files."
    echo -e "                   The sub-directory \"${WHITE}rbbl${RESET}\" is created inside it if missing."
    echo -e "  ${GREEN}-v${RESET}           Verbose mode. Show each file transferred by rsync."
    echo -e "  ${GREEN}-r${RESET}           Remove old files in <target_dir>/rbbl before filtering."
    echo -e "  ${GREEN}--help, -h${RESET}   Show this help message and exit."
    echo -e ""
    echo -e "${CYAN}Examples:${RESET}"
    echo -e "  bash ${0} --d ./output"
    echo -e "  bash ${0} --d ./output -v"
    echo -e "  bash ${0} --d ./output -v -r"
}

# Description:
#   This function prints a brief welcome banner before filtering starts.
# Args:
#   None
# Returns:
#   None
# Echo:
#   Welcome message with a one-line usage hint.
function guideinfo() {
    info "WELCOME TO USE THIS SCRIPT!"
    info "${GREEN}Usage:${RESET} 'bash ${0} --d <target_dir> [-v] [-r]'"
    info "Run 'bash ${0} --help' for detailed instructions."
    sleep 1
}

# Description:
#   This function parses command line options and copies the pure api
#   framework files from rbbl/ into the target directory, excluding
#   main.cpp and google test files. When -r is given, old files in the
#   target rbbl directory are removed first. When -v is given, rsync
#   runs in verbose mode and lists each transferred file.
# Args:
#   --d <dir>   - Required. Target directory that receives the filtered files.
#   -v          - Optional. Enable verbose rsync output.
#   -r          - Optional. Remove old files in <target_dir>/rbbl before filtering.
#   --help, -h  - Show usage and exit.
# Returns:
#   0 on success, 1 on invalid arguments or operation failure.
# Echo:
#   Progress and result messages via info, ok, warning, and error loggers.
function filter() {
    local PROOT_DIR="rbbl"
    local TARGET_DIR
    local VERBOSE="false"
    local REMOVE_OLD_FILES="false"

    while [[ $# -gt 0 ]]; do
        case "${1}" in
        --d)
            if [[ $# -lt 2 ]]; then
                error "Option \"--d\" requires a target directory!"
                return 1
            fi
            TARGET_DIR="${2}"
            shift 2
            ;;
        -v)
            VERBOSE="true"
            shift 1
            ;;
        -r)
            REMOVE_OLD_FILES="true"
            shift 1
            ;;
        --help | -h)
            usage
            return 0
            ;;
        *)
            error "Unknown parameter \"${1}\"!"
            return 1
            ;;
        esac
    done

    if [[ -z "${TARGET_DIR}" ]]; then
        error "Option \"--d\" is required!"
        info "Run 'bash ${0} --help' for detailed instructions."
        return 1
    fi

    if [[ ! -d "${TARGET_DIR}" ]]; then
        error "Target directory \"${TARGET_DIR}\" does not exist!"
        info "Please check the directory path."
        return 1 &>/dev/null
    fi

    if [[ ! -d "${TARGET_DIR}/${PROOT_DIR}" ]]; then
        warning "Target directory \"${TARGET_DIR}\" does not contain \"${PROOT_DIR}\" directory!"
        warning "Will create it automatically."
        if ! mkdir "${TARGET_DIR}/${PROOT_DIR}"; then
            error "Failed to create directory \"${TARGET_DIR}/${PROOT_DIR}\"!"
            info "Please check the directory permission."
            info "Or try to run this script with \"sudo\"!"
            return 1 &>/dev/null
        else
            ok "Directory \"${TARGET_DIR}/${PROOT_DIR}\" created successfully."
        fi
    fi

    if [[ "${REMOVE_OLD_FILES}" == "true" ]]; then
        warning "Removing old files: \"${TARGET_DIR}/${PROOT_DIR}\""
        if ! rm -rf "${TARGET_DIR}/${PROOT_DIR:?}"/*; then
            error "Failed to remove old files!"
            info "Please check the directory permission."
            info "Or try to run this script with \"sudo\"!"
            return 1 &>/dev/null
        fi
        ok "Old files removed successfully."
    fi

    local ret
    if [[ "${VERBOSE}" == "true" ]]; then
        info "Filtering files..."
        rsync -av --exclude="main.cpp" rbbl/ "${TARGET_DIR}/${PROOT_DIR}"/ || ret="${?}"
    else
        rsync -a --exclude="main.cpp" rbbl/ "${TARGET_DIR}/${PROOT_DIR}"/ || ret="${?}"
    fi

    if [[ "${ret}" -ne 0 ]]; then
        error "Failed to filter files!"
        info "Please check the directory permission."
        info "Or try to run this script with \"sudo\"!"
        return 1 &>/dev/null
    fi
    ok "Files filtered successfully."
}

# Description:
#   This function is the entry point of the script. It short-circuits to
#   usage when --help or -h is given, otherwise prints the welcome banner
#   and forwards all arguments to filter.
# Args:
#   $@ - All command line arguments passed to the script.
# Returns:
#   The return value of filter: 1 on failure, 0 on success.
# Echo:
#   The output produced by guideinfo and filter.
function main() {
    if [[ "${1}" == "--help" || "${1}" == "-h" ]]; then
        usage
        return 0
    fi
    guideinfo
    filter "$@"
}

main "$@"
exit 0
