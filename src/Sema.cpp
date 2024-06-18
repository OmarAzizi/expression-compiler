/*
    Semantic analysis will be done using the Visitor.

    The basic idea is that the name of each declared variable is stored in 
    a set. During the creation of the set, each name can be checked for 
    uniqueness, and later it can be checked that the given name is in the set.
*/

#include "Sema.h"
#include "AST.h"
#include "llvm/ADT/StringSet.h"
#include "llvm/Support/raw_ostream.h"

namespace {

class DeclCheck : public ASTVisitor {
    llvm::StringSet<> Scope;
    bool HasError;
    enum ErrorType { Twice, Not };
    void error(ErrorType ET, llvm::StringRef V) {
        llvm::errs() << "Variable " << V << " "
                     << (ET == Twice ? "already" : "not")
                     << "defined\n";
        HasError = true;
    }

public:
    DeclCheck() : HasError(false) {}

    bool hasError() { return HasError; }

    virtual void visit(Factor& Node) override {
        if (Node.getKind() == Factor::Ident) {
            /* Check if the variable was defined */
            if (Scope.find(Node.getVal()) == Scope.end())
                error(Not, Node.getVal());
        }
    }

    virtual void visit(BinaryOp& Node) override {
    /* 
            For BinaryOp there is nothing to check other than 
            both sides exist and are visited 
    */
        if (Node.getLeft()) Node.getLeft()->accept(*this);
        else HasError = true;

        if (Node.getRight()) Node.getRight()->accept(*this);
        else HasError = true;
    }

    virtual void visit(WithDecl& Node) override {
        for (auto I = Node.begin(), E = Node.end(); I != E; ++I) {
            if (!Scope.insert(*I).second)
                error(Twice, *I);
        }

        if (Node.getExpr()) Node.getExpr()->accept(*this);
        else HasError = true;
    }
};
}

/* This method only starts the tree walk and return the error flag */
bool Sema::semantic(AST* Tree) {
    if (!Tree) return false;
    DeclCheck Check;
    Tree->accept(Check);
    return Check.hasError();
}
