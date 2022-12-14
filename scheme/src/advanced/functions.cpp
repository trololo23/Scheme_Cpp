#include "functions.h"

void ArithmeticCheckThrow(const std::vector<std::shared_ptr<Object>> &args) {
    for (auto ptr : args) {
        if (!ptr || !Is<Number>(ptr)) {
            throw RuntimeError("Invalid expression");
        }
    }
}

bool ArithmeticCheckNoThrow(const std::vector<std::shared_ptr<Object>> &args) {
    for (auto ptr : args) {
        if (!Is<Number>(ptr)) {
            return false;
        }
    }
    return true;
}

bool ValidArg(const std::shared_ptr<Object> &ptr) {
    if (!ptr || !(Is<Number>(ptr) || Is<Symbol>(ptr))) {
        return false;
    }
    return true;
}

std::vector<std::shared_ptr<Object>> GetArgsVec(std::shared_ptr<Object> root,
                                                std::shared_ptr<Scope> scope) {
    std::vector<std::shared_ptr<Object>> ans;
    auto cur = As<Cell>(root);
    std::string func_name = As<Symbol>(cur->GetFirst())->GetName();

    while (cur->GetSecond()) {
        if (!Is<Cell>(cur->GetSecond())) {
            ans.push_back(cur->GetSecond());
            return ans;
        }
        cur = As<Cell>(cur->GetSecond());

        if (func_name == "quote" || func_name == "and" || func_name == "or" || func_name == "if" ||
            func_name == "define" || func_name == "set!" || func_name == "lambda" ||
            !cur->GetFirst()) {
            ans.push_back(cur->GetFirst());
        } else {
            ans.push_back(cur->GetFirst()->Eval(scope));
        }
    }
    return ans;
}
