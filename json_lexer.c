#include "json_lexer.h"
#include "malloc.h"
#include <stdlib.h>
#include <string.h>
#include <vcruntime.h>
// FIX ME: dynamic token stream is required
JLTokenStream *jl_new_token_stream() {
  JLTokenStream *token_stream = malloc(sizeof(JLTokenStream));
  token_stream->size = 0;
  token_stream->tokens = malloc(sizeof(JLToken *) * 1000);
  return token_stream;
}

JLToken *jl_new_token(JLTokenName token_name, void *token_value) {
  JLToken *token = malloc(sizeof(token));
  token->token_name = token_name;
  token->token_value = token_value;

  return token;
}

int __is_separator(char c) {
  for (int i = 0; i < strlen(JSON_LEXER_SEPARATORS); i++) {
    if (c == JSON_LEXER_SEPARATORS[i])
      return 0;
  }

  return -1;
}

void __add_token(JLTokenStream *token_stream, JLTokenName token_name,
                 void *token_value) {

  token_stream->tokens[token_stream->size] =
      jl_new_token(token_name, token_value);

  token_stream->size++;
}

void jl_tokenize(JLTokenStream *token_stream, const char *str) {

  int str_pointer = 0;

  while (str_pointer < strlen(str)) {
    if (__is_separator(str[str_pointer]) == 0) {
      __add_token(token_stream, 1, (void *)(size_t)str[str_pointer]);
      str_pointer++;
    }
  }
}

void jl_print_token_stream(JLTokenStream *token_stream) {
  for (int i = 0; i < token_stream->size; i++) {
    printf("(%d '%c')", token_stream->tokens[i]->token_name,
           (char)(size_t)(char *)token_stream->tokens[i]->token_value);
  }
}