#ifndef SEMA_H
#define SEMA_H

/* Semantic analyzer */

#include "AST.h"
#include "Lexer.h"

class Sema {
public:
    bool semantic(AST* Tree);
};

#endif
