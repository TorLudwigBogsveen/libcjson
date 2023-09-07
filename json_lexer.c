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
  JLValue v = {.string = (char*)str};
  jl_push(token_stream, jl_new_token(JSON_LEXER_TOKEN_KEY, v));
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
        const char *begin = str + str_ptr + 1;
        char *end = strchr(begin, '\"');
        if (end == NULL)
        {
          printf("Could not find closing \" for key");
          return -1;
        }

        int length = end - begin;
        char *key = malloc((length+1) * sizeof(char));
        memcpy(key, begin, length * sizeof(char));
        key[length] = '\0';

        __add_key_token(token_stream, key);

        str_ptr += length;
      }
      else
      {
        printf("formatting error");
        return -1;
      }
      break;
    case JSON_LEXER_MODE_VALUE:

      break;
    default:
      break;
    }

    str_ptr++;
  }
  return 0;
}


void jl_print_token_stream(const JLTokenStream token_stream) {
  for (int i = 0; i < token_stream.length; i++) {
    JLToken token = token_stream.ptr[i];
    switch (token.token_name) {
      case JNULL:
        break;
      case SEPARATOR:
        printf("(Separator %c)  ", token.token_value.character);
        break;
      case KEY:
        printf("(key %s)  ", token.token_value.string);
        break;
      default:
        printf("INVALID TOKEN TYPE IN TOKEN STREAM!\n");
        break;
    }
  }
}