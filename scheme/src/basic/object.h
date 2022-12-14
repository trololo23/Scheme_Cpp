#pragma once

#include "vector"
#include <memory>
#include "error.h"

class Object : public std::enable_shared_from_this<Object> {
public:
    virtual ~Object() = default;
    virtual std::string Serrialize() = 0;
    virtual std::shared_ptr<Object> Eval() = 0;
};

template <class T>
std::shared_ptr<T> As(const std::shared_ptr<Object>& obj) {
    return std::dynamic_pointer_cast<T, Object>(obj);
};

template <class T>
bool Is(const std::shared_ptr<Object>& obj) {
    return As<T>(obj).get();
};

class Number : public Object {
public:
    Number(int number) : value_(number){};

    int64_t GetValue() const {
        return value_;
    };

    std::string Serrialize() override {
        return std::to_string(value_);
    }

    std::shared_ptr<Object> Eval() override {
        return std::make_shared<Number>(value_);
    }

private:
    int64_t value_;
};

class Symbol : public Object {
public:
    Symbol(std::string s) : value_(s){};

    const std::string& GetName() const {
        return value_;
    };

    std::string Serrialize() override {
        return value_;
    }

    std::shared_ptr<Object> Eval() override {
        return std::make_shared<Symbol>(value_);
    }

private:
    std::string value_;
};

class Boolean : public Object {
public:
    Boolean(bool b) : value_(b) {
    }

    bool GetValue() const {
        return value_;
    }

    std::string Serrialize() override {
        if (value_) {
            return "#t";
        } else {
            return "#f";
        }
    }
    std::shared_ptr<Object> Eval() override {
        return std::make_shared<Boolean>(value_);
    }

private:
    bool value_;
};

class Function {
public:
    virtual std::shared_ptr<Object> Apply(const std::vector<std::shared_ptr<Object>>& args) = 0;
};

std::shared_ptr<Function> ObjToFunc(const std::shared_ptr<Object>& ptr);

std::vector<std::shared_ptr<Object>> GetArgsVec(std::shared_ptr<Object> root);

class Cell : public Object {
public:
    Cell(){};

    Cell(std::shared_ptr<Object> first, std::shared_ptr<Object> second)
        : first_(first), second_(second){};

    void SetFirst(std::shared_ptr<Object> ptr) {
        first_ = ptr;
    }

    void SetSecond(std::shared_ptr<Object> ptr) {
        second_ = ptr;
    }

    std::shared_ptr<Object> GetFirst() const {
        return first_;
    };

    std::shared_ptr<Object> GetSecond() const {
        return second_;
    };

    std::string Serrialize() override {
        std::string ans = "(";
        auto cur = std::make_shared<Cell>(first_, second_);
        while (cur) {
            if (cur->GetFirst()) {
                ans += cur->GetFirst()->Serrialize() + " ";
            } else {
                ans += "() ";
            }

            if (cur->GetSecond() && !Is<Cell>(cur->GetSecond())) {
                ans += ". " + cur->GetSecond()->Serrialize() + " ";
                break;
            } else {
                cur = As<Cell>(cur->GetSecond());
            }
        }
        ans.back() = ')';
        return ans;
    }

    std::shared_ptr<Object> Eval() override {
        if (!first_ || Is<Cell>(first_)) {
            throw RuntimeError("Invalid arguments");
        }
        if (Is<Symbol>(first_)) {
            auto function = ObjToFunc(first_);
            auto args = GetArgsVec(std::make_shared<Cell>(first_, second_));
            return function->Apply(args);
        } else {
            throw RuntimeError("Invalid arguments");
        }
    }

private:
    std::shared_ptr<Object> first_;
    std::shared_ptr<Object> second_;
};

class Dot : public Object {
    std::string Serrialize() override {
        return ".";
    }

    std::shared_ptr<Object> Eval() override {
        return std::make_shared<Dot>();
    }
};

class Bracket : public Object {
    std::string Serrialize() override {
        return ")";
    }

    std::shared_ptr<Object> Eval() override {
        return std::make_shared<Bracket>();
    }
};

class Null : public Object {
    std::string Serrialize() override {
        return "()";
    }

    std::shared_ptr<Object> Eval() override {
        return std::shared_ptr<Object>();
    }
};
