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
    free(vec->tokens);
    vec->size = 0;
    vec->capacity = 0;
}