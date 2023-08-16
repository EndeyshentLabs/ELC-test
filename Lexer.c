#include "Lexer.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>

#include "Token.h"

#define TODO(...) printf("%s:%d TODO: %s\n", __FILE__, __LINE__, __VA_ARGS__)

void ELC_Lexer_init(Lexer* l, const char* input, int isfile) {
    l->input = input;

    assert(strlen(l->input) > 0);

    l->curChar = *l->input;

    if (!isfile) {
        l->filename = "<memory>";
        ELC_Lexer_parseFromMemory(l, input);
    }
    else {
        assert(0 && "File lexing is not implemented yet");
    }
}

void ELC_Lexer_advance(Lexer* l) {
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

Token ELC_Lexer_makeIdentifier(Lexer* l) {
    char* idString = malloc(1024);
    assert(idString != NULL && "BUY MORE RAM lol");
    memset(idString, 0, 1024);

    unsigned int startLine = l->line;
    unsigned int startPos = l->pos;
    int exitChar = 0;

    while (l->curChar != '\0' && isalnum(l->curChar)) {
        idString[strlen(idString)] = l->curChar;
        printf("    %c\n", l->curChar);

        ELC_Lexer_advance(l);
    }

    TokenType type = IDENTIFIER;

    for (size_t i = 0; i < KEYWORD_COUNT; i++) {
        if (strcmp(idString, keywords[i]) == 0) {
            type = KEYWORD;
            break;
        }
    }

    printf("idString: %s\n", idString);

    Token token = { .type = type, .text = idString, .line = startLine, .col = startPos };

    return token;
}

Token ELC_Lexer_makeNumber(Lexer* l) {
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

    Token tok = { .type = ((dotCount == 1) ? FLOAT : INT), .text = numStr, .line = startLine, .col = startPos };

    return tok;
}

Token ELC_Lexer_makeString(Lexer* l) {
    char* string = malloc(1024);
    assert(string != NULL && "BUY MORE RAM lol");
    memset(string, 0, 1024);

    unsigned int startLine = l->line;
    unsigned int startPos = l->pos;

    ELC_Lexer_advance(l);

    while (l->curChar != '"') {
        if (l->curChar == '\0') {
            printf("%s:%d:%d: ERROR: Unclosed string.\n", l->filename, startLine + 1, startPos + 1);
            exit(70);
        }
        string[strlen(string)] = l->curChar;

        ELC_Lexer_advance(l);
    }

    Token tok = { .type = STRING, .text = string, .line = startLine, .col = startPos };

    return tok;
}

void ELC_Lexer_parseFromMemory(Lexer* l) {
    TokenVector tokens = { 0 };

    TokenVector_init(&tokens);

    assert(l->input != NULL);
    assert(l->curChar != NULL);

    while (l->curChar != '\0') {
        if (l->curChar == '\t' || l->curChar == ' ' || l->curChar == "\r") {
            ELC_Lexer_advance(l);
        }
        else if (isalpha(l->curChar)) {
            Token tok = ELC_Lexer_makeIdentifier(l, l->input);
            TokenVector_push(&tokens, &tok);
        }
        else if (isdigit(l->curChar)) {
            Token tok = ELC_Lexer_makeNumber(l, l->input);
            TokenVector_push(&tokens, &tok);
            while (isdigit(l->curChar) || l->curChar == '.') {
                ELC_Lexer_advance(l);
            }
        }
        else if (l->curChar == '?') {
            Token tok = { .type = NILLABLE, .text = "?", .line = l->line, .col = l->pos };
            TokenVector_push(&tokens, &tok);
            ELC_Lexer_advance(l);
        }
        else if (l->curChar == '=') {
            Token tok = { .type = ASSIGN, .text = "=", .line = l->line, .col = l->pos };
            TokenVector_push(&tokens, &tok);
            ELC_Lexer_advance(l);
        }
        else if (l->curChar == '"') {
            Token tok = ELC_Lexer_makeString(l);
            TokenVector_push(&tokens, &tok);
            ELC_Lexer_advance(l);
        }
        else {
            printf("%s:%d:%d: ERROR: Unknown token. Starts with %c\n", l->filename, l->line, l->pos, l->curChar);
            exit(70);
        }
    }

    TokenVector_display(&tokens);

    TokenVector_free(&tokens);
}