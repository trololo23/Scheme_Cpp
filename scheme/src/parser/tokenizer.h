#pragma once

#include <variant>
#include <optional>
#include <istream>
#include "error.h"
#include "ctype.h"
#include "iostream"

struct SymbolToken {

    SymbolToken(const std::string& nname) : name(nname){};

    bool operator==(const SymbolToken& other) const {
        return name == other.name;
    };

    std::string name;
};

struct QuoteToken {
    bool operator==(const QuoteToken&) const {
        return true;
    };
};

struct DotToken {
    bool operator==(const DotToken&) const {
        return true;
    };
};

enum class BracketToken { OPEN, CLOSE };

struct ConstantToken {
    ConstantToken(int val) : value(val){};

    bool operator==(const ConstantToken& other) const {
        return value == other.value;
    };

    int value;
};

struct BooleanToken {
    BooleanToken(bool vval) : val(vval){};

    bool operator==(const BooleanToken& other) const {
        return val == other.val;
    }
    bool val;
};

using Token =
    std::variant<ConstantToken, BracketToken, SymbolToken, QuoteToken, DotToken, BooleanToken>;

class Tokenizer {
public:
    Tokenizer(std::istream* in) : in_(in) {
        Next();
    };

    bool IsEnd() {
        return is_end_;
    };

    void Next() {
        Cases token_type = None;
        std::string buffer;

        while (true) {
            if ((*in_).peek() == EOF && token_type == None) {
                is_end_ = true;
                return;
            } else if ((*in_).peek() == EOF) {
                break;
            }
            char symb = static_cast<char>((*in_).peek());
            if (symb == ' ' || symb == '\t' || symb == '\v' || symb == '\n') {
                if (token_type != None) {
                    break;
                }
                (*in_).get();
                continue;
            } else if (std::isdigit(symb)) {
                if (token_type == None) {
                    token_type = Constant;
                }

                if (token_type == Constant) {
                    buffer += symb;
                    (*in_).get();
                } else {
                    break;
                }
            } else if (symb == '.') {
                if (token_type == None) {
                    token_type = Dot;
                    buffer += symb;
                    (*in_).get();
                }
                break;
            } else if (symb == '\'') {
                if (token_type == None) {
                    token_type = Quote;
                    buffer += symb;
                    (*in_).get();
                }
                break;
            } else if (symb == ')' || symb == '(') {
                if (token_type == None) {
                    token_type = Bracket;
                    buffer += symb;
                    (*in_).get();
                }
                break;
            } else {
                if (token_type == None) {
                    bool is_correct = false;
                    for (char c : "<=>*/#!-+") {
                        if (c == symb || std::isalpha(symb)) {
                            token_type = Symbol;
                            buffer += symb;
                            (*in_).get();
                            is_correct = true;
                            break;
                        }
                    }
                    if (!is_correct) {
                        throw SyntaxError("Invalid symbol");
                    }
                } else if (token_type == Symbol) {
                    bool is_correct = false;
                    for (char c : "*/#?!-") {
                        if (c == symb || std::isalpha(symb) || std::isdigit(symb)) {
                            token_type = Symbol;
                            buffer += symb;
                            (*in_).get();
                            is_correct = true;
                            break;
                        }
                    }
                    if (!is_correct) {
                        throw SyntaxError("Invalid symbol");
                    }
                } else {
                    break;
                }

                if (buffer == "#" && (static_cast<char>((*in_).peek()) == 'f' ||
                                      static_cast<char>((*in_).peek()) == 't')) {
                    token_type = Boolean;
                    buffer += static_cast<char>((*in_).get());
                    break;
                } else if ((buffer == "+" || buffer == "-") &&
                           std::isdigit(static_cast<char>((*in_).peek()))) {
                    token_type = Constant;
                    buffer += static_cast<char>((*in_).get());
                }
            }
        }

        if (token_type == Constant) {
            cur_token_ = ConstantToken(std::stoi(buffer));
        } else if (token_type == Symbol) {
            cur_token_ = SymbolToken(buffer);
        } else if (token_type == Bracket) {
            if (buffer == ")") {
                cur_token_ = BracketToken::CLOSE;
            } else {
                cur_token_ = BracketToken::OPEN;
            }
        } else if (token_type == Quote) {
            cur_token_ = QuoteToken();
        } else if (token_type == Dot) {
            cur_token_ = DotToken();
        } else if (token_type == Boolean) {
            if (buffer.back() == 't') {
                cur_token_ = BooleanToken(true);
            } else {
                cur_token_ = BooleanToken(false);
            }
        }
    };

    Token GetToken() {
        return cur_token_;
    };

private:
    std::istream* in_;
    bool is_end_ = false;
    Token cur_token_ = BooleanToken(true);

    enum Cases { Symbol, Quote, Bracket, Constant, Dot, Boolean, None };
};
