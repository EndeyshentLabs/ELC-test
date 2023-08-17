#ifndef ELC_PARSER_H_
#define ELC_PARSER_H_

#include "Token.h"
#include "Hashmap.h"

void ELC_parseTokenVector(TokenVector tokens);

extern Hashmap config;

#endif // ELC_PARSER_H_