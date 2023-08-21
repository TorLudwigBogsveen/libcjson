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

#define JSON_LEXER_MODE_NORMAL 0
#define JSON_LEXER_MODE_GET_KEY_NAME 1

#define JSON_LEXER_TOKEN_JNULL 0
#define JSON_LEXER_TOKEN_SEPARATOR 1
#define JSON_LEXER_TOKEN_IDENTIFIER 2
#define JSON_LEXER_TOKEN_KEY 3
#define JSON_LEXER_TOKEN_NUMBER 4
#define JSON_LEXER_TOKEN_JFLOAT 5
#define JSON_LEXER_TOKEN_STRING 6
#define JSON_LEXER_TOKEN_BOOLEAN 7
#define JSON_LEXER_TOKEN_OBJ 8

typedef enum JLTokenName {
  JNULL = 0,
  SEPARATOR = 1,
  IDENTIFIER = 2,
  KEY = 3,
  NUMBER = 4,
  JFLOAT = 5,
  STRING = 6,
  BOOLEAN = 7,
  OBJ = 8,

} JLTokenName;



// unsure what the type of the token_value should be
typedef struct JLToken {
  JLTokenName token_name;
  void *token_value;
} JLToken;

DECLARE_VECTOR_TYPE(JLTokenStream, jl, JLToken)

JLToken jl_new_token(JLTokenName token_name, void *token_value);
JLTokenStream jl_new_token_stream();

void jl_tokenize(JLTokenStream *token_stream, const char *str);

void jl_print_token_stream(const JLTokenStream token_stream);

#endif