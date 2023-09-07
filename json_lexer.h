/**
 * @file
 */
#ifndef JSON_LEXER_H
#define JSON_LEXER_H

#include <stdio.h>
#include "vector.h"

#define JSON_LEXER_SEPARATORS "{}[]\",:"
#define JSON_LEXER_SEPARATOR_LCB JSON_LEXER_SEPARATORS[0]
#define JSON_LEXER_SEPARATOR_RCB JSON_LEXER_SEPARATORS[1]
#define JSON_LEXER_SEPARATOR_LSB JSON_LEXER_SEPARATORS[2]
#define JSON_LEXER_SEPARATOR_RSB JSON_LEXER_SEPARATORS[3]
#define JSON_LEXER_SEPARATOR_QM JSON_LEXER_SEPARATORS[4]
#define JSON_LEXER_SEPARATOR_C JSON_LEXER_SEPARATORS[5]
#define JSON_LEXER_SEPARATOR_CO JSON_LEXER_SEPARATORS[6]

// the mode to find the first curly bracket of a json object
#define JSON_LEXER_MODE_FIND_OBJECT_START_BRACKET 0
#define JSON_LEXER_MODE_FIND_KEY 1
#define JSON_LEXER_MODE_VALUE 2 

#define JSON_LEXER_TOKEN_NULL 0
#define JSON_LEXER_TOKEN_SEPARATOR 1
#define JSON_LEXER_TOKEN_KEY 2

typedef enum JLTokenName
{
  JNULL = 0,
  SEPARATOR = 1,
  KEY = 2

} JLTokenName;

typedef union JLValue
{
  char character;
  char *string;
} JLValue;

typedef struct JLToken
{
  JLTokenName token_name;
  JLValue token_value;
} JLToken;

DECLARE_VECTOR_TYPE(JLTokenStream, jl, JLToken)

JLToken jl_new_token(JLTokenName token_name, JLValue token_value);
JLTokenStream jl_new_token_stream();

int jl_tokenize(JLTokenStream *token_stream, const char *str);

void jl_print_token_stream(const JLTokenStream token_stream);

#endif