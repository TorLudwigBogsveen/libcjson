#include "json.h"
#include "dynamic_string.h"
#include "list.h"
#include "malloc.h"
#include "stdio.h"
#include "string.h"
#include <stdlib.h>

JObject *j_new_object() {
  JObject *obj = (JObject *)malloc(sizeof(JObject));
  obj->children = 0;
  obj->data = l_new_list();
  return obj;
}

int __add(JObject *object, JStr key, void *value, JType type) {
  JKVPair *kvp = (JKVPair *)malloc(sizeof(JKVPair));
  kvp->type = type;
  kvp->key = key;
  kvp->value = value;
  int ret = l_append(object->data, (void *)kvp);

  if (ret == 0)
    object->children += 1;

  return ret;
}

void *__get(JObject *object, JStr key, JType type) {
  int counter = 0;
  LNode *current = object->data->first;
  while (counter < object->children) {
    JKVPair *kvp = current->value;
    if (strcmp(kvp->key, key) == 0)

      // type checking, returns -1 if the types don't match.
      return kvp->type == type ? kvp->value : (void *)-1;
    current = current->next;
    counter++;
  }
  return (void *)-1;
}

int j_add_int(JObject *object, JStr key, int value) {
  return __add(object, key, (void *)(size_t)value, JSON_TYPE_NUM);
}

int j_add_str(JObject *object, JStr key, JStr value) {
  return __add(object, key, (void *)(size_t)value, JSON_TYPE_STR);
}

int j_add_obj(JObject *object, JStr key, JObject *value) {
  return __add(object, key, (void *)(size_t)value, JSON_TYPE_OBJECT);
}

int j_add_bool(JObject *object, JStr key, JBool value) {
  return __add(object, key, (void *)(size_t)value, JSON_TYPE_BOOL);
};

int j_add_double(JObject *object, JStr key, double value) {
  double *n = malloc(sizeof(double));
  *n = value;
  return __add(object, key, (void *)n, JSON_TYPE_DOUBLE);
};

JBool *j_get_bool(JObject *object, JStr key) {
  void *ret = __get(object, key, JSON_TYPE_BOOL);
  if ((int)(size_t)ret != -1)
    return (JBool *)ret;
  printf("Type missmatch!");
  return (JBool *)ret;
}

int j_get_int(JObject *object, JStr key) {
  void *ret = __get(object, key, JSON_TYPE_NUM);
  if ((int)(size_t)ret != -1)
    return (int)(size_t)ret;
  printf("Type missmatch!");
  return (int)(size_t)ret;
}

JStr j_get_str(JObject *object, JStr key) {
  void *ret = __get(object, key, JSON_TYPE_STR);
  if ((int)(size_t)ret != -1)
    return (JStr)ret;
  printf("Type missmatch!");
  return (JStr)ret;
}

JObject *j_get_obj(JObject *object, JStr key) {
  void *ret = __get(object, key, JSON_TYPE_OBJECT);
  if ((int)(size_t)ret != -1)
    return (JObject *)ret;
  printf("Type missmatch!");
  return (JObject *)ret;
}

double j_get_double(JObject *object, JStr key) {
  void *ret = __get(object, key, JSON_TYPE_DOUBLE);
  if ((int)(size_t)ret != -1)
    return *(double *)ret;
  printf("Type missmatch!");
  return *(double *)ret;
}

JStr __kvp_to_str(JKVPair *kvp) {
  String str = new_string();
  switch (kvp->type) {
  case STR:
    string_printf(&str, "\"%s\": \"%s\"", kvp->key, (char *)(size_t)kvp->value);
    break;
  case NUM:
    string_printf(&str, "\"%s\": %d", kvp->key, (int)(size_t)kvp->value);
    break;
  case BOOL:
    string_printf(&str, "\"%s\": %s", kvp->key,
                  ((JBool)(size_t)kvp->value == TRUE ? "true" : "false"));
    break;
  case OBJECT:
    string_printf(&str, "\"%s\": %s", kvp->key, __obj_to_str(kvp->value));
    break;

  case DOUBLE:
    string_printf(&str, "\"%s\": %lf", kvp->key, *(double *)kvp->value);
    break;
  }

  return str.ptr;
}

JStr __obj_to_str(JObject *obj) {
  String str = new_string();
  string_push_char(&str, '{');

  for (int i = 0; i < obj->children; i++) {
    JStr kvp_string = __kvp_to_str(l_get_index(obj->data->first, i, 0));
    string_push_string(&str, kvp_string);

    if (i != obj->children - 1)
      string_push_char(&str, ',');

    free(kvp_string);
  }

  string_push_char(&str, '}');

  return str.ptr;
}

JStr j_obj_to_str(JObject *obj) { return __obj_to_str(obj); }
