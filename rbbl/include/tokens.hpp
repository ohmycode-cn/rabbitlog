// Author: ohmycode-cn
// Email: ohcode@163.com
// Date: 2026-09-28
// License: MIT
// Copyright: (c) 2026 ohmycode-cn, all rights reserved.

#pragma once
#ifndef RBBL_TOKENS_HPP
#define RBBL_TOKENS_HPP

namespace rbbl::tks::idt::key {
    constexpr auto G_LEFT_BRACE{"left_brace"};                     // {
    constexpr auto G_RIGHT_BRACE{"right_brace"};                   // }
    constexpr auto G_LEFT_SQUARE_BRACKET{"left_square_bracket"};   // [
    constexpr auto G_RIGHT_SQUARE_BRACKET{"right_square_bracket"}; // ]
    constexpr auto G_LEFT_PARENTHESIS{"left_parenthesis"};         // (
    constexpr auto G_RIGHT_PARENTHESIS{"right_parenthesis"};       // )
    constexpr auto G_SEQUENCE{"sequence"};                         // SEQUENCE
    constexpr auto G_TIME{"time"};                                 // TIME
    constexpr auto G_LEVEL{"level"};                               // LEVEL
    constexpr auto G_MESSAGE{"message"};                           // MESSAGE
    constexpr auto G_FILE{"file"};                                 // FILE
    constexpr auto G_LINE{"line"};                                 // LINE
    constexpr auto G_COLON{"colon"};                               // :
    constexpr auto G_COMMA{"comma"};                               // ,
    constexpr auto G_EQUAL{"equal"};                               // =
    constexpr auto G_QUOTE{"quote"};                               // "
    constexpr auto G_GT{"gt"};                                     // >
    constexpr auto G_LT{"lt"};                                     // <
    constexpr auto G_SLASH{"slash"};                               // /
    constexpr auto G_QUESTION{"question"};                         // ?
    constexpr auto G_DEBUG{"debug"};                               // DEBUG
    constexpr auto G_INFO{"info"};                                 // INFO
    constexpr auto G_WARNING{"warning"};                           // WARNING
    constexpr auto G_ERROR{"error"};                               // ERROR
    constexpr auto G_FATAL{"fatal"};                               // FATAL
    constexpr auto G_XML_RECORD{"xml_record"};                     // record
    constexpr auto G_XML_TIME{"xml_time"};                         // time
    constexpr auto G_XML_LEVEL{"xml_level"};                       // level
    constexpr auto G_XML_MESSAGE{"xml_message"};                   // message
    constexpr auto G_XML_SEQUENCE{"xml_sequence"};                 // sequence
    constexpr auto G_XML_FILE{"xml_file"};                         // file
    constexpr auto G_XML_LINE{"xml_line"};                         // line
} // namespace rbbl::tks::idt::key

namespace rbbl::tks::idt::val {
    constexpr auto G_LEFT_BRACE{"{"};           // {
    constexpr auto G_RIGHT_BRACE{"}"};          // }
    constexpr auto G_LEFT_SQUARE_BRACKET{"["};  // [
    constexpr auto G_RIGHT_SQUARE_BRACKET{"]"}; // ]
    constexpr auto G_LEFT_PARENTHESIS{"("};     // (
    constexpr auto G_RIGHT_PARENTHESIS{")"};    // )
    constexpr auto G_SEQUENCE{"SEQUENCE"};      // SEQUENCE
    constexpr auto G_TIME{"TIME"};              // TIME
    constexpr auto G_LEVEL{"LEVEL"};            // LEVEL
    constexpr auto G_MESSAGE{"MESSAGE"};        // MESSAGE
    constexpr auto G_FILE{"FILE"};              // FILE
    constexpr auto G_LINE{"LINE"};              // LINE
    constexpr auto G_COLON{":"};                // :
    constexpr auto G_COMMA{","};                // ,
    constexpr auto G_EQUAL{"="};                // =
    constexpr auto G_QUOTE{"\""};               // "
    constexpr auto G_GT{">"};                   // >
    constexpr auto G_LT{"<"};                   // <
    constexpr auto G_SLASH{"/"};                // /
    constexpr auto G_QUESTION{"?"};             // ?
    constexpr auto G_DEBUG{"DEBUG"};            // DEBUG
    constexpr auto G_INFO{"INFO"};              // INFO
    constexpr auto G_WARNING{"WARNING"};        // WARNING
    constexpr auto G_ERROR{"ERROR"};            // ERROR
    constexpr auto G_FATAL{"FATAL"};            // FATAL
    constexpr auto G_XML_RECORD{"record"};      // record
    constexpr auto G_XML_TIME{"time"};          // time
    constexpr auto G_XML_LEVEL{"level"};        // level
    constexpr auto G_XML_MESSAGE{"message"};    // message
    constexpr auto G_XML_SEQUENCE{"sequence"};  // sequence
    constexpr auto G_XML_FILE{"file"};          // file
    constexpr auto G_XML_LINE{"line"};          // line
} // namespace rbbl::tks::idt::val

namespace rbbl::tks::idt::oth {
    constexpr auto G_SPACE_08{"        "}; // space 8
    constexpr auto G_SPACE_04{"    "};     // space 4
    constexpr auto G_SPACE_03{"   "};      // space 3
    constexpr auto G_SPACE_02{"  "};       // space 2
    constexpr auto G_SPACE_01{" "};        // space 1
    constexpr auto G_NEXT_LINE{"\n"};      // \n
} // namespace rbbl::tks::idt::oth

namespace rbbl::tks::cfg::key {
    constexpr auto G_ENABLE_TERM_COMPATIBLE_MODE{"ENABLE_TERM_COMPATIBLE_MODE"};
    constexpr auto G_ENABLE_TERM_HIGHLIGHT_MODE{"ENABLE_TERM_HIGHLIGHT_MODE"};
    constexpr auto G_ENABLE_TERM_BOLD_FONT_MODE{"ENABLE_TERM_BOLD_FONT_MODE"};
    constexpr auto G_LOG_TERM_FORMAT_STYLE{"LOG_TERM_FORMAT_STYLE"};
    constexpr auto G_LOG_FILE_FORMAT_STYLE{"LOG_FILE_FORMAT_STYLE"};
    constexpr auto G_LOG_TERM_OUTPUT_MODE{"LOG_TERM_OUTPUT_MODE"};
    constexpr auto G_LOG_FILE_OUTPUT_MODE{"LOG_FILE_OUTPUT_MODE"};
    constexpr auto G_LOG_WRITE_FILE_PATH{"LOG_WRITE_FILE_PATH"};
    constexpr auto G_LOG_WRITE_FILE_NAME{"LOG_WRITE_FILE_NAME"};
    constexpr auto G_LOG_FILE_SIZE_LIMIT{"LOG_FILE_SIZE_LIMIT"};
    constexpr auto G_LOG_TERM_LEVEL_FILTER{"LOG_TERM_LEVEL_FILTER"};
    constexpr auto G_LOG_FILE_LEVEL_FILTER{"LOG_FILE_LEVEL_FILTER"};
    constexpr auto G_LOG_MINI_LEVEL_FILTER{"LOG_MINI_LEVEL_FILTER"};
} // namespace rbbl::tks::cfg::key

namespace rbbl::tks::cfg::val {
    constexpr auto G_DEBUG{"debug"};
    constexpr auto G_INFO{"info"};
    constexpr auto G_WARNING{"warning"};
    constexpr auto G_ERROR{"error"};
    constexpr auto G_FATAL{"fatal"};
    constexpr auto G_COMMENT{"#"};
    constexpr auto G_SEMICOLON{";"};
    constexpr auto G_EQUAL{"="};
    constexpr auto G_QUOTE{"\""};
    constexpr auto G_CONSOLE{"console"};
    constexpr auto G_FILE{"file"};
    constexpr auto G_TEXT{"text"};
    constexpr auto G_JSON{"json"};
    constexpr auto G_XML{"xml"};
    constexpr auto G_FALSE{"false"};
    constexpr auto G_TRUE{"true"};
    constexpr auto G_LOG_FILE_SIZE_LIMIT_VALUE{"128MB"};
} // namespace rbbl::tks::cfg::val

#endif // RBBL_TOKENS_HPP
