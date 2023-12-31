#include "Lexer.h"

#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Hashmap.h"
#include "Parser.h"
#include "Token.h"

#define TODO(...) printf("%s:%d TODO: %s\n", __FILE__, __LINE__, __VA_ARGS__)

#ifndef DEBUG
#define PRINTF(...) //
#else
#define PRINTF printf
#endif

Hashmap* ELC_Lexer_init(Lexer* l, const char* input, int isfile)
{
    l->input = input;

    assert(strlen(l->input) > 0);

    l->curChar = *l->input;

    if (!isfile) {
        l->filename = "<memory>";
        ELC_Lexer_parseFromMemory(l);
    } else {
        assert(0 && "File lexing is not implemented yet");
    }

    return &config;
}

void ELC_Lexer_advance(Lexer* l)
{
    l->pos += 1;
    l->input += 1;
    l->curChar = *l->input;
    if (l->curChar == '\n') {
        ++l->line;
        l->pos = 0;
        l->input += 1;
        l->curChar = *l->input;
    }
}

Token ELC_Lexer_makeIdentifier(Lexer* l)
{
    char* idString = malloc(1024);
    assert(idString != NULL && "BUY MORE RAM lol");
    memset(idString, 0, 1024);

    unsigned int startLine = l->line;
    unsigned int startPos = l->pos;

    while (l->curChar != '\0' && isalnum(l->curChar)) {
        if (l->line > startLine)
            break;
        idString[strlen(idString)] = l->curChar;
        PRINTF("    %c\n", l->curChar);

        ELC_Lexer_advance(l);
    }

    TokenType type = TOKEN_TYPE_IDENTIFIER;

    for (size_t i = 0; i < TYPES_COUNT; i++) {
        if (strcmp(idString, types[i]) == 0) {
            type = TOKEN_TYPE_TYPE;
            break;
        }
    }

    if (strcmp(idString, "nil") == 0) {
        type = TOKEN_TYPE_NIL;
    } else if (strcmp(idString, "true") == 0 || strcmp(idString, "false") == 0) {
        type = TOKEN_TYPE_BOOL;
    }

    PRINTF("idString: %s\n", idString);

    Token token = {
        .type = type, .text = strdup(idString), .line = startLine, .col = startPos
    };

    free(idString);

    return token;
}

Token ELC_Lexer_makeNumber(Lexer* l)
{
    char* numStr = malloc(1024);
    assert(numStr != NULL && "BUY MORE RAM lol");
    memset(numStr, 0, 1024);

    unsigned int dotCount = 0;
    unsigned int startLine = l->line;
    unsigned int startPos = l->pos;

    while (l->curChar != '\0' && (isdigit(l->curChar) || l->curChar == '.')) {
        if (l->curChar == '.') {
            if (dotCount == 1)
                break;
            ++dotCount;
        }

        numStr[strlen(numStr)] = l->curChar;

        ELC_Lexer_advance(l);
    }

    Token tok = { .type = ((dotCount == 1) ? TOKEN_TYPE_FLOAT : TOKEN_TYPE_INT),
        .text = strdup(numStr),
        .line = startLine,
        .col = startPos };

    free(numStr);

    return tok;
}

Token ELC_Lexer_makeString(Lexer* l)
{
    char* string = malloc(1024);
    assert(string != NULL && "BUY MORE RAM lol");
    memset(string, 0, 1024);

    unsigned int startLine = l->line;
    unsigned int startPos = l->pos;

    ELC_Lexer_advance(l);

    while (l->curChar != '"') {
        if (l->curChar == '\0') {
            printf("%s:%d:%d: ERROR: Unclosed string.\n", l->filename, startLine + 1,
                startPos + 1);
            exit(70);
        }
        string[strlen(string)] = l->curChar;

        ELC_Lexer_advance(l);
    }

    Token tok = {
        .type = TOKEN_TYPE_STRING, .text = strdup(string), .line = startLine, .col = startPos
    };

    free(string);

    return tok;
}

Token ELC_Lexer_makeChar(Lexer* l)
{
    char* chr = malloc(2);
    assert(chr != NULL && "BUY MORE RAM lol");
    memset(chr, 0, 2);

    unsigned int startLine = l->line;
    unsigned int startPos = l->pos;

    ELC_Lexer_advance(l);

    chr[0] = l->curChar;

    ELC_Lexer_advance(l);

    if (l->curChar != '\'') {
        printf("%s:%d:%d: ERROR: Unclosed char literal.\n", l->filename,
            startLine, startPos);
        printf("          NOTE: Character literals are the lenght of 1.\n");
        exit(70);
    }

    Token tok = { .type = TOKEN_TYPE_CHAR, .text = strdup(chr), .line = l->line, .col = l->pos };

    free(chr);

    return tok;
}

void ELC_Lexer_parseFromMemory(Lexer* l)
{
    TokenVector tokens = { 0 };

    TokenVector_init(&tokens);

    assert(l->input != NULL);
    assert(l->curChar != '\0');

    while (l->curChar != '\0') {
        if (l->curChar == '\t' || l->curChar == ' ' || l->curChar == '\r') {
            ELC_Lexer_advance(l);
        } else if (isalpha(l->curChar)) {
            Token tok = ELC_Lexer_makeIdentifier(l);
            TokenVector_push(&tokens, &tok);
        } else if (isdigit(l->curChar)) {
            Token tok = ELC_Lexer_makeNumber(l);
            TokenVector_push(&tokens, &tok);
            while (isdigit(l->curChar) || l->curChar == '.') {
                ELC_Lexer_advance(l);
            }
        } else if (l->curChar == '?') {
            Token tok = {
                .type = TOKEN_TYPE_NILLABLE, .text = strdup("?"), .line = l->line, .col = l->pos
            };
            TokenVector_push(&tokens, &tok);
            ELC_Lexer_advance(l);
        } else if (l->curChar == '=') {
            Token tok = { .type = TOKEN_TYPE_ASSIGN, .text = strdup("="), .line = l->line, .col = l->pos };
            TokenVector_push(&tokens, &tok);
            ELC_Lexer_advance(l);
        } else if (l->curChar == '"') {
            Token tok = ELC_Lexer_makeString(l);
            TokenVector_push(&tokens, &tok);
            ELC_Lexer_advance(l);
        } else if (l->curChar == '\'') {
            Token tok = ELC_Lexer_makeChar(l);
            TokenVector_push(&tokens, &tok);
            ELC_Lexer_advance(l);
        } else {
            printf("%s:%d:%d: ERROR: Unknown token. Starts with %c\n", l->filename,
                l->line, l->pos, l->curChar);
            exit(70);
        }
    }

#ifdef DEBUG
    TokenVector_display(&tokens);
#endif

    ELC_parseTokenVector(tokens);

    TokenVector_free(&tokens);
}
