#!/bin/bash

# ******************************************************************
# * Author: ohmycode-cn
# * Email: ohcode@163.com
# * Date: 2026-09-28
# * License: MIT
# * Copyright: (c) 2026 ohmycode-cn, all rights reserved.
# * Description: Bash shared script
# * Bash Standard: Bash 5.3.0 +
# ******************************************************************

# Highlight: reset
readonly RESET='\033[0m'

# Highlight: black ~ white
readonly BLACK='\033[30m'   # Black
readonly RED='\033[31m'     # Red
readonly GREEN='\033[32m'   # Green
readonly YELLOW='\033[33m'  # Yellow
readonly BLUE='\033[34m'    # Blue
readonly MAGENTA='\033[35m' # Magenta
readonly CYAN='\033[36m'    # Cyan
readonly WHITE='\033[37m'   # White
ONCE_TIME=$(date '+%Y-%m-%d-%H-%M-%S')
# shellcheck disable=SC2034
readonly ONCE_TIME
COLON=${WHITE}":"${RESET}
readonly COLON

# Description:
#   This function echo the current timestamp in YYYY-MM-DD-HH-MM-SS-3N format.
# Args:
#   None
# Returns:
#   None
# Echo:
#   Timestamp in YYYY-MM-DD-HH-MM-SS-3N format.
function now() {
    echo -e "${BLUE}[${BLACK}$(date '+%Y-%m-%d-%H-%M-%S@%3N')${BLUE}]${RESET}"
}

# Description:
#   This function prints an informational message with a timestamp.
# Args:
#   $1 - The message to display.
# Returns:
#   None
# Echo:
#   Formatted INFO log line with timestamp and cyan label.
function info() {
    echo -e "$(now) [${CYAN}INFO ${RESET}] ${COLON}${GREEN}${1}${RESET}"
}

# Description:
#   This function prints a success message with a timestamp.
# Args:
#   $1 - The message to display.
# Returns:
#   None
# Echo:
#   Formatted OK log line with timestamp and green label.
function ok() {
    echo -e "$(now) [${GREEN}OK${RESET}] ${COLON}${GREEN}${1}${RESET}"
}

# Description:
#   This function prints a warning message with a timestamp.
# Args:
#   $1 - The message to display.
# Returns:
#   None
# Echo:
#   Formatted WARNING log line with timestamp and yellow label.
function warning() {
    echo -e "$(now) [${YELLOW}WARNING${RESET}] ${COLON}${YELLOW}${1}${RESET}"
}

# Description:
#   This function prints an error message with a timestamp.
# Args:
#   $1 - The message to display.
# Returns:
#   None
# Echo:
#   Formatted ERROR log line with timestamp and magenta label.
function error() {
    echo -e "$(now) [${RED}ERROR${RESET}] ${COLON}${MAGENTA}${1}${RESET}"
}
