#ifndef ELC_TOKEN_H_
#define ELC_TOKEN_H_

#include <stdlib.h>

typedef enum {
    TOKEN_TYPE_IDENTIFIER = 0,
    TOKEN_TYPE_NIL,
    TOKEN_TYPE_NILLABLE,
    TOKEN_TYPE_TYPE,
    TOKEN_TYPE_ASSIGN,
    TOKEN_TYPE_PLUS, // Unused
    TOKEN_TYPE_MINUS, // Unused
    TOKEN_TYPE_MULT, // Unused
    TOKEN_TYPE_DIV, // Unused
    TOKEN_TYPE_INT,
    TOKEN_TYPE_FLOAT,
    TOKEN_TYPE_STRING,
    TOKEN_TYPE_CHAR,
    TOKEN_TYPE_BOOL // TODO: Not implemented
} TokenType;

const char* TokenType_toString(TokenType type);

#define TYPES_COUNT 5

extern const char* types[TYPES_COUNT];

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
