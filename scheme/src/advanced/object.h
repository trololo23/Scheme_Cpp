#pragma once

#include "vector"
#include <memory>
#include "error.h"
#include "unordered_map"

class Scope;

class Object : public std::enable_shared_from_this<Object> {
public:
    virtual ~Object() = default;
    virtual std::string Serrialize() = 0;
    virtual std::shared_ptr<Object> Eval(const std::shared_ptr<Scope>& scope) = 0;
};

class Scope {
public:
    Scope() = default;

    Scope(std::unordered_map<std::string, std::shared_ptr<Object>> objects)
        : local_objects_(objects){};

    Scope(std::shared_ptr<Scope> parent) : parent_(parent){};

    Scope(const Scope& other) {
        parent_ = other.parent_;
        local_objects_ = other.local_objects_;
    }

    void AddObject(std::string name, std::shared_ptr<Object> object) {
        local_objects_[name] = object;
    }

    void SimpleSet(std::string name, std::shared_ptr<Object> object) {
        local_objects_[name] = object;
    }
    void SetObject(std::string name, std::shared_ptr<Object> object) {
        if (!Contains(name)) {
            local_objects_[name] = object;
        } else {
            if (!local_objects_.contains(name)) {
                parent_->SetObject(name, object);
            } else {
                local_objects_[name] = object;
            }
        }
    }

    std::shared_ptr<Object> GetObject(const std::string& name) {
        if (Contains(name)) {
            if (local_objects_.contains(name)) {
                return local_objects_[name];
            } else {
                return parent_->GetObject(name);
            }
        } else {
            throw NameError("No such variable");
        }
    }

    bool Contains(const std::string& name) {
        if (local_objects_.contains(name)) {
            return true;
        } else if (parent_) {
            return parent_->Contains(name);
        }
        return false;
    }

private:
    std::unordered_map<std::string, std::shared_ptr<Object>> local_objects_;
    std::shared_ptr<Scope> parent_;
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

    std::shared_ptr<Object> Eval(const std::shared_ptr<Scope>& scope) override {
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

    std::shared_ptr<Object> Eval(const std::shared_ptr<Scope>& scope) override {
        if (!scope->Contains(value_)) {
            throw NameError("No such variable");
        } else {
            return scope->GetObject(value_);
        }
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
    std::shared_ptr<Object> Eval(const std::shared_ptr<Scope>& scope) override {
        return std::make_shared<Boolean>(value_);
    }

private:
    bool value_;
};

class Function : public Object {
public:
    virtual std::shared_ptr<Object> Apply(const std::vector<std::shared_ptr<Object>>& args,
                                          std::shared_ptr<Scope> scope) = 0;

    std::string Serrialize() override {
        return "";
    }

    std::shared_ptr<Object> Eval(const std::shared_ptr<Scope>& scope) override {
        return std::shared_ptr<Object>();
    }
};

std::shared_ptr<Function> ObjToFunc(const std::shared_ptr<Object>& ptr);

std::vector<std::shared_ptr<Object>> GetArgsVec(std::shared_ptr<Object> root,
                                                std::shared_ptr<Scope> scope);

class LambdaObj;

class Cell : public Object {
public:
    Cell() = default;

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

    std::shared_ptr<Object> Eval(const std::shared_ptr<Scope>& scope) override {
        if (!first_) {
            throw RuntimeError("Invalid arguments");
        }
        auto func = first_->Eval(scope);
        if (Is<Cell>(first_) && Is<LambdaObj>(func)) {
            first_ = std::make_shared<Symbol>("kostyl");
        }

        if (Is<Function>(func)) {
            auto function = As<Function>(func);
            auto args = GetArgsVec(std::make_shared<Cell>(first_, second_), scope);
            return function->Apply(args, scope);
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

    std::shared_ptr<Object> Eval(const std::shared_ptr<Scope>& scope) override {
        return std::make_shared<Dot>();
    }
};

class Bracket : public Object {
    std::string Serrialize() override {
        return ")";
    }

    std::shared_ptr<Object> Eval(const std::shared_ptr<Scope>& scope) override {
        return std::make_shared<Bracket>();
    }
};

class Null : public Object {
    std::string Serrialize() override {
        return "()";
    }

    std::shared_ptr<Object> Eval(const std::shared_ptr<Scope>& scope) override {
        return std::shared_ptr<Object>();
    }
};

class LambdaObj : public Function {
public:
    LambdaObj(std::vector<std::string>&& args, std::vector<std::shared_ptr<Object>>&& computations,
              std::shared_ptr<Scope> up_scope)
        : args_(std::move(args)), computations_(std::move(computations)), up_scope_(up_scope){};

    std::shared_ptr<Object> Apply(const std::vector<std::shared_ptr<Object>>& args,
                                  std::shared_ptr<Scope> scope) override {
        auto local_scope = std::make_shared<Scope>(up_scope_);
        if (args.size() != args_.size()) {
            throw RuntimeError("Not enough args");
        }

        for (size_t i = 0; i < args.size(); ++i) {
            local_scope->SimpleSet(args_[i], args[i]);
        }

        for (size_t i = 0; i < computations_.size() - 1; ++i) {
            computations_[i]->Eval(local_scope);
        }
        auto res = computations_.back()->Eval(local_scope);
        return res;
    }

private:
    std::vector<std::string> args_;
    std::vector<std::shared_ptr<Object>> computations_;
    std::shared_ptr<Scope> up_scope_;
};
