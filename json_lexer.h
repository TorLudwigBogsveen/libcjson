/**
 * @file
 */
#ifndef JSON_LEXER_H
#define JSON_LEXER_H

typedef enum JLTokenName {
  SEPARATOR = 0,
  IDENTIFIER = 1,
  LITERAL = 2,
  KEY = 3
} JLTokenName;

// unsure what the type of the token_value should be
typedef struct JLToken {
  JLTokenName token_name;
  void *token_value;
} JLToken;



#endif