#pragma once

#include "object.h"

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

class PlusFucntion : public Function {
public:
    std::shared_ptr<Object> Apply(const std::vector<std::shared_ptr<Object>> &args) override {
        ArithmeticCheckThrow(args);
        if (args.empty()) {
            return std::make_shared<Number>(0);
        } else if (args.size() == 1) {
            return As<Number>(args[0]);
        }
        int64_t ans = 0;
        for (auto ptr : args) {
            ans += As<Number>(ptr)->GetValue();
        }
        return std::make_shared<Number>(ans);
    }
};

class MinusFucntion : public Function {
public:
    std::shared_ptr<Object> Apply(const std::vector<std::shared_ptr<Object>> &args) override {
        ArithmeticCheckThrow(args);
        if (args.empty()) {
            throw RuntimeError("Invalid expression");
        } else if (args.size() == 1) {
            return As<Number>(args[0]);
        }
        int64_t ans = As<Number>(args[0])->GetValue();
        for (size_t i = 1; i < args.size(); ++i) {
            ans -= As<Number>(args[i])->GetValue();
        }
        return std::make_shared<Number>(ans);
    }
};

class ProductFucntion : public Function {
public:
    std::shared_ptr<Object> Apply(const std::vector<std::shared_ptr<Object>> &args) override {
        ArithmeticCheckThrow(args);
        if (args.empty()) {
            return std::make_shared<Number>(1);
        } else if (args.size() == 1) {
            return As<Number>(args[0]);
        }
        int64_t ans = 1;
        for (auto ptr : args) {
            ans *= As<Number>(ptr)->GetValue();
        }
        return std::make_shared<Number>(ans);
    }
};

class DevideFucntion : public Function {
public:
    std::shared_ptr<Object> Apply(const std::vector<std::shared_ptr<Object>> &args) override {
        ArithmeticCheckThrow(args);
        if (args.empty()) {
            throw RuntimeError("Inavlid expression");
        } else if (args.size() == 1) {
            return As<Number>(args[0]);
        }
        int64_t ans = As<Number>(args[0])->GetValue();
        for (size_t i = 1; i < args.size(); ++i) {
            if (!As<Number>(args[i])->GetValue()) {
                throw RuntimeError("Devide Null");
            }
            ans /= As<Number>(args[i])->GetValue();
        }
        return std::make_shared<Number>(ans);
    }
};

class IntegerPredicate : public Function {
public:
    std::shared_ptr<Object> Apply(const std::vector<std::shared_ptr<Object>> &args) override {
        if (!ArithmeticCheckNoThrow(args)) {
            return std::make_shared<Boolean>(false);
        }
        return std::make_shared<Boolean>(true);
    }
};

class ArithmEqual : public Function {
public:
    std::shared_ptr<Object> Apply(const std::vector<std::shared_ptr<Object>> &args) override {
        ArithmeticCheckThrow(args);
        if (args.empty()) {
            return std::make_shared<Boolean>(true);
        }
        for (size_t i = 0; i < args.size() - 1; ++i) {
            if (As<Number>(args[i])->GetValue() != As<Number>(args[i + 1])->GetValue()) {
                return std::make_shared<Boolean>(false);
            }
        }
        return std::make_shared<Boolean>(true);
    }
};

class ArithmLess : public Function {
public:
    std::shared_ptr<Object> Apply(const std::vector<std::shared_ptr<Object>> &args) override {
        ArithmeticCheckThrow(args);
        if (args.empty()) {
            return std::make_shared<Boolean>(true);
        }
        for (size_t i = 0; i < args.size() - 1; ++i) {
            if (As<Number>(args[i])->GetValue() >= As<Number>(args[i + 1])->GetValue()) {
                return std::make_shared<Boolean>(false);
            }
        }
        return std::make_shared<Boolean>(true);
    }
};

class ArithmMore : public Function {
public:
    std::shared_ptr<Object> Apply(const std::vector<std::shared_ptr<Object>> &args) override {
        ArithmeticCheckThrow(args);
        if (args.empty()) {
            return std::make_shared<Boolean>(true);
        }
        for (size_t i = 0; i < args.size() - 1; ++i) {
            if (As<Number>(args[i])->GetValue() <= As<Number>(args[i + 1])->GetValue()) {
                return std::make_shared<Boolean>(false);
            }
        }
        return std::make_shared<Boolean>(true);
    }
};

class ArithmNoLess : public Function {
public:
    std::shared_ptr<Object> Apply(const std::vector<std::shared_ptr<Object>> &args) override {
        ArithmeticCheckThrow(args);
        if (args.empty()) {
            return std::make_shared<Boolean>(true);
        }
        for (size_t i = 0; i < args.size() - 1; ++i) {
            if (As<Number>(args[i])->GetValue() < As<Number>(args[i + 1])->GetValue()) {
                return std::make_shared<Boolean>(false);
            }
        }
        return std::make_shared<Boolean>(true);
    }
};

class ArithmNoMore : public Function {
public:
    std::shared_ptr<Object> Apply(const std::vector<std::shared_ptr<Object>> &args) override {
        ArithmeticCheckThrow(args);
        if (args.empty()) {
            return std::make_shared<Boolean>(true);
        }
        for (size_t i = 0; i < args.size() - 1; ++i) {
            if (As<Number>(args[i])->GetValue() > As<Number>(args[i + 1])->GetValue()) {
                return std::make_shared<Boolean>(false);
            }
        }
        return std::make_shared<Boolean>(true);
    }
};

class ArithmMax : public Function {
public:
    std::shared_ptr<Object> Apply(const std::vector<std::shared_ptr<Object>> &args) override {
        ArithmeticCheckThrow(args);
        if (args.empty()) {
            throw RuntimeError("Invalid expression");
        }
        int64_t ans = As<Number>(args[0])->GetValue();
        for (size_t i = 0; i < args.size(); ++i) {
            ans = std::max(ans, As<Number>(args[i])->GetValue());
        }
        return std::make_shared<Number>(ans);
    }
};

class ArithmMin : public Function {
public:
    std::shared_ptr<Object> Apply(const std::vector<std::shared_ptr<Object>> &args) override {
        ArithmeticCheckThrow(args);
        if (args.empty()) {
            throw RuntimeError("Invalid expression");
        }
        int64_t ans = As<Number>(args[0])->GetValue();
        for (size_t i = 0; i < args.size(); ++i) {
            ans = std::min(ans, As<Number>(args[i])->GetValue());
        }
        return std::make_shared<Number>(ans);
    }
};

class ArithmAbs : public Function {
public:
    std::shared_ptr<Object> Apply(const std::vector<std::shared_ptr<Object>> &args) override {
        ArithmeticCheckThrow(args);
        if (args.size() != 1) {
            throw RuntimeError("Invalid expression");
        }
        return std::make_shared<Number>(abs(As<Number>(args[0])->GetValue()));
    }
};

class BooleanPredicate : public Function {
public:
    std::shared_ptr<Object> Apply(const std::vector<std::shared_ptr<Object>> &args) override {
        if (args.size() != 1) {
            throw RuntimeError("Invalid expression");
        }
        if (Is<Boolean>(args[0])) {
            return std::make_shared<Boolean>(true);
        } else {
            return std::make_shared<Boolean>(false);
        }
    }
};

class NotPredicate : public Function {
public:
    std::shared_ptr<Object> Apply(const std::vector<std::shared_ptr<Object>> &args) override {
        if (args.size() != 1) {
            throw RuntimeError("Invalid expression");
        }

        if (Is<Boolean>(args[0])) {
            return std::make_shared<Boolean>(!As<Boolean>(args[0])->GetValue());
        } else {
            return std::make_shared<Boolean>(false);
        }
    }
};

class AndFunc : public Function {
public:
    std::shared_ptr<Object> Apply(const std::vector<std::shared_ptr<Object>> &args) override {
        if (args.empty()) {
            return std::make_shared<Boolean>(true);
        }
        for (auto ptr : args) {
            auto obj = ptr->Eval();
            if (Is<Boolean>(obj) && !As<Boolean>(obj)->GetValue()) {
                return obj;
            }
        }
        return args.back()->Eval();
    }
};

class OrFunc : public Function {
public:
    std::shared_ptr<Object> Apply(const std::vector<std::shared_ptr<Object>> &args) override {
        if (args.empty()) {
            return std::make_shared<Boolean>(false);
        }
        for (auto ptr : args) {
            auto obj = ptr->Eval();
            if (Is<Boolean>(obj) && As<Boolean>(obj)->GetValue()) {
                return obj;
            }
        }
        return args.back()->Eval();
    }
};

class Quote : public Function {
public:
    std::shared_ptr<Object> Apply(const std::vector<std::shared_ptr<Object>> &args) override {
        if (args.empty()) {
            throw RuntimeError("Invalid expression");
        }
        if (!args[0]) {
            return std::make_shared<Null>();
        }
        return args[0];
    }
};

bool ValidArg(const std::shared_ptr<Object> &ptr) {
    if (!ptr || !(Is<Number>(ptr) || Is<Symbol>(ptr))) {
        return false;
    }
    return true;
}

class PairPredicate : public Function {
public:
    std::shared_ptr<Object> Apply(const std::vector<std::shared_ptr<Object>> &args) override {
        if (args.size() != 1) {
            throw RuntimeError("Invalid expression");
        }
        if (!args[0] || !Is<Cell>(args[0])) {
            return std::make_shared<Boolean>(false);
        }
        auto cell = As<Cell>(args[0]);
        if (!ValidArg(cell->GetFirst()) && !(cell->GetSecond())) {
            return std::make_shared<Boolean>(false);
        }
        if (Is<Cell>(cell->GetSecond())) {
            cell = As<Cell>(cell->GetSecond());
            if (ValidArg(cell->GetFirst()) && !(cell->GetSecond())) {
                return std::make_shared<Boolean>(true);
            }
            return std::make_shared<Boolean>(false);
        } else {
            if (ValidArg(cell->GetSecond())) {
                return std::make_shared<Boolean>(true);
            }
            return std::make_shared<Boolean>(false);
        }
    }
};

class NullPredicate : public Function {
public:
    std::shared_ptr<Object> Apply(const std::vector<std::shared_ptr<Object>> &args) override {
        if (args.size() != 1) {
            throw RuntimeError("Invalid expression");
        }
        if (!args[0] || Is<Null>(args[0])) {
            return std::make_shared<Boolean>(true);
        }
        return std::make_shared<Boolean>(false);
    }
};

class ListPredicate : public Function {
public:
    std::shared_ptr<Object> Apply(const std::vector<std::shared_ptr<Object>> &args) override {
        if (args.size() != 1) {
            throw RuntimeError("Invalid expression");
        }
        if (!args[0] || Is<Null>(args[0])) {
            return std::make_shared<Boolean>(true);
        } else if (!Is<Cell>(args[0])) {
            return std::make_shared<Boolean>(false);
        }
        auto cur = As<Cell>(args[0]);

        while (cur) {
            if (cur->GetSecond() && !Is<Cell>(cur->GetSecond())) {
                return std::make_shared<Boolean>(false);
            } else {
                cur = As<Cell>(cur->GetSecond());
            }
        }
        return std::make_shared<Boolean>(true);
    }
};

class ListCons : public Function {
public:
    std::shared_ptr<Object> Apply(const std::vector<std::shared_ptr<Object>> &args) override {
        if (args.size() != 2) {
            throw RuntimeError("Invalid expression");
        }
        ArithmeticCheckThrow(args);
        auto cell = std::make_shared<Cell>();
        cell->SetFirst(args[0]);
        cell->SetSecond(args[1]);
        return cell;
    }
};

class ListCar : public Function {
public:
    std::shared_ptr<Object> Apply(const std::vector<std::shared_ptr<Object>> &args) override {
        if (args.empty()) {
            throw RuntimeError("Invalid expression");
        }

        if (args[0] && Is<Cell>(args[0])) {
            return As<Cell>(args[0])->GetFirst();
        } else {
            throw RuntimeError("Invalid expression");
        }
    }
};

class ListCdr : public Function {
public:
    std::shared_ptr<Object> Apply(const std::vector<std::shared_ptr<Object>> &args) override {
        if (args.empty()) {
            throw RuntimeError("Invalid expression");
        }

        std::shared_ptr<Object> obj;
        if (args[0] && Is<Cell>(args[0])) {
            obj = As<Cell>(args[0])->GetSecond();
        } else {
            throw RuntimeError("Invalid expression");
        }
        if (!obj) {
            return std::make_shared<Null>();
        }
        return obj;
    }
};

class List : public Function {
public:
    std::shared_ptr<Object> Apply(const std::vector<std::shared_ptr<Object>> &args) override {
        if (args.empty()) {
            return std::make_shared<Null>();
        }
        auto cell = std::make_shared<Cell>();
        auto ans = std::shared_ptr<Cell>(cell);
        cell->SetFirst(args[0]);
        for (size_t i = 1; i < args.size(); ++i) {
            cell->SetSecond(std::make_shared<Cell>());
            cell = As<Cell>(cell->GetSecond());
            cell->SetFirst(args[i]);
        }
        return ans;
    }
};

class ListRef : public Function {
public:
    std::shared_ptr<Object> Apply(const std::vector<std::shared_ptr<Object>> &args) override {
        if (args.size() != 2) {
            throw RuntimeError("Invalid expression");
        }
        if (!std::make_shared<ListPredicate>()->Apply({args[0]})) {
            throw RuntimeError("Invalid expression");
        }
        if (!Is<Number>(args[1])) {
            throw RuntimeError("Invalid expression");
        }
        auto pos = As<Number>(args[1])->GetValue();
        auto cur = As<Cell>(args[0]);
        int64_t counter = 0;
        while (cur) {
            if (counter == pos) {
                return cur->GetFirst();
            }
            cur = As<Cell>(cur->GetSecond());
            ++counter;
        }
        throw RuntimeError("Invalid expression");
    }
};

class ListTail : public Function {
public:
    std::shared_ptr<Object> Apply(const std::vector<std::shared_ptr<Object>> &args) override {
        if (args.size() != 2) {
            throw RuntimeError("Invalid expression");
        }
        if (!std::make_shared<ListPredicate>()->Apply({args[0]})) {
            throw RuntimeError("Invalid expression");
        }
        if (!Is<Number>(args[1])) {
            throw RuntimeError("Invalid expression");
        }
        auto pos = As<Number>(args[1])->GetValue();
        auto cur = As<Cell>(args[0]);
        int64_t counter = 0;
        while (cur) {
            if (counter == pos) {
                return cur;
            }
            cur = As<Cell>(cur->GetSecond());
            ++counter;
        }
        if (counter == pos) {
            return std::make_shared<Null>();
        }
        throw RuntimeError("Invalid expression");
    }
};

std::shared_ptr<Function> ObjToFunc(const std::shared_ptr<Object> &ptr) {
    if (!Is<Symbol>(ptr)) {
        throw SyntaxError("Invalid expression");
    }
    if (As<Symbol>(ptr)->GetName() == "+") {
        return std::make_shared<PlusFucntion>();
    } else if (As<Symbol>(ptr)->GetName() == "number?") {
        return std::make_shared<IntegerPredicate>();
    } else if (As<Symbol>(ptr)->GetName() == "=") {
        return std::make_shared<ArithmEqual>();
    } else if (As<Symbol>(ptr)->GetName() == "<") {
        return std::make_shared<ArithmLess>();
    } else if (As<Symbol>(ptr)->GetName() == ">") {
        return std::make_shared<ArithmMore>();
    } else if (As<Symbol>(ptr)->GetName() == "<=") {
        return std::make_shared<ArithmNoMore>();
    } else if (As<Symbol>(ptr)->GetName() == ">=") {
        return std::make_shared<ArithmNoLess>();
    } else if (As<Symbol>(ptr)->GetName() == "-") {
        return std::make_shared<MinusFucntion>();
    } else if (As<Symbol>(ptr)->GetName() == "*") {
        return std::make_shared<ProductFucntion>();
    } else if (As<Symbol>(ptr)->GetName() == "/") {
        return std::make_shared<DevideFucntion>();
    } else if (As<Symbol>(ptr)->GetName() == "max") {
        return std::make_shared<ArithmMax>();
    } else if (As<Symbol>(ptr)->GetName() == "min") {
        return std::make_shared<ArithmMin>();
    } else if (As<Symbol>(ptr)->GetName() == "abs") {
        return std::make_shared<ArithmAbs>();
    } else if (As<Symbol>(ptr)->GetName() == "boolean?") {
        return std::make_shared<BooleanPredicate>();
    } else if (As<Symbol>(ptr)->GetName() == "not") {
        return std::make_shared<NotPredicate>();
    } else if (As<Symbol>(ptr)->GetName() == "quote") {
        return std::make_shared<Quote>();
    } else if (As<Symbol>(ptr)->GetName() == "and") {
        return std::make_shared<AndFunc>();
    } else if (As<Symbol>(ptr)->GetName() == "or") {
        return std::make_shared<OrFunc>();
    } else if (As<Symbol>(ptr)->GetName() == "pair?") {
        return std::make_shared<PairPredicate>();
    } else if (As<Symbol>(ptr)->GetName() == "null?") {
        return std::make_shared<NullPredicate>();
    } else if (As<Symbol>(ptr)->GetName() == "list?") {
        return std::make_shared<ListPredicate>();
    } else if (As<Symbol>(ptr)->GetName() == "cons") {
        return std::make_shared<ListCons>();
    } else if (As<Symbol>(ptr)->GetName() == "car") {
        return std::make_shared<ListCar>();
    } else if (As<Symbol>(ptr)->GetName() == "cdr") {
        return std::make_shared<ListCdr>();
    } else if (As<Symbol>(ptr)->GetName() == "list") {
        return std::make_shared<List>();
    } else if (As<Symbol>(ptr)->GetName() == "list-ref") {
        return std::make_shared<ListRef>();
    } else if (As<Symbol>(ptr)->GetName() == "list-tail") {
        return std::make_shared<ListTail>();
    }
    throw SyntaxError("Invalid expression");
}

std::vector<std::shared_ptr<Object>> GetArgsVec(std::shared_ptr<Object> root) {
    std::vector<std::shared_ptr<Object>> ans;
    auto cur = As<Cell>(root);
    std::string func_name = As<Symbol>(cur->GetFirst())->GetName();

    while (cur->GetSecond()) {
        if (!Is<Cell>(cur->GetSecond())) {
            ans.push_back(cur->GetSecond());
            return ans;
        }
        cur = As<Cell>(cur->GetSecond());

        if (func_name == "quote" || func_name == "and" || func_name == "or" || !cur->GetFirst()) {
            ans.push_back(cur->GetFirst());
        } else {
            ans.push_back(cur->GetFirst()->Eval());
        }
    }
    return ans;
}
