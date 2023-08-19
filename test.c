#include "json.h"
#include "list.h"
#include "string.h"
#include <stdio.h>

void string_test();

int main(void)
{
  JObject *obj = j_new_object();
  JObject *koord = j_new_object();
  JObject *poof = j_new_object();

  j_add_int(poof, "xyz", 100);

  j_add_obj(obj, "koords", koord);
  j_add_double(koord, "lat", 60.128161);
  j_add_double(koord, "lon", 18.643501);

  j_add_obj(koord, "poof", poof);

  j_add_str(obj, "country", "SWE");
  j_add_int(obj, "inhabs", 10000000);

  printf("obj->str: %s\n", j_obj_to_str(obj));

  printf("xyz: %d", j_get_int(j_get_obj(j_get_obj(obj, "koords"), "poof"), "xyz"));
  return 0;
}