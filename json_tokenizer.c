#include "json_tokenizer.h"
#include "malloc.h"
#include <stdlib.h>
#include <string.h>
#include "dynamic_string.h"
#include <stdio.h>
#include <string.h>

#include <stdio.h>
#include <string.h>

#include "vector.h"

DEFINE_VECTOR_TYPE(JTTokenList, jt, JTToken);

JTTokenList jt_new_token_list()
{
    return jt_new();
}

int __jt_is_separator(char c)
{
    if (strchr(JSON_TOKENIZER_SEPARATORS, c) != NULL)
        return 1;

    return 0;
}

JTToken __jt_handle_separator(char c)
{
    JTToken token;
    Unit unit;
    JTTokenValue data = { .nothing = unit };
    token.data = data;

    switch (c)
    {
    case '{':
        token.type = JSON_TOKEN_TYPE_LEFT_CURLY;
        break;
    case '}':
        token.type = JSON_TOKEN_TYPE_RIGHT_CURLY;
        break;
    case '[':
        token.type = JSON_TOKEN_TYPE_LEFT_SQUARE;
        break;
    case ']':
        token.type = JSON_TOKEN_TYPE_RIGHT_SQUARE;
        break;
    case '\"':
        token.type = JSON_TOKEN_TYPE_QUOTE;
        break;
    case ':':
        token.type = JSON_TOKEN_TYPE_COLON;
        break;
    default:
        printf("ERROR TOKENIZING SEPARATOR : %c", c);
        break;
    }

    return token;
}

JTToken __jt_handle_word(String input, int *pointer)
{
    int off = 0;
    JTToken token;
    String word = new_string();
    // detta resulterar  i att om man har t.ex " i en text sträng så ses det som en separator, vilket resulterar i att man senare får pussla ihop strängen igen.
    while (!__jt_is_separator(input.ptr[*pointer + off]))
    {
        string_push_char(&word, input.ptr[*pointer + off]);

        off++;
    }

    JTTokenValue data = { .string = word };
    token.data = data;
    token.type = JSON_TOKENIZER_TYPE_WORD;

    pointer += word.length - 1;

    return token;
}

void jt_tokenizer(JTTokenList *token_list, String input)
{
    int pointer = 0;
    JTToken *res;

    while (input.ptr[pointer] != NULL)
    {
        if (input.ptr[pointer] == ' ')
        {
            pointer++;
            continue;
        }

        if (__jt_is_separator(input.ptr[pointer]))
        {
            JTToken res = __jt_handle_separator(input.ptr[pointer]);
            jt_push(token_list, res);
        }
        else
        {
            JTToken res = __jt_handle_word(input, &pointer);
            jt_push(token_list, res);
        }

        pointer++;
    }
}

void jt_print_token_list(JTTokenList * token_list)
{
    for (int i = 0; i < token_list->length; i++)
    {
        if (token_list->ptr[i].type == JSON_TOKENIZER_TYPE_SEPARATOR)
            printf("%10s ","SEPARATOR");

        else if (token_list->ptr[i].type == JSON_TOKENIZER_TYPE_WORD)
            printf("%10s ","WORD");

        //printf("(%s) \n", token_list->ptr[i].data.ptr);
    }
}