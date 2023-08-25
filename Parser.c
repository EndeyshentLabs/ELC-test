#include "Parser.h"
#include "Hashmap.h"
#include "Token.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

Hashmap config = { 0 };

#define TYPE_CHECK(enumType, str)                                                                                                                                                                                     \
    if (strcmp(text, str) == 0) {                                                                                                                                                                                     \
        if (tokens.tokens[i + 1].type != enumType && (nillable == 1 && tokens.tokens[i + 1].type != TOKEN_TYPE_NIL)) {                                                                                                \
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
        case TOKEN_TYPE_NILLABLE: {
            if (tokens.tokens[i - 1].type != TOKEN_TYPE_TYPE) {
                fprintf(stderr, "%s:%d:%d: ERROR: Expected type before `?`.\n", "<CHANGE_IT>", curTok.line, curTok.col);
                exit(71);
            }
        } break;
        case TOKEN_TYPE_TYPE: {
            if (i + 1 > tokens.size || (tokens.tokens[i + 1].type != TOKEN_TYPE_IDENTIFIER && tokens.tokens[i + 1].type != TOKEN_TYPE_NILLABLE)) {
                fprintf(stderr, "%s:%d:%d: ERROR: Expected `?` or identifier after type.\n", "<CHANGE_IT>", curTok.line, curTok.col);
                exit(71);
            }
        } break;
        case TOKEN_TYPE_ASSIGN: {
            int nillable = 0;

            if ((int)i - 1 < 0 || tokens.tokens[i - 1].type != TOKEN_TYPE_IDENTIFIER) {
                fprintf(stderr, "%s:%d:%d: ERROR: Expected identifier before `=`\n", "<CHANGE_IT>", curTok.line, curTok.col);
                exit(71);
            }

            if ((int)i - 2 < 0 || (tokens.tokens[i - 1].type != TOKEN_TYPE_NILLABLE && tokens.tokens[i - 1].type != TOKEN_TYPE_IDENTIFIER)) {
                fprintf(stderr, "%s:%d:%d: ERROR: Identifier or nillable qualifier(`?`) before `=`\n", "<CHANGE_IT>", curTok.line, curTok.col);
                exit(71);
            }
            if (tokens.tokens[i - 2].type == TOKEN_TYPE_NILLABLE) {
                nillable = 1;
            }

            if (i + 1 > tokens.size
                || ((tokens.tokens[i + 1].type != TOKEN_TYPE_INT && tokens.tokens[i + 1].type != TOKEN_TYPE_FLOAT && tokens.tokens[i + 1].type != TOKEN_TYPE_CHAR && tokens.tokens[i + 1].type != TOKEN_TYPE_STRING && tokens.tokens[i + 1].type != TOKEN_TYPE_BOOL)
                    && (nillable && tokens.tokens[i + 1].type != TOKEN_TYPE_NIL))) {
                fprintf(stderr, "%s:%d:%d: ERROR: Expected data litaral after `=` but got `%s`\n", "<CHANGE_IT>", curTok.line, curTok.col, tokens.tokens[i + 1].text);
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

            TYPE_CHECK(TOKEN_TYPE_INT, "int")
            TYPE_CHECK(TOKEN_TYPE_FLOAT, "float")
            TYPE_CHECK(TOKEN_TYPE_STRING, "string")
            TYPE_CHECK(TOKEN_TYPE_CHAR, "character")
            TYPE_CHECK(TOKEN_TYPE_BOOL, "bool")
            TYPE_CHECK(TOKEN_TYPE_NIL, "nil")

            free(text);

            for (size_t i = 0; i < config.size; i++) {
                if (strcmp(config.data[i].key, tokens.tokens[i - 1].text) == 0) {
                    fprintf(stderr, "%s:%d:%d: ERROR: Variable with that name already exists!\n", "<CHANGE_IT>", curTok.line, curTok.col);
                    Hashmap_free(&config);
                    exit(71);
                }
            }

            Hashmap_push(&config, tokens.tokens[i - 1].text, tokens.tokens[i + 1].text, tokens.tokens[i + 1].type);
        } break;
        case TOKEN_TYPE_IDENTIFIER:
        case TOKEN_TYPE_PLUS:
        case TOKEN_TYPE_MINUS:
        case TOKEN_TYPE_MULT:
        case TOKEN_TYPE_DIV:
        case TOKEN_TYPE_INT:
        case TOKEN_TYPE_FLOAT:
        case TOKEN_TYPE_CHAR:
        case TOKEN_TYPE_STRING:
        case TOKEN_TYPE_NIL:
        case TOKEN_TYPE_BOOL:
            break;
        default:
            assert(0 && "ELC_parseTokenVector: unreachable");
        }
    }
}
