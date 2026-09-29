// Author: ohmycode-cn
// Email: ohcode@163.com
// Date: 2026-09-28
// License: MIT
// Copyright: (c) 2026 ohmycode-cn, all rights reserved.

#include "format_xml.hpp"
#include "tokens.hpp"
#include <mutex>
#include <sstream>

namespace {

    namespace k = rbbl::tks::idt::key;
    namespace o = rbbl::tks::idt::oth;

    template <typename V>
    auto retfmt(const rbbl::type::smp &map, const rbbl::type::str &key, const V &val) -> rbbl::type::str {
        std::stringstream ss;
        ss << o::G_SPACE_08;
        ss << map.at(k::G_LT);
        ss << map.at(key);
        ss << map.at(k::G_GT);
        ss << val;
        ss << map.at(k::G_LT);
        ss << map.at(k::G_SLASH);
        ss << map.at(key);
        ss << map.at(k::G_GT);
        return ss.str();
    }

} // namespace

namespace rbbl::fmt {

    /**
     * @brief Formats a single log entry as an XML <record> element string.
     *
     * @param param  Bundled log entry parameters (timestamp, level, message, token map, file, line).
     * @return A formatted XML <record> segment as a string.
     *
     * @details e.g.
     * <space:4><record><next_line>
     * <space:8><time>timestamp</time><next_line>
     * <space:8><level>level</level><next_line>
     * <space:8><message>message</message><next_line>
     * <space:8><file>file</file><next_line>
     * <space:8><line>line</line><next_line>
     * <space:4></record>
     */
    auto FormatXml::format(const FormatArgs &param) -> rbbl::type::str {
        std::lock_guard<std::mutex> lock(M_MTX_FORMAT_XML);
        std::stringstream ss;
        const rbbl::type::smp &map{param.token};
        ss << o::G_SPACE_04;
        ss << map.at(k::G_LT);
        ss << map.at(k::G_XML_RECORD);
        ss << map.at(k::G_GT);
        ss << o::G_NEXT_LINE;
        // time.
        ss << retfmt(map, k::G_XML_TIME, param.time);
        ss << o::G_NEXT_LINE;
        // level.
        ss << retfmt(map, k::G_XML_LEVEL, param.level);
        ss << o::G_NEXT_LINE;
        // message.
        ss << retfmt(map, k::G_XML_MESSAGE, param.message);
        ss << o::G_NEXT_LINE;
        // file.
        ss << retfmt(map, k::G_XML_FILE, param.file);
        ss << o::G_NEXT_LINE;
        // line.
        ss << retfmt(map, k::G_XML_LINE, param.line);
        ss << o::G_NEXT_LINE;
        ss << o::G_SPACE_04;
        ss << map.at(k::G_LT);
        ss << map.at(k::G_SLASH);
        ss << map.at(k::G_XML_RECORD);
        ss << map.at(k::G_GT);
        ss << o::G_NEXT_LINE;
        return ss.str();
    }

} // namespace rbbl::fmt
