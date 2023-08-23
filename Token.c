#include "Token.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* types[TYPES_COUNT] = {
    "float",
    "int",
    "string",
    "char",
    "bool"
};

const char* TokenType_toString(TokenType type)
{
    switch (type) {
    case TOKEN_TYPE_IDENTIFIER:
        return "TOKEN_TYPE_IDENTIFIER";
    case TOKEN_TYPE_NIL:
        return "TOKEN_TYPE_NIL";
    case TOKEN_TYPE_NILLABLE:
        return "TOKEN_TYPE_NILLABLE";
    case TOKEN_TYPE_TYPE:
        return "TOKEN_TYPE_TYPE";
    case TOKEN_TYPE_ASSIGN:
        return "TOKEN_TYPE_ASSIGN";
    case TOKEN_TYPE_PLUS:
        return "TOKEN_TYPE_PLUS";
    case TOKEN_TYPE_MINUS:
        return "TOKEN_TYPE_MINUS";
    case TOKEN_TYPE_MULT:
        return "TOKEN_TYPE_MULT";
    case TOKEN_TYPE_DIV:
        return "TOKEN_TYPE_DIV";
    case TOKEN_TYPE_INT:
        return "TOKEN_TYPE_INT";
    case TOKEN_TYPE_FLOAT:
        return "TOKEN_TYPE_FLOAT";
    case TOKEN_TYPE_STRING:
        return "TOKEN_TYPE_STRING";
    case TOKEN_TYPE_CHAR:
        return "TOKEN_TYPE_CHAR";
    case TOKEN_TYPE_BOOL:
        return "TOKEN_TYPE_BOOL";
    default:
        assert(0 && "TokenType_toString: unreachable");
    }
}

void TokenVector_init(TokenVector* vec)
{
    vec->size = 0;
    vec->capacity = 10;
    vec->tokens = malloc(vec->capacity * sizeof(Token));
}

void TokenVector_push(TokenVector* vec, Token* token)
{
    assert(token != NULL && "Token cannot be NULL");
    if (vec->size == vec->capacity) {
        vec->capacity *= 2;
        vec->tokens = realloc(vec->tokens, vec->capacity * sizeof(Token));
        assert(vec->tokens != NULL && "BUY MORE RAM lol");
    }

    vec->tokens[vec->size] = *token;
    vec->size++;
}

void TokenVector_display(TokenVector* vec)
{
    for (size_t i = 0; i < vec->size; i++) {
        printf("Token %zu: %s (line %u, col %u, type %d)\n", i, vec->tokens[i].text, vec->tokens[i].line, vec->tokens[i].col, vec->tokens[i].type);
    }
}

void TokenVector_free(TokenVector* vec)
{
    for (size_t i = 0; i < vec->size; i++) {
        free(&*vec->tokens[i].text);
    }
    free(vec->tokens);
    vec->size = 0;
    vec->capacity = 0;
}
