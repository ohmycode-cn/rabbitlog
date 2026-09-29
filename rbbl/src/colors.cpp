// Author: ohmycode-cn
// Email: ohcode@163.com
// Date: 2026-09-29
// License: MIT
// Copyright: (c) 2026 ohmycode-cn, all rights reserved.

#include "colors.hpp"

namespace rbbl::clr {

    /**
     * @brief Construct a Colors formatter and initialize color sequences.
     *
     * @param enable_ce  Use classic ESC escape sequence (\033) instead of \x1b.
     * @param enable_ht  Enable ANSI color output; false disables all colors.
     * @param enable_bf  Enable bold font weight instead of normal.
     */
    Colors::Colors(const bool enable_ce, const bool enable_ht, const bool enable_bf) {
        init(enable_ce, enable_ht, enable_bf);
    }

    /**
     * @brief Initialize ANSI color sequences based on configuration.
     *
     * @param enable_ce  Use classic ESC escape sequence (\033) instead of \x1b.
     * @param enable_ht  Enable ANSI color output; false sets all colors to empty.
     * @param enable_bf  Enable bold font weight instead of normal.
     */
    void Colors::init(const bool enable_ce, const bool enable_ht, const bool enable_bf) {
        type::str font = (enable_bf) ? M_FONT_BOLD : M_FONT_NORMAL;
        type::str ansi = (enable_ce) ? M_ANSI_OLD : M_ANSI_NEW;
        if (!enable_ht) {
            m_reset = "";
            m_dark = "";
            m_red = "";
            m_green = "";
            m_yellow = "";
            m_blue = "";
            m_magenta = "";
            m_cyan = "";
            m_white = "";
            return;
        }
        m_reset = ansi + font + M_ANSI_SEQS[0];
        m_dark = ansi + font + M_ANSI_SEQS[1];
        m_red = ansi + font + M_ANSI_SEQS[2];
        m_green = ansi + font + M_ANSI_SEQS[3];
        m_yellow = ansi + font + M_ANSI_SEQS[4];
        m_blue = ansi + font + M_ANSI_SEQS[5];
        m_magenta = ansi + font + M_ANSI_SEQS[6];
        m_cyan = ansi + font + M_ANSI_SEQS[7];
        m_white = ansi + font + M_ANSI_SEQS[8];
    }

    /**
     * @brief Wrap a message with an ANSI color prefix and reset suffix.
     *
     * @param color    The ANSI color sequence to prepend.
     * @param message  The message text to colorize.
     * @return The colorized string with reset appended.
     */
    auto Colors::wrap(const type::str &color, const type::str &message) -> type::str {
        return color + message + m_reset;
    }

    /**
     * @brief Resolve a ColorName enum to its underlying color sequence.
     *
     * @param color  The ColorName enumerator to resolve.
     * @return The ANSI color sequence member matching the given enumerator.
     */
    auto Colors::get_var(ColorName color) -> type::str {
        switch (color) {
        case ColorName::RESET:
            return m_reset;
        case ColorName::DARK:
            return m_dark;
        case ColorName::RED:
            return m_red;
        case ColorName::GREEN:
            return m_green;
        case ColorName::YELLOW:
            return m_yellow;
        case ColorName::BLUE:
            return m_blue;
        case ColorName::MAGENTA:
            return m_magenta;
        case ColorName::CYAN:
            return m_cyan;
        case ColorName::WHITE:
            return m_white;
        }
        return m_reset;
    }

    /**
     * @brief Apply dark (black) color to the message.
     *
     * @param message  The message text to colorize.
     * @return The colorized string.
     */
    auto Colors::d(const type::str &message) -> type::str {
        return wrap(m_dark, message);
    }

    /**
     * @brief Apply red color to the message.
     *
     * @param message  The message text to colorize.
     * @return The colorized string.
     */
    auto Colors::r(const type::str &message) -> type::str {
        return wrap(m_red, message);
    }

    /**
     * @brief Apply green color to the message.
     *
     * @param message  The message text to colorize.
     * @return The colorized string.
     */
    auto Colors::g(const type::str &message) -> type::str {
        return wrap(m_green, message);
    }

    /**
     * @brief Apply yellow color to the message.
     *
     * @param message  The message text to colorize.
     * @return The colorized string.
     */
    auto Colors::y(const type::str &message) -> type::str {
        return wrap(m_yellow, message);
    }

    /**
     * @brief Apply blue color to the message.
     *
     * @param message  The message text to colorize.
     * @return The colorized string.
     */
    auto Colors::b(const type::str &message) -> type::str {
        return wrap(m_blue, message);
    }

    /**
     * @brief Apply magenta color to the message.
     *
     * @param message  The message text to colorize.
     * @return The colorized string.
     */
    auto Colors::m(const type::str &message) -> type::str {
        return wrap(m_magenta, message);
    }

    /**
     * @brief Apply cyan color to the message.
     *
     * @param message  The message text to colorize.
     * @return The colorized string.
     */
    auto Colors::c(const type::str &message) -> type::str {
        return wrap(m_cyan, message);
    }

    /**
     * @brief Apply white color to the message.
     *
     * @param message  The message text to colorize.
     * @return The colorized string.
     */
    auto Colors::w(const type::str &message) -> type::str {
        return wrap(m_white, message);
    }

} // namespace rbbl::clr
