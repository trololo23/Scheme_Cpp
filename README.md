# Scheme_Cpp

Implementation of an interpreter for a LISP-like programming language, namely some subset of Scheme.

The language interface includes:

1) Primitive types: int, bool char
2) Composite Types: Pairs and Lists
3) Variables with syntactic scope.
4) Functions and lambda expressions

First, the tokeynaser converts the program text into a sequence of atomic tokens. The parser reads a stream of tokens and builds a syntax tree based on them. In the base part, the main process of calculations is organized, a lot of basic functions that work with primitive and composite types are implemented. The advanced part implements support for conditional expressions, the creation of variables and lambda functions that can capture context.
