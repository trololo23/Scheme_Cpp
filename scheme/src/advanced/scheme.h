#pragma once

#include <string>
#include "unordered_map"
#include "functions.h"

static std::unordered_map<std::string, std::shared_ptr<Object>> func_map = {
    {"+", std::make_shared<PlusFucntion>()},
    {"number?", std::make_shared<IntegerPredicate>()},
    {"-", std::make_shared<MinusFucntion>()},
    {"<", std::make_shared<ArithmLess>()},
    {">", std::make_shared<ArithmMore>()},
    {"<=", std::make_shared<ArithmNoMore>()},
    {">=", std::make_shared<ArithmNoLess>()},
    {"*", std::make_shared<ProductFucntion>()},
    {"/", std::make_shared<DevideFucntion>()},
    {"max", std::make_shared<ArithmMax>()},
    {"min", std::make_shared<ArithmMin>()},
    {"abs", std::make_shared<ArithmAbs>()},
    {"boolean?", std::make_shared<BooleanPredicate>()},
    {"not", std::make_shared<NotPredicate>()},
    {"quote", std::make_shared<Quote>()},
    {"and", std::make_shared<AndFunc>()},
    {"or", std::make_shared<OrFunc>()},
    {"pair?", std::make_shared<PairPredicate>()},
    {"null?", std::make_shared<NullPredicate>()},
    {"list?", std::make_shared<ListPredicate>()},
    {"cons", std::make_shared<ListCons>()},
    {"car", std::make_shared<ListCar>()},
    {"cdr", std::make_shared<ListCdr>()},
    {"list", std::make_shared<List>()},
    {"list-ref", std::make_shared<ListRef>()},
    {"list-tail", std::make_shared<ListTail>()},
    {"define", std::make_shared<Define>()},
    {"symbol?", std::make_shared<SymbolPredicate>()},
    {"set!", std::make_shared<Set>()},
    {"if", std::make_shared<IfFunc>()},
    {"=", std::make_shared<ArithmEqual>()},
    {"set-car!", std::make_shared<SetCar>()},
    {"set-cdr!", std::make_shared<SetCdr>()},
    {"lambda", std::make_shared<LambdaFunc>()}};

class Interpreter {
public:
    Interpreter() {
        global_ = std::make_shared<Scope>(func_map);
    }

    std::string Run(const std::string&);

private:
    std::shared_ptr<Scope> global_;
};
