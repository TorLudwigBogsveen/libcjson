#include "assert.h"
#include "json.h"
#include "json_lexer.h"
#include "list.h"
#include "string.h"
#include "vector.h"
#include "dynamic_string.h"
#include <stdio.h>

#define TEST_OUTPUT_1                                                          \
  "{\"koords\": {\"lat\": 60.128161,\"lon\": 18.643501,\"poof\": {\"xyz\": "   \
  "100}},\"country\": \"SWE\",\"inhabs\": 10000000}"

#define TEST_INPUT_1                                                           \
  "{\"koords\": {\"lat\": 60.128161,\"lon\": 18.643501,\"poof\": {\"xyz\": "   \
  "100}},\"country\": \"SWE\",\"inhabs\": 10000000"

JObject *obj;
JObject *koord;
JObject *poof;

void init() {
  obj = j_new_object();
  koord = j_new_object();
  poof = j_new_object();

  j_add_int(poof, "xyz", 100);

  j_add_obj(obj, "koords", koord);
  j_add_double(koord, "lat", 60.128161);
  j_add_double(koord, "lon", 18.643501);

  j_add_obj(koord, "poof", poof);

  j_add_str(obj, "country", "SWE");
  j_add_int(obj, "inhabs", 10000000);
}

void type_missmatch_test() {
  // test the type missmatch
  printf("This should print a \"Type missmatch!\" error to the terminal!\n");
  assert((int)(size_t)j_get_obj(obj, "inhabs") == -1);
}

void nested_get_test() {
  // check nested gets
  assert(j_get_int(j_get_obj(j_get_obj(obj, "koords"), "poof"), "xyz") == 100);
}

void obj_to_str_test() {
  // test obj to str
  assert(strcmp(j_obj_to_str(obj), TEST_OUTPUT_1) == 0);
}

void test_iccorect_formated_json() {
  int ret = (int)(size_t)j_str_to_obj(TEST_INPUT_1);
  assert(ret == -1);
}

void test_tokenizer() {
  JLTokenStream stream = jl_new_token_stream();
  printf("poof1!");
  jl_tokenize(&stream, "{\"x\":10, \"y\":20}");
  printf("poof2!");
  jl_print_token_stream(stream);
}

void test_string() {
  String a = new_string();
  for (int i = 0; i < 8; i++) {
    string_printf(&a, "%d ", i * 2);
  }
  printf("\n%s\n", a.ptr);
}

CREATE_VECTOR_TYPE(intVec, vecint, int)

void test_vector() {
  intVec a = vecint_new();
  vecint_push(&a, 640);
  assert(a.ptr[0] == 640);
}

int main(void) {
  init();

  type_missmatch_test();
  nested_get_test();
  obj_to_str_test();
  test_iccorect_formated_json();
  test_tokenizer();
  test_vector();
  test_string();
  return 0;
}