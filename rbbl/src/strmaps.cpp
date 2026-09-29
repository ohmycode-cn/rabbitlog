// Author: ohmycode-cn
// Email: ohcode@163.com
// Date: 2026-09-28
// License: MIT
// Copyright: (c) 2026 ohmycode-cn, all rights reserved.

#include "strmaps.hpp"
#include "colors.hpp"
#include "type.hpp"
#include "tokens.hpp"

namespace {
    namespace k = rbbl::tks::idt::key;
    namespace v = rbbl::tks::idt::val;

    auto retmap_normal() -> rbbl::type::smp {
        rbbl::type::smp map{
            {k::G_LEFT_BRACE, v::G_LEFT_BRACE},
            {k::G_RIGHT_BRACE, v::G_RIGHT_BRACE},
            {k::G_LEFT_SQUARE_BRACKET, v::G_LEFT_SQUARE_BRACKET},
            {k::G_RIGHT_SQUARE_BRACKET, v::G_RIGHT_SQUARE_BRACKET},
            {k::G_LEFT_PARENTHESIS, v::G_LEFT_PARENTHESIS},
            {k::G_RIGHT_PARENTHESIS, v::G_RIGHT_PARENTHESIS},
            {k::G_SEQUENCE, v::G_SEQUENCE},
            {k::G_TIME, v::G_TIME},
            {k::G_LEVEL, v::G_LEVEL},
            {k::G_MESSAGE, v::G_MESSAGE},
            {k::G_FILE, v::G_FILE},
            {k::G_LINE, v::G_LINE},
            {k::G_COLON, v::G_COLON},
            {k::G_COMMA, v::G_COMMA},
            {k::G_EQUAL, v::G_EQUAL},
            {k::G_QUOTE, v::G_QUOTE},
            {k::G_GT, v::G_GT},
            {k::G_LT, v::G_LT},
            {k::G_SLASH, v::G_SLASH},
            {k::G_QUESTION, v::G_QUESTION},
            {k::G_DEBUG, v::G_DEBUG},
            {k::G_INFO, v::G_INFO},
            {k::G_WARNING, v::G_WARNING},
            {k::G_ERROR, v::G_ERROR},
            {k::G_FATAL, v::G_FATAL},
            {k::G_XML_RECORD, v::G_XML_RECORD},
            {k::G_XML_TIME, v::G_XML_TIME},
            {k::G_XML_LEVEL, v::G_XML_LEVEL},
            {k::G_XML_MESSAGE, v::G_XML_MESSAGE},
            {k::G_XML_SEQUENCE, v::G_XML_SEQUENCE},
            {k::G_XML_FILE, v::G_XML_FILE},
            {k::G_XML_LINE, v::G_XML_LINE}};
        return map;
    }

    auto retmap_highlight() -> rbbl::type::smp {
        rbbl::clr::Colors t(true, true, true);
        rbbl::type::smp map{
            {k::G_LEFT_BRACE, t.c(v::G_LEFT_BRACE)},
            {k::G_RIGHT_BRACE, t.c(v::G_RIGHT_BRACE)},
            {k::G_LEFT_SQUARE_BRACKET, t.b(v::G_LEFT_SQUARE_BRACKET)},
            {k::G_RIGHT_SQUARE_BRACKET, t.b(v::G_RIGHT_SQUARE_BRACKET)},
            {k::G_LEFT_PARENTHESIS, t.m(v::G_LEFT_PARENTHESIS)},
            {k::G_RIGHT_PARENTHESIS, t.m(v::G_RIGHT_PARENTHESIS)},
            {k::G_SEQUENCE, t.y(v::G_SEQUENCE)},
            {k::G_TIME, t.y(v::G_TIME)},
            {k::G_LEVEL, t.y(v::G_LEVEL)},
            {k::G_MESSAGE, t.y(v::G_MESSAGE)},
            {k::G_FILE, t.y(v::G_FILE)},
            {k::G_LINE, t.y(v::G_LINE)},
            {k::G_COLON, t.c(v::G_COLON)},
            {k::G_COMMA, t.w(v::G_COMMA)},
            {k::G_EQUAL, t.w(v::G_EQUAL)},
            {k::G_QUOTE, t.r(v::G_QUOTE)},
            {k::G_GT, t.w(v::G_GT)},
            {k::G_LT, t.w(v::G_LT)},
            {k::G_SLASH, t.w(v::G_SLASH)},
            {k::G_QUESTION, t.w(v::G_QUESTION)},
            {k::G_DEBUG, t.g(v::G_DEBUG)},
            {k::G_INFO, t.b(v::G_INFO)},
            {k::G_WARNING, t.y(v::G_WARNING)},
            {k::G_ERROR, t.r(v::G_ERROR)},
            {k::G_FATAL, t.m(v::G_FATAL)},
            {k::G_XML_RECORD, t.g(v::G_XML_RECORD)},
            {k::G_XML_TIME, t.g(v::G_XML_TIME)},
            {k::G_XML_LEVEL, t.g(v::G_XML_LEVEL)},
            {k::G_XML_MESSAGE, t.g(v::G_XML_MESSAGE)},
            {k::G_XML_SEQUENCE, t.g(v::G_XML_SEQUENCE)},
            {k::G_XML_FILE, t.g(v::G_XML_FILE)},
            {k::G_XML_LINE, t.g(v::G_XML_LINE)}};
        return map;
    }
} // namespace

namespace rbbl {

    auto get_token_map(bool use_highlight_map) -> type::smp {
        return use_highlight_map ? retmap_highlight() : retmap_normal();
    }

} // namespace rbbl
