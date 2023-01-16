#include "scheme.h"
#include "tokenizer.h"
#include "parser.h"
#include <sstream>

std::string Interpreter::Run(const std::string& s) {
    if (!global_) {
        global_ = std::make_shared<Scope>();
    }

    std::stringstream ss(s);
    Tokenizer tokenizer(&ss);

    auto input_ast = Read(&tokenizer, true);

    std::shared_ptr<Object> out_ast;
    if (!input_ast) {
        throw RuntimeError("Invalid expression");
    } else {
        out_ast = input_ast->Eval(global_);
    }

    return out_ast->Serrialize();
}
