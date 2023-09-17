#include "json_lexer.h"
#include "malloc.h"
#include <stdlib.h>
#include <string.h>
#include "dynamic_string.h"
#include <stdio.h>
#include <string.h>

DEFINE_VECTOR_TYPE(JLTokenStream, jl, JLToken)

JLTokenStream jl_new_token_stream()
{
  return jl_new();
}

JLToken jl_new_token(JLTokenName token_name, JLValue token_value)
{
  JLToken token;
  token.token_name = token_name;
  token.token_value = token_value;

  return token;
}

void __add_separator_token(JLTokenStream *token_stream, const char c)
{
  JLValue v = {.character = c};
  jl_push(token_stream, jl_new_token(JSON_LEXER_TOKEN_SEPARATOR, v));
}

void __add_key_token(JLTokenStream *token_stream, const char *str)
{
}

//kod tagen från https://www.geeksforgeeks.org/strtok-strtok_r-functions-c-examples/
// Nested-Tokenization in C

int jl_tokenize(JLTokenStream *token_stream, const char *json_str)
{
  printf("%s\n",json_str);

  printf("hello world\n");

  char *str = malloc(sizeof(json_str));

  printf("hello world\n");

  strcpy(str, json_str);

  printf("hello world\n");

  const char outer_delimiters[] = ",";
  const char inner_delimiters[] = ":";

  char *token;
  char *outer_saveptr = NULL;
  char *inner_saveptr = NULL;

  token = strtok_s(str, outer_delimiters, &outer_saveptr);

  while (token != NULL)
  {
    printf("Outer Token: %s\n", token);

    char *inner_token = strtok_s(
        token, inner_delimiters, &inner_saveptr);

    while (inner_token != NULL)
    {
      printf("Inner Token: %s\n", inner_token);
      inner_token = strtok_s(NULL, inner_delimiters,
                             &inner_saveptr);
    }

    token = strtok_s(NULL, outer_delimiters,
                     &outer_saveptr);
  }

  return 0;
}
