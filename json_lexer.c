#include "json_lexer.h"
#include "malloc.h"
#include <stdlib.h>
#include <string.h>

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

void __add_separator_token(JLTokenStream *token_stream, const char c) {
  JLToken *token = jl_new_token(JSON_LEXER_TOKEN_SEPARATOR, (void *)(size_t)c);
  token_stream->tokens[token_stream->size] = token;
  token_stream->size++;
}
void __add_key_token(JLTokenStream *token_stream, const char *str) {
  JLToken *token = jl_new_token(JSON_LEXER_TOKEN_KEY, (void *)str);
  token_stream->tokens[token_stream->size] = token;
  token_stream->size++;
}

int __is_separator(const char c) {
  for (int i = 0; i < strlen(JSON_LEXER_SEPARATORS); i++) {
    if (c == JSON_LEXER_SEPARATORS[i])
      return 0;
  }

  return 1;
}

#define STORE_SIZE 1024

// just nu så har vi samma minnes plats för alla värden som sparas i store
// vilket gör att vi skriver över namn osv.
//
// det vi får : (1 '{')(1 '"')(3 'y')(1 '"')(1 ':')(1 ',')(1 '"')(3 'y')(1 '"')(1 ':')(1 '}')
// så det borde vara : (1 '{')(1 '"')(3 'x')(1 '"')(1 ':')(1 ',')(1 '"')(3 'y')(1 '"')(1 ':')(1 '}')

void jl_tokenize(JLTokenStream *token_stream, const char *str) {
  int mode = JSON_LEXER_MODE_NORMAL;
  int str_ptr = 0;
  int store_ptr = 0;
  char *store = calloc(1, sizeof(char) * STORE_SIZE);

  while (str_ptr < strlen(str)) {
    switch (mode) {
    case JSON_LEXER_MODE_NORMAL:
      if (__is_separator(str[str_ptr]) == 0)
        __add_separator_token(token_stream, str[str_ptr]);
      if (__is_separator(str[str_ptr]) == 0 &&
          str[str_ptr] == JSON_LEXER_SEPARATOR_QM) {
        mode = JSON_LEXER_MODE_GET_KEY_NAME;
        str_ptr++;
        continue;
      }
      break;

    case JSON_LEXER_MODE_GET_KEY_NAME:

      if (__is_separator(str[str_ptr]) == 0 &&
          str[str_ptr] == JSON_LEXER_SEPARATOR_QM) {
        mode = JSON_LEXER_MODE_NORMAL;
        store_ptr = 0;
        __add_key_token(token_stream, store);
        __add_separator_token(token_stream, str[str_ptr]);
        str_ptr++;
        char *store = calloc(1, sizeof(char) * STORE_SIZE);
        continue;
      }

      store[store_ptr] = str[str_ptr];
      store_ptr++;
      break;
    }
    str_ptr++;
  }
}

void jl_print_token_stream(JLTokenStream *token_stream) {
  for (int i = 0; i < token_stream->size; i++) {
    if (token_stream->tokens[i]->token_name == JSON_LEXER_TOKEN_KEY ||
        token_stream->tokens[i]->token_name == JSON_LEXER_TOKEN_STRING) {
      printf("(%d '%s')", token_stream->tokens[i]->token_name,
             (char *)token_stream->tokens[i]->token_value);

    } else
      printf("(%d '%c')", token_stream->tokens[i]->token_name,
             (char)(size_t)token_stream->tokens[i]->token_value);
  }
}