#ifndef ELC_LEXER_H_
#define ELC_LEXER_H_

#include "Token.h"

typedef struct {
    const char* filename;

    unsigned int pos;
    unsigned int line;

    const char* input;
    char curChar;
} Lexer;

void ELC_Lexer_init(Lexer* l, const char* input, int isfile);

void ELC_Lexer_advance(Lexer* l);
Token ELC_Lexer_makeIdentifier(Lexer* l);
Token ELC_Lexer_makeNumber(Lexer* l);
void ELC_Lexer_parseFromMemory(Lexer* l);

#endif