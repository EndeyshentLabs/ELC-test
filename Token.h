#ifndef ELC_TOKEN_H_
#define ELC_TOKEN_H_

#include <stdlib.h>

typedef enum {
    IDENTIFIER,
    NIL,
    NILLABLE,
    KEYWORD,
    ASSIGN,
    PLUS,
    MINUS,
    MULT,
    DIV,
    INT,
    FLOAT,
    STRING,
    CHAR,
    BOOL
} TokenType;

#define KEYWORD_COUNT 5

extern const char* keywords[KEYWORD_COUNT];

typedef struct {
    TokenType type;
    char* text;
    unsigned int line;
    unsigned int col;
} Token;

typedef struct {
    Token* tokens;
    size_t size;
    size_t capacity;
} TokenVector;

void TokenVector_init(TokenVector* vec);
void TokenVector_push(TokenVector* vec, Token* token);
void TokenVector_display(TokenVector* vec);
void TokenVector_free(TokenVector* vec);

#endif // ELC_TOKEN_H_
