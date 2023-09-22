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


typedef struct JTToken
{
  int type;
  String data;
} JTToken;

DECLARE_VECTOR_TYPE(JTTokenList, jt, JTToken);


void jt_tokenizer(JTTokenList *token_list, String input);

JTTokenList jt_new_token_list();

void jt_print_token_list(JTTokenList *token_list);

#endif