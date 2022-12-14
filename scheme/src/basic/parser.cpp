#include <parser.h>

std::shared_ptr<Object> Read(Tokenizer* tokenizer, bool first_token) {
    std::shared_ptr<Object> ans_obj;
    if (tokenizer->IsEnd()) {
        throw SyntaxError("Invalid expression");
    }
    Token next = tokenizer->GetToken();
    tokenizer->Next();
    if (BracketToken* t = std::get_if<BracketToken>(&next)) {
        if ((*t) == BracketToken::OPEN) {
            ans_obj = ReadList(tokenizer);
        } else {
            ans_obj = std::make_shared<Bracket>();
        }
    } else if (DotToken* t = std::get_if<DotToken>(&next)) {
        ans_obj = std::make_shared<Dot>();
    } else if (SymbolToken* t = std::get_if<SymbolToken>(&next)) {
        ans_obj = std::make_shared<Symbol>(t->name);
    } else if (ConstantToken* t = std::get_if<ConstantToken>(&next)) {
        ans_obj = std::make_shared<Number>(t->value);
    } else if (QuoteToken* t = std::get_if<QuoteToken>(&next)) {
        if (tokenizer->IsEnd()) {
            throw SyntaxError("Invalid expression");
        }
        auto next = Read(tokenizer);
        if (Is<Bracket>(next)) {
            throw SyntaxError("Invalid expression");
        }
        auto cell = std::make_shared<Cell>();
        cell->SetFirst(std::make_shared<Symbol>("quote"));
        auto next_cell = std::make_shared<Cell>();
        next_cell->SetFirst(next);
        cell->SetSecond(next_cell);
        ans_obj = cell;
    } else if (BooleanToken* t = std::get_if<BooleanToken>(&next)) {
        ans_obj = std::make_shared<Boolean>(t->val);
    }
    if (first_token && !tokenizer->IsEnd()) {
        throw SyntaxError("Wrong expression");
    }
    //    if (!ans_obj) {
    //        throw RuntimeError("Wrong expression");
    //    }
    return ans_obj;
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
        if (Is<Number>(next) || Is<Symbol>(next) || Is<Boolean>(next) || Is<Cell>(next) || !next) {
            if (!args_counter) {
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
            if (!cur_ptr->GetFirst()) {
                throw SyntaxError("Invalid expression");
            }
            if (tokenizer->IsEnd()) {
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
