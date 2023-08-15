#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "Token.h"

#define advance() \
    ++pos; \
    ++input

Token ELC_makeIdentifier(const char* input) {
    assert(0 && "NOT IMPLEMENTED YET");
}

Token ELC_makeNumber(const char* input) {
    assert(0 && "NOT IMPLEMENTED YET");
}

void ELC_parseFromMemory(const char* input) {
    unsigned int pos = 0;

    TokenVector tokens;
    TokenVector_init(&tokens);

    while (*input != '\0') {
        if (isspace(*input)) {
            advance();
        } else if (isalnum(*input)) {
            Token tok = ELC_makeIdentifier(input);
            TokenVector_push(&tokens, &tok);
        } else if (isdigit(*input)) {
            Token tok = ELC_makeNumber(input);
            TokenVector_push(&tokens, &tok);
        } else if (*input == '?') {
            Token tok = { .type = NILLABLE, .line = 1, .col = pos };
            TokenVector_push(&tokens, &tok);
            advance();
        } else {
            printf("1:%d: [ERROR] Unknown token. Starts with %c\n", pos, *input);
        }
    }

    TokenVector_free(&tokens);
}

int main(void) {
    const char* input = "float? pi = 3.1415926535898";

    ELC_parseFromMemory(input);

    return 0;
}
