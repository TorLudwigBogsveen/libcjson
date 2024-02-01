/**
 * @file
 */
#ifndef JSON_TOKENIZER_H
#define JSON_TOKENIZER_H

#include <stdio.h>
#include "vector.h"
#include "dynamic_string.h"

#define JSON_TOKENIZER_SEPARATORS "{}[]\",:"

#define JSON_TOKENIZER_TYPE_SEPARATOR 1
#define JSON_TOKENIZER_TYPE_WORD 2

typedef enum JTTokenType {
  JSON_TOKEN_TYPE_LEFT_CURLY,
  JSON_TOKEN_TYPE_RIGHT_CURLY,
  JSON_TOKEN_TYPE_LEFT_SQUARE,
  JSON_TOKEN_TYPE_RIGHT_SQUARE,
  JSON_TOKEN_TYPE_QUOTE,
  JSON_TOKEN_TYPE_COMMA,
  JSON_TOKEN_TYPE_COLON,
  // JSON_TOKEN_TYPE_LEFT_PARENS,
  // JSON_TOKEN_TYPE_RIGHT_PARENS
} JTTokenType;

typedef struct Unit{} Unit;

typedef union JTTokenValue {
  String string;
  char ch;
  Unit nothing;
} JTTokenValue;


typedef struct JTToken
{
  JTTokenType type;
  JTTokenValue data;
} JTToken;

DECLARE_VECTOR_TYPE(JTTokenList, jt, JTToken);


void jt_tokenizer(JTTokenList *token_list, String input);

JTTokenList jt_new_token_list();

void jt_print_token_list(JTTokenList *token_list);

#endif