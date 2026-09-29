// Author: ohmycode-cn
// Email: ohcode@163.com
// Date: 2026-09-28
// License: MIT
// Copyright: (c) 2026 ohmycode-cn, all rights reserved.

#include <mutex>
#include <sstream>
#include "format_text.hpp"
#include "tokens.hpp"

namespace {

    namespace k = rbbl::tks::idt::key;
    namespace o = rbbl::tks::idt::oth;

} // namespace

namespace rbbl::fmt {

    /**
     * @brief Formats a single log entry as a plain-text line pair.
     *
     * @param param  Bundled log entry parameters (timestamp, level, message, token map, file, line).
     * @return A formatted plain-text log segment as a string.
     *
     * @details e.g.
     * time level line:file<next_line>
     * <space:8>{MESSAGE}:<space:1>message
     */
    auto FormatText::format(const FormatArgs &param) -> type::str {

        std::lock_guard<std::mutex> lock(M_MTX_FORMAT_TEXT);

        std::stringstream ss;
        const type::smp &map{param.token};

        ss << param.time;
        ss << o::G_SPACE_01;
        ss << param.level;
        ss << o::G_SPACE_01;
        ss << param.line;
        ss << map.at(k::G_COLON);
        ss << param.file;
        ss << o::G_NEXT_LINE;
        ss << o::G_SPACE_08;
        ss << map.at(k::G_LEFT_BRACE);
        ss << map.at(k::G_MESSAGE);
        ss << map.at(k::G_RIGHT_BRACE);
        ss << map.at(k::G_COLON);
        ss << o::G_SPACE_01;
        ss << param.message;
        ss << o::G_NEXT_LINE;
        return ss.str();
    }

} // namespace rbbl::fmt
