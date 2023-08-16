#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "Lexer.h"

int main(void) {
    char* input =
        "float? pi = 3.1415926535898\n"
        "string str = \"Hello, World!\"";
    Lexer l = { 0 };
    ELC_Lexer_init(&l, input, 0);

    return 0;
}