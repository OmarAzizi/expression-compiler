#ifndef LEXER_H
#define LEXER_H

#include "llvm/ADT/StringRef.h"
#include "llvm/Support/MemoryBuffer.h"

class Lexer;

class Token {
    friend class Lexer;

public:
    enum TokenKind : unsigned short {
        eoi, unknown, ident, number, comma, colon, plus, 
        minus, star, slash, l_paren, r_paren, KW_with
    };

    TokenKind getKind() const { return Kind; }
    llvm::StringRef getText() const { return Text; }

    bool is(TokenKind K) const { return Kind == K; }
    bool isOneOf(TokenKind K1, TokenKind K2) const { 
        return is(K1) || is(K2);
    }

    template <typename... Ts>
    bool isOneOf(TokenKind K1, TokenKind K2, Ts... Ks) const {
        return is(K1) || isOneOf(K2, Ks...);
    }

private:
    TokenKind Kind;
    llvm::StringRef Text; // Points somewhere int the memory buffer
};

class Lexer {
    const char* BufferStart;
    const char* BufferPtr;
public:
    Lexer(const llvm::StringRef& Buffer) : 
        BufferStart(Buffer.begin()), BufferPtr(BufferStart) {}

    void next(Token& token);
    
private:
    // Populates the members of the Token instance and updates the pointer to the next unprocessed character
    void formToken(Token& Result, const char* TokEnd, Token::TokenKind Kind);
};

#endif
