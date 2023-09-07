#include "json_lexer.h"
#include "malloc.h"
#include <stdlib.h>
#include <string.h>
#include "dynamic_string.h"

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

int jl_tokenize(JLTokenStream *token_stream, const char *str)
{
  int mode = JSON_LEXER_MODE_FIND_OBJECT_START_BRACKET;
  int str_ptr = 0;
  String store = new_string();
  while (str_ptr < strlen(str))
  {
    switch (mode)
    {
    case JSON_LEXER_MODE_FIND_OBJECT_START_BRACKET:
      if (str[str_ptr] != '{')
      {
        printf("formatting error");
        return -1;
      }

      __add_separator_token(token_stream, str[str_ptr]);
      mode = JSON_LEXER_MODE_FIND_KEY;

      break;
    case JSON_LEXER_MODE_FIND_KEY:
      if (str[str_ptr] == '\"')
      {
        char *begin = str + str_ptr + 1;
        char *end = strchr(begin, '\"');
        if (end == NULL)
        {
          printf("Could not find closing \" for key");
          return 0;
        }

        //__add_key_token(token_stream, )
      }
      else
      {
        printf("formatting error");
        return 0;
      }
      break;
    case JSON_LEXER_MODE_VALUE:

      break;
    default:
      break;
    }

    str_ptr++;
  }
}
