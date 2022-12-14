#pragma once

#include "object.h"

void ArithmeticCheckThrow(const std::vector<std::shared_ptr<Object>> &args);

bool ArithmeticCheckNoThrow(const std::vector<std::shared_ptr<Object>> &args);

class PlusFucntion : public Function {
public:
    std::shared_ptr<Object> Apply(const std::vector<std::shared_ptr<Object>> &args,
                                  std::shared_ptr<Scope> scope) override {
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
    std::shared_ptr<Object> Apply(const std::vector<std::shared_ptr<Object>> &args,
                                  std::shared_ptr<Scope> scope) override {
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
    std::shared_ptr<Object> Apply(const std::vector<std::shared_ptr<Object>> &args,
                                  std::shared_ptr<Scope> scope) override {
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
    std::shared_ptr<Object> Apply(const std::vector<std::shared_ptr<Object>> &args,
                                  std::shared_ptr<Scope> scope) override {
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
    std::shared_ptr<Object> Apply(const std::vector<std::shared_ptr<Object>> &args,
                                  std::shared_ptr<Scope> scope) override {
        if (!ArithmeticCheckNoThrow(args)) {
            return std::make_shared<Boolean>(false);
        }
        return std::make_shared<Boolean>(true);
    }
};

class ArithmEqual : public Function {
public:
    std::shared_ptr<Object> Apply(const std::vector<std::shared_ptr<Object>> &args,
                                  std::shared_ptr<Scope> scope) override {
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
    std::shared_ptr<Object> Apply(const std::vector<std::shared_ptr<Object>> &args,
                                  std::shared_ptr<Scope> scope) override {
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
    std::shared_ptr<Object> Apply(const std::vector<std::shared_ptr<Object>> &args,
                                  std::shared_ptr<Scope> scope) override {
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
    std::shared_ptr<Object> Apply(const std::vector<std::shared_ptr<Object>> &args,
                                  std::shared_ptr<Scope> scope) override {
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
    std::shared_ptr<Object> Apply(const std::vector<std::shared_ptr<Object>> &args,
                                  std::shared_ptr<Scope> scope) override {
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
    std::shared_ptr<Object> Apply(const std::vector<std::shared_ptr<Object>> &args,
                                  std::shared_ptr<Scope> scope) override {
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
    std::shared_ptr<Object> Apply(const std::vector<std::shared_ptr<Object>> &args,
                                  std::shared_ptr<Scope> scope) override {
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
    std::shared_ptr<Object> Apply(const std::vector<std::shared_ptr<Object>> &args,
                                  std::shared_ptr<Scope> scope) override {
        ArithmeticCheckThrow(args);
        if (args.size() != 1) {
            throw RuntimeError("Invalid expression");
        }
        return std::make_shared<Number>(abs(As<Number>(args[0])->GetValue()));
    }
};

class BooleanPredicate : public Function {
public:
    std::shared_ptr<Object> Apply(const std::vector<std::shared_ptr<Object>> &args,
                                  std::shared_ptr<Scope> scope) override {
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
    std::shared_ptr<Object> Apply(const std::vector<std::shared_ptr<Object>> &args,
                                  std::shared_ptr<Scope> scope) override {
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
    std::shared_ptr<Object> Apply(const std::vector<std::shared_ptr<Object>> &args,
                                  std::shared_ptr<Scope> scope) override {
        if (args.empty()) {
            return std::make_shared<Boolean>(true);
        }
        for (auto ptr : args) {
            auto obj = ptr->Eval(scope);
            if (Is<Boolean>(obj) && !As<Boolean>(obj)->GetValue()) {
                return obj;
            }
        }
        return args.back()->Eval(scope);
    }
};

class OrFunc : public Function {
public:
    std::shared_ptr<Object> Apply(const std::vector<std::shared_ptr<Object>> &args,
                                  std::shared_ptr<Scope> scope) override {
        if (args.empty()) {
            return std::make_shared<Boolean>(false);
        }
        for (auto ptr : args) {
            auto obj = ptr->Eval(scope);
            if (Is<Boolean>(obj) && As<Boolean>(obj)->GetValue()) {
                return obj;
            }
        }
        return args.back()->Eval(scope);
    }
};

class Quote : public Function {
public:
    std::shared_ptr<Object> Apply(const std::vector<std::shared_ptr<Object>> &args,
                                  std::shared_ptr<Scope> scope) override {
        if (args.empty()) {
            throw RuntimeError("Invalid expression");
        }
        if (!args[0]) {
            return std::make_shared<Null>();
        }
        return args[0];
    }
};

bool ValidArg(const std::shared_ptr<Object> &ptr);

class PairPredicate : public Function {
public:
    std::shared_ptr<Object> Apply(const std::vector<std::shared_ptr<Object>> &args,
                                  std::shared_ptr<Scope> scope) override {
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
    std::shared_ptr<Object> Apply(const std::vector<std::shared_ptr<Object>> &args,
                                  std::shared_ptr<Scope> scope) override {
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
    std::shared_ptr<Object> Apply(const std::vector<std::shared_ptr<Object>> &args,
                                  std::shared_ptr<Scope> scope) override {
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
    std::shared_ptr<Object> Apply(const std::vector<std::shared_ptr<Object>> &args,
                                  std::shared_ptr<Scope> scope) override {
        if (args.size() != 2) {
            throw RuntimeError("Invalid expression");
        }
        auto cell = std::make_shared<Cell>();
        cell->SetFirst(args[0]);
        cell->SetSecond(args[1]);
        return cell;
    }
};

class ListCar : public Function {
public:
    std::shared_ptr<Object> Apply(const std::vector<std::shared_ptr<Object>> &args,
                                  std::shared_ptr<Scope> scope) override {
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
    std::shared_ptr<Object> Apply(const std::vector<std::shared_ptr<Object>> &args,
                                  std::shared_ptr<Scope> scope) override {
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
    std::shared_ptr<Object> Apply(const std::vector<std::shared_ptr<Object>> &args,
                                  std::shared_ptr<Scope> scope) override {
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
    std::shared_ptr<Object> Apply(const std::vector<std::shared_ptr<Object>> &args,
                                  std::shared_ptr<Scope> scope) override {
        if (args.size() != 2) {
            throw RuntimeError("Invalid expression");
        }
        if (!std::make_shared<ListPredicate>()->Apply({args[0]}, scope)) {
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
    std::shared_ptr<Object> Apply(const std::vector<std::shared_ptr<Object>> &args,
                                  std::shared_ptr<Scope> scope) override {
        if (args.size() != 2) {
            throw RuntimeError("Invalid expression");
        }
        if (!std::make_shared<ListPredicate>()->Apply({args[0]}, scope)) {
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

class LambdaFunc : public Function {
public:
    std::shared_ptr<Object> Apply(const std::vector<std::shared_ptr<Object>> &args,
                                  std::shared_ptr<Scope> scope) override {
        if (args.size() < 2) {
            throw SyntaxError("Invalid expression");
        }
        if (args[0] && !Is<Cell>(args[0])) {
            throw SyntaxError("Invalid expression");
        }
        auto func_args = As<Cell>(args[0]);
        std::vector<std::string> variables;
        while (func_args) {
            if (!Is<Symbol>(func_args->GetFirst())) {
                throw SyntaxError("Invalid expression");
            }
            variables.push_back(As<Symbol>(func_args->GetFirst())->GetName());
            func_args = As<Cell>(func_args->GetSecond());
        }
        std::vector<std::shared_ptr<Object>> computations;
        for (size_t i = 1; i < args.size(); ++i) {
            computations.push_back(args[i]);
        }
        auto function_obj =
            std::make_shared<LambdaObj>(std::move(variables), std::move(computations), scope);
        return function_obj;
    }
};

class Define : public Function {
public:
    std::shared_ptr<Object> Apply(const std::vector<std::shared_ptr<Object>> &args,
                                  std::shared_ptr<Scope> scope) override {
        if (args.size() < 2) {
            throw SyntaxError("Invalid expression");
        } else if (Is<Cell>(args[0]) && Is<Symbol>(As<Cell>(args[0])->GetFirst())) {
            std::vector<std::shared_ptr<Object>> arguments;
            std::string name = As<Symbol>(As<Cell>(args[0])->GetFirst())->GetName();
            arguments.push_back(As<Cell>(args[0])->GetSecond());
            for (size_t i = 1; i < args.size(); ++i) {
                arguments.push_back(args[i]);
            }
            auto func_obj = std::make_shared<LambdaFunc>()->Apply(arguments, scope);
            scope->SimpleSet(name, func_obj);
            return std::make_shared<Null>();
        } else if (args.size() == 2) {
            if (!Is<Symbol>(args[0])) {
                throw RuntimeError("Invalid expression");
            }
            auto rhs = args[1]->Eval(scope);
            scope->SetObject(As<Symbol>(args[0])->GetName(), rhs);
            return std::make_shared<Null>();
        } else {
            throw SyntaxError("Invalid expression");
        }
    }
};

class Set : public Function {
public:
    std::shared_ptr<Object> Apply(const std::vector<std::shared_ptr<Object>> &args,
                                  std::shared_ptr<Scope> scope) override {
        if (args.size() != 2) {
            throw SyntaxError("Invalid expression");
        }
        if (!Is<Symbol>(args[0])) {
            throw RuntimeError("Invalid expression");
        }
        std::string name = As<Symbol>(args[0])->GetName();
        auto rhs = args[1]->Eval(scope);
        if (!scope->Contains(name)) {
            throw NameError("No such variable");
        }
        scope->SetObject(As<Symbol>(args[0])->GetName(), rhs);
        return std::make_shared<Null>();
    }
};

class IfFunc : public Function {
public:
    std::shared_ptr<Object> Apply(const std::vector<std::shared_ptr<Object>> &args,
                                  std::shared_ptr<Scope> scope) override {
        if (args.empty()) {
            throw SyntaxError("Invalid expression");
        }
        auto condition = args[0]->Eval(scope);
        if (args.size() == 2) {
            if (!Is<Boolean>(condition) || As<Boolean>(condition)->GetValue()) {
                return args[1]->Eval(scope);
            } else {
                return std::make_shared<Null>();
            }
        } else if (args.size() == 3) {
            if (!Is<Boolean>(condition) || As<Boolean>(condition)->GetValue()) {
                return args[1]->Eval(scope);
            } else {
                return args[2]->Eval(scope);
            }
        } else {
            throw SyntaxError("Invalid expression");
        }
    }
};

class SymbolPredicate : public Function {
public:
    std::shared_ptr<Object> Apply(const std::vector<std::shared_ptr<Object>> &args,
                                  std::shared_ptr<Scope> scope) override {
        if (args.size() != 1) {
            throw RuntimeError("Invalid expression");
        }
        return std::make_shared<Boolean>(Is<Symbol>(args[0]));
    }
};

class SetCar : public Function {
public:
    std::shared_ptr<Object> Apply(const std::vector<std::shared_ptr<Object>> &args,
                                  std::shared_ptr<Scope> scope) override {
        if (args.size() != 2) {
            throw RuntimeError("Invalid expression");
        }
        auto list = args[0];
        if (!Is<Cell>(list)) {
            throw RuntimeError("Invalid expression");
        }

        As<Cell>(list)->SetFirst(args[1]);

        return std::make_shared<Null>();
    }
};

class SetCdr : public Function {
public:
    std::shared_ptr<Object> Apply(const std::vector<std::shared_ptr<Object>> &args,
                                  std::shared_ptr<Scope> scope) override {
        if (args.size() != 2) {
            throw RuntimeError("Invalid expression");
        }
        auto list = args[0];
        if (!Is<Cell>(list)) {
            throw RuntimeError("Invalid expression");
        }

        As<Cell>(list)->SetSecond(args[1]);

        return std::make_shared<Null>();
    }
};

std::vector<std::shared_ptr<Object>> GetArgsVec(std::shared_ptr<Object> root,
                                                std::shared_ptr<Scope> scope);
