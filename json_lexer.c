#include "json_lexer.h"
#include "malloc.h"
#include <stdlib.h>
#include <string.h>
#include "dynamic_string.h"

DEFINE_VECTOR_TYPE(JLTokenStream, jl, JLToken)

JLTokenStream jl_new_token_stream() {
  return jl_new();
}

JLToken jl_new_token(JLTokenName token_name, JLValue token_value) {
  JLToken token;
  token.token_name = token_name;
  token.token_value = token_value;

  return token;
}

void __add_separator_token(JLTokenStream *token_stream, const char c) {
  JLValue value;
  value.character = c;
  JLToken token = jl_new_token(JSON_LEXER_TOKEN_SEPARATOR, value);
  jl_push(token_stream, token);
}
void __add_key_token(JLTokenStream *token_stream, const char *str) {
  JLValue value;
  value.string = str;
  JLToken token = jl_new_token(JSON_LEXER_TOKEN_KEY, value);
  jl_push(token_stream, token);
}

int __is_separator(const char c) {
  for (int i = 0; i < strlen(JSON_LEXER_SEPARATORS); i++) {
    if (c == JSON_LEXER_SEPARATORS[i])
      return 0;
  }

  return 1;
}

void jl_tokenize(JLTokenStream *token_stream, const char *str) {
  int mode = JSON_LEXER_MODE_NORMAL;
  int str_ptr = 0;
  String store = new_string();

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
        __add_key_token(token_stream, store.ptr);
        store = new_string();
        __add_separator_token(token_stream, str[str_ptr]);
        str_ptr++;
        continue;
      }

      string_push_char(&store, str[str_ptr]);
      break;
    }
    str_ptr++;
  }
}

void jl_print_token_stream(const JLTokenStream token_stream) {
  for (int i = 0; i < token_stream.length; i++) {
    if (token_stream.ptr[i].token_name == JSON_LEXER_TOKEN_KEY ||
        token_stream.ptr[i].token_name == JSON_LEXER_TOKEN_STRING) {
      printf("(%d '%s')", token_stream.ptr[i].token_name,
             token_stream.ptr[i].token_value.string);

    } else
      printf("(%d '%c')", token_stream.ptr[i].token_name,
             token_stream.ptr[i].token_value.character);
  }
}