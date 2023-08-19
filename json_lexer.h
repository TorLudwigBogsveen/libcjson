/**
 * @file
 */
#ifndef JSON_LEXER_H
#define JSON_LEXER_H

#include <stdio.h>
#define JSON_LEXER_SEPARATORS "{}[]\",:"

typedef enum JLTokenName {
  JNULL = 0,
  SEPARATOR = 1,
  IDENTIFIER = 2,
  LITERAL = 3,
  KEY = 4
} JLTokenName;

// unsure what the type of the token_value should be
typedef struct JLToken {
  JLTokenName token_name;
  void *token_value;
} JLToken;

typedef struct JLTokenStream {
  JLToken **tokens;
  int size;
} JLTokenStream;

JLToken *jl_new_token(JLTokenName token_name, void *token_value);
JLTokenStream *jl_new_token_stream();

void jl_tokenize(JLTokenStream *token_stream, const char *str);

void jl_print_token_stream(JLTokenStream *token_stream);

#endif