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
    String sep = new_string();
    string_push_char(&sep, c);

    token.data = sep;
    token.type = JSON_TOKENIZER_TYPE_SEPARATOR;

    return token;
}

JTToken __jt_handle_word(String input, int pointer)
{
    int off = 0;
    JTToken token;
    String word = new_string();

    while (!__jt_is_separator(input.ptr[pointer + off]))
    {
        string_push_char(&word, input.ptr[pointer + off]);

        off++;
    }

    token.data = word;
    token.type = JSON_TOKENIZER_TYPE_WORD;

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
            JTToken res = __jt_handle_word(input, pointer);
            jt_push(token_list, res);

            pointer += res.data.length - 1;
        }

        pointer++;
    }
}

void jt_print_token_list(JTTokenList * token_list)
{
    for (int i = 0; i < token_list->length; i++)
    {
        if (token_list->ptr[i].type == JSON_TOKENIZER_TYPE_SEPARATOR)
            printf("%-10s: ","SEPARATOR");

        else if (token_list->ptr[i].type == JSON_TOKENIZER_TYPE_WORD)
            printf("%-10s: ","WORD");

        printf("(%s) \n", token_list->ptr[i].data.ptr);
    }
}