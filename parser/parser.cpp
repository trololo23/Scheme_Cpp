#include <parser.h>

std::shared_ptr<Object> Read(Tokenizer* tokenizer) {
    if (tokenizer->IsEnd()) {
        throw SyntaxError("Inavlid expression");
    }
    Token next = tokenizer->GetToken();
    tokenizer->Next();
    if (BracketToken* t = std::get_if<BracketToken>(&next)) {
        if ((*t) == BracketToken::OPEN) {
            return ReadList(tokenizer);
        } else {
            return std::make_shared<Bracket>();
        }
    } else if (DotToken* t = std::get_if<DotToken>(&next)) {
        return std::make_shared<Dot>();
    } else if (SymbolToken* t = std::get_if<SymbolToken>(&next)) {
        return std::make_shared<Symbol>(t->name);
    } else if (ConstantToken* t = std::get_if<ConstantToken>(&next)) {
        return std::make_shared<Number>(t->value);
    } else if (QuoteToken* t = std::get_if<QuoteToken>(&next)) {
        throw SyntaxError("Inavlid expression");
    } else if (BooleanToken* t = std::get_if<BooleanToken>(&next)) {
        return std::make_shared<Boolean>(t->val);
    }
    return std::shared_ptr<Object>();
};

std::shared_ptr<Object> ReadList(Tokenizer* tokenizer) {
    int args_counter = 0;
    auto cur_ptr = std::make_shared<Cell>();
    auto ans_ptr = std::shared_ptr<Cell>(cur_ptr);
    std::shared_ptr<Object> next;
    while (true) {
        if (tokenizer->IsEnd()) {
            throw SyntaxError("Invalid expression");
        }
        next = Read(tokenizer);
        if (Is<Number>(next) || Is<Symbol>(next) || Is<Boolean>(next)) {
            if (!cur_ptr->GetFirst().get()) {
                cur_ptr->SetFirst(next);
            } else {
                cur_ptr->SetSecond(std::make_shared<Cell>());
                cur_ptr = As<Cell>(cur_ptr->GetSecond());
                cur_ptr->SetFirst(next);
            }
        } else if (Is<Bracket>(next)) {
            if (!args_counter) {
                return std::shared_ptr<Cell>();
            }
            return ans_ptr;
        } else if (Is<Dot>(next)) {
            if (!cur_ptr->GetFirst().get()) {
                throw SyntaxError("Invalid expression");
            }
            next = Read(tokenizer);
            if (Is<Bracket>(next)) {
                throw SyntaxError("Invalid expression");
            }
            cur_ptr->SetSecond(next);
            next = Read(tokenizer);
            if (!Is<Bracket>(next)) {
                throw SyntaxError("Invalid expression");
            }
            return ans_ptr;
        }
        ++args_counter;
    }
}
