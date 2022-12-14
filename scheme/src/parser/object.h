#pragma once

#include <memory>

class Object : public std::enable_shared_from_this<Object> {
public:
    virtual ~Object() = default;
};

class Number : public Object {
public:
    Number(int number) : value_(number){};

    int GetValue() const {
        return value_;
    };

private:
    int value_;
};

class Dot : public Object {};

class Symbol : public Object {
public:
    Symbol(std::string s) : value_(s){};

    const std::string& GetName() const {
        return value_;
    };

private:
    std::string value_;
};

class Boolean : public Object {
public:
    Boolean(bool b) : value_(b) {
    }

private:
    bool value_;
};

class Bracket : public Object {};

class Cell : public Object {
public:
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

private:
    std::shared_ptr<Object> first_;
    std::shared_ptr<Object> second_;
};

///////////////////////////////////////////////////////////////////////////////

// Runtime type checking and convertion.
// This can be helpful: https://en.cppreference.com/w/cpp/memory/shared_ptr/pointer_cast

template <class T>
std::shared_ptr<T> As(const std::shared_ptr<Object>& obj) {
    return std::dynamic_pointer_cast<T, Object>(obj);
};

template <class T>
bool Is(const std::shared_ptr<Object>& obj) {
    return As<T>(obj).get();
};
