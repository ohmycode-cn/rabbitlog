// Author: ohmycode-cn
// Email: ohcode@163.com
// Date: 2026-09-29
// License: MIT
// Copyright: (c) 2026 ohmycode-cn, all rights reserved.

#pragma once
#ifndef RBBL_COLORS_HPP
#define RBBL_COLORS_HPP

#include "type.hpp"

namespace rbbl::clr {

    /**
     * @brief Enumeration of supported ANSI color names for log colorization
     */
    enum class ColorName {
        RESET = 0,
        DARK,
        RED,
        GREEN,
        YELLOW,
        BLUE,
        MAGENTA,
        CYAN,
        WHITE
    };

    /**
     * @brief Utility for applying ANSI color codes to log messages.
     *
     * Provides shorthand methods (d, r, g, y, b, m, c, w) to wrap text
     * in the corresponding ANSI terminal color sequences.
     * Supports configurable escape prefix and font weight.
     */
    class Colors {
      private:
        const char *const M_ANSI_SEQS[9]{"0m", "30m", "31m", "32m", "33m", "34m", "35m",
                                         "36m", "37m"};
        const char *const M_FONT_NORMAL{"[0;"};
        const char *const M_FONT_BOLD{"[1;"};
        const char *const M_ANSI_OLD{"\033"};
        const char *const M_ANSI_NEW{"\x1b"};

      private:
        type::str m_reset;
        type::str m_dark;
        type::str m_red;
        type::str m_green;
        type::str m_yellow;
        type::str m_blue;
        type::str m_magenta;
        type::str m_cyan;
        type::str m_white;

      private:
        void init(const bool enable_ce, const bool enable_ht, const bool enable_bf);
        auto wrap(const type::str &color, const type::str &message) -> type::str;

      public:
        Colors(const bool enable_ce = true, const bool enable_ht = false, const bool enable_bf = false);
        ~Colors() = default;

      public:
        auto d(const type::str &message) -> type::str;
        auto r(const type::str &message) -> type::str;
        auto g(const type::str &message) -> type::str;
        auto y(const type::str &message) -> type::str;
        auto b(const type::str &message) -> type::str;
        auto m(const type::str &message) -> type::str;
        auto c(const type::str &message) -> type::str;
        auto w(const type::str &message) -> type::str;
        auto get_var(ColorName color) -> type::str;
    };

} // namespace rbbl::clr

#endif // RBBL_COLORS_HPP
