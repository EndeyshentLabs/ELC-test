#include "Parser.h"
#include "Token.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

Hashmap config = { 0 };

#define TYPE_CHECK(enumType, str)                                                                                                                                                                                     \
    if (strcmp(text, str) == 0) {                                                                                                                                                                                     \
        if (tokens.tokens[i + 1].type != enumType && (nillable == 1 && tokens.tokens[i + 1].type != NIL)) {                                                                                                           \
            printf("%s:%d:%d: ERROR: Expected a " str " literal\n", "<CHANGE_IT>", curTok.line, curTok.col);                                                                                                          \
            printf("%s:%d:%d: NOTE: Type defined here\n", "<CHANGE_IT>", nillable == 1 ? tokens.tokens[i - 3].line : tokens.tokens[i - 2].line, nillable == 1 ? tokens.tokens[i - 3].col : tokens.tokens[i - 2].col); \
            exit(71);                                                                                                                                                                                                 \
        }                                                                                                                                                                                                             \
    }

void ELC_parseTokenVector(TokenVector tokens)
{
    Hashmap_init(&config);

    for (size_t i = 0; i < tokens.size; i++) {
        Token curTok = tokens.tokens[i];

        switch (curTok.type) {
        case NILLABLE: {
            if (tokens.tokens[i - 1].type != TYPE) {
                printf("%s:%d:%d: ERROR: Expected type before `?`.\n", "<CHANGE_IT>", curTok.line, curTok.col);
                exit(71);
            }
        } break;
        case TYPE: {
            if (i + 1 > tokens.size || (tokens.tokens[i + 1].type != IDENTIFIER && tokens.tokens[i + 1].type != NILLABLE)) {
                printf("%s:%d:%d: ERROR: Expected `?` or identifier after type.\n", "<CHANGE_IT>", curTok.line, curTok.col);
                exit(71);
            }
        } break;
        case ASSIGN: {
            int nillable = 0;

            if ((int)i - 1 < 0 || tokens.tokens[i - 1].type != IDENTIFIER) {
                printf("%s:%d:%d: ERROR: Expected identifier before `=`\n", "<CHANGE_IT>", curTok.line, curTok.col);
                exit(71);
            }

            if ((int)i - 2 < 0 || (tokens.tokens[i - 1].type != NILLABLE && tokens.tokens[i - 1].type != IDENTIFIER)) {
                printf("%s:%d:%d: ERROR: Identifier or nillable qualifier(`?`) before `=`\n", "<CHANGE_IT>", curTok.line, curTok.col);
                exit(71);
            }
            if (tokens.tokens[i - 2].type == NILLABLE) {
                nillable = 1;
            }

            if (i + 1 > tokens.size
                || (tokens.tokens[i + 1].type != INT && tokens.tokens[i + 1].type != FLOAT && tokens.tokens[i + 1].type != CHAR && tokens.tokens[i + 1].type != STRING)) {
                printf("%s:%d:%d: ERROR: Expected data litaral after `=`\n", "<CHANGE_IT>", curTok.line, curTok.col);
                exit(71);
            }

            char* text = malloc(1024);
            assert(text != NULL && "BUY MORE RAM lol");
            memset(text, 0, 1024);

            if (!nillable) {
                text = strdup(tokens.tokens[i - 2].text);
            } else {
                text = strdup(tokens.tokens[i - 3].text);
            }

            TYPE_CHECK(INT, "int")
            TYPE_CHECK(FLOAT, "float")
            TYPE_CHECK(STRING, "string")
            TYPE_CHECK(CHAR, "character")

            free(text);

            Hashmap_push(&config, tokens.tokens[i - 1].text, tokens.tokens[i + 1].text, tokens.tokens[i + 1].type);
        } break;
        case IDENTIFIER:
        case KEYWORD:
        case PLUS:
        case MINUS:
        case MULT:
        case DIV:
        case INT:
        case FLOAT:
        case CHAR:
        case STRING:
        case NIL:
        case BOOL:
        default:
            break;
        }
    }
}
