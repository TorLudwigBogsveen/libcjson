#include "json_parser.h"
#include "json_tokenizer.h"

JObject *jp_parse_string(String json) {
    JTTokenList token_list = jt_new_token_list();
    jt_tokenizer(&token_list, json);
}