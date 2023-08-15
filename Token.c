#include "Token.h"

#include <stdio.h>

const char* keywords[KEYWORD_COUNT] = {
    "float",
    "int",
    "string",
    "char",
    "bool"
};

// Function to initialize the token vector
void TokenVector_init(TokenVector* vec) {
    vec->size = 0;
    vec->capacity = 10;  // Initial capacity of 10
    vec->tokens = malloc(vec->capacity * sizeof(Token));
}

// Function to push a token to the token vector
void TokenVector_push(TokenVector* vec, Token* token) {
    // Check if capacity needs to be increased
    if (vec->size == vec->capacity) {
        vec->capacity *= 2;  // Double the capacity
        vec->tokens = realloc(vec->tokens, vec->capacity * sizeof(Token));
    }
    
    // Add the token to the vector
    vec->tokens[vec->size] = *token;
    vec->size++;
}

// Function to display the contents of the token vector
void TokenVector_display(TokenVector* vec) {
    for (size_t i = 0; i < vec->size; i++) {
        printf("Token %zu: %s (line %u, col %u)\n", i+1, vec->tokens[i].text, vec->tokens[i].line, vec->tokens[i].col);
    }
}

// Function to free the memory allocated by the token vector
void TokenVector_free(TokenVector* vec) {
    free(vec->tokens);
    vec->size = 0;
    vec->capacity = 0;
}
