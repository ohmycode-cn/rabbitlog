// Author: ohmycode-cn
// Email: ohcode@163.com
// Date: 2026-09-28
// License: MIT
// Copyright: (c) 2026 ohmycode-cn, all rights reserved.

#include <mutex>
#include <sstream>
#include "format_json.hpp"
#include "tokens.hpp"

namespace {

    namespace k = rbbl::tks::idt::key;
    namespace o = rbbl::tks::idt::oth;

    template <typename V>
    auto retfmt(const rbbl::type::smp &map, const rbbl::type::str &key, const V &val) -> rbbl::type::str {
        std::stringstream ss;
        ss << o::G_SPACE_08;
        ss << map.at(k::G_QUOTE);
        ss << map.at(key);
        ss << map.at(k::G_QUOTE);
        ss << map.at(k::G_COLON);
        ss << o::G_SPACE_01;
        ss << map.at(k::G_QUOTE);
        ss << val;
        ss << map.at(k::G_QUOTE);
        ss << map.at(k::G_COMMA);
        ss << o::G_NEXT_LINE;
        return ss.str();
    }

} // namespace

namespace rbbl::fmt {

    /**
     * @brief Formats a single log entry as a JSON object string.
     *
     * @param param  Bundled log entry parameters (timestamp, level, message, token map, file, line).
     * @return A formatted JSON object segment as a string.
     *
     * @details e.g.
     * <space:4>"timestamp":<space:1>{<next_line>
     * <space:8>"TIME":<space:1>"timestamp",<next_line>
     * <space:8>"LEVEL":<space:1>"level",<next_line>
     * <space:8>"MESSAGE":<space:1>"message",<next_line>
     * <space:8>"FILE":<space:1>"file",<next_line>
     * <space:8>"LINE":<space:1>line,<next_line>
     * <space:4>},
     */
    auto FormatJson::format(const FormatArgs &param) -> rbbl::type::str {

        std::lock_guard<std::mutex> lock(M_MTX_FORMAT_JSON);

        std::stringstream ss;
        const rbbl::type::smp &map{param.token};

        // start.
        ss << o::G_SPACE_04;
        ss << map.at(k::G_QUOTE);
        ss << param.time;
        ss << map.at(k::G_QUOTE);
        ss << map.at(k::G_COLON);
        ss << o::G_SPACE_01;
        ss << map.at(k::G_LEFT_BRACE);
        ss << o::G_NEXT_LINE;

        // time.
        ss << retfmt(map, k::G_TIME, param.time);
        // level.
        ss << retfmt(map, k::G_LEVEL, param.level);
        // message.
        ss << retfmt(map, k::G_MESSAGE, param.message);
        // file.
        ss << retfmt(map, k::G_FILE, param.file);
        // line.
        ss << retfmt(map, k::G_LINE, param.line);

        // endof.
        ss << o::G_SPACE_04;
        ss << map.at(k::G_RIGHT_BRACE);
        ss << map.at(k::G_COMMA);
        return ss.str();
    }

} // namespace rbbl::fmt
