#include "json.h"
#include "dynamic_string.h"
#include "malloc.h"
#include "stdio.h"
#include "string.h"

DEFINE_VECTOR_TYPE(JObject, j, JKVPair)

JObject *j_new_object()
{
  JObject *obj = (JObject *)malloc(sizeof(JObject));
  *obj = j_new();
  return obj;
}

void __add(JObject *object, JStr key, JValue value, JType type)
{
  JKVPair kvp;
  kvp.type = type;
  kvp.key = key;
  kvp.value = value;
  j_push(object, kvp);
}

JValue __get(JObject *object, JStr key, JType type, JBool *has_error)
{
  for (int i = 0; i < object->length; i++)
  {
    JKVPair *kvp = &object->ptr[i];
    if (strcmp(kvp->key, key) == 0)
    {
      // type checking, returns UNDEFINED if the types don't match.
      if (kvp->type == type)
      {
        return kvp->value;
      }
      else
      {
        *has_error = T;
        JValue error;
        error.error = J_TYPE_MISMATCH;
        return error;
      }
    }
  }

  *has_error = T;

  JValue error;
  error.error = J_UNDEFINED;
  return error;
}

// Section for all "add" functions

void j_add_int(JObject *object, JStr key, int value)
{
  JValue j_value;
  j_value.integer = value;
  __add(object, key, j_value, JSON_TYPE_NUM);
}

void j_add_str(JObject *object, JStr key, JStr value)
{
  JValue j_value;
  j_value.string = value;
  __add(object, key, j_value, JSON_TYPE_STR);
}

void j_add_obj(JObject *object, JStr key, JObject *value)
{
  JValue j_value;
  j_value.object = value;
  __add(object, key, j_value, JSON_TYPE_OBJECT);
}

void j_add_bool(JObject *object, JStr key, JBool value)
{
  JValue j_value;
  j_value.boolean = value;
  __add(object, key, j_value, JSON_TYPE_BOOL);
};

void j_add_double(JObject *object, JStr key, double value)
{
  JValue j_value;
  j_value.decimal = value;
  __add(object, key, j_value, JSON_TYPE_DOUBLE);
};

// Section for all "Get" functions

JBool j_get_bool(JObject *object, JStr key)
{
  JBool has_error = F;
  JValue ret = __get(object, key, JSON_TYPE_BOOL, &has_error);
  if (!has_error)
    return ret.boolean;
  printf("Type missmatch!\n");
  return F;
}

int j_get_int(JObject *object, JStr key)
{
  JBool has_error = F;
  JValue ret = __get(object, key, JSON_TYPE_NUM, &has_error);
  if (!has_error)
    return ret.integer;
  printf("Type missmatch!\n");
  return 0;
}

JStr j_get_str(JObject *object, JStr key)
{
  JBool has_error = F;
  JValue ret = __get(object, key, JSON_TYPE_STR, &has_error);
  if (!has_error)
    return ret.string;
  printf("Type missmatch!\n");
  return "";
}

JObject *j_get_obj(JObject *object, JStr key)
{
  JBool has_error = F;
  JValue ret = __get(object, key, JSON_TYPE_OBJECT, &has_error);
  if (!has_error)
    return ret.object;
  printf("Type missmatch!\n");
  return NULL;
}

double j_get_double(JObject *object, JStr key)
{
  JBool has_error = F;
  JValue ret = __get(object, key, JSON_TYPE_DOUBLE, &has_error);
  if (!has_error)
    return ret.decimal;
  printf("Type missmatch!\n");
  return 0.0;
}

// stringify section

JStr __kvp_to_str(JKVPair *kvp)
{
  String str = new_string();
  switch (kvp->type)
  {
  case STR:
    string_printf(&str, "\"%s\": \"%s\"", kvp->key, kvp->value.string);
    break;
  case NUM:
    string_printf(&str, "\"%s\": %d", kvp->key, kvp->value.integer);
    break;
  case BOOL:
    string_printf(&str, "\"%s\": %s", kvp->key,
                  (kvp->value.boolean == TRUE ? "true" : "false"));
    break;
  case OBJECT:
    string_printf(&str, "\"%s\": %s", kvp->key, __obj_to_str(kvp->value.object));
    break;

  case DOUBLE:
    string_printf(&str, "\"%s\": %lf", kvp->key, kvp->value.decimal);
    break;
  }

  return str.ptr;
}

JStr __obj_to_str(JObject *obj)
{
  String str = new_string();
  string_push_char(&str, '{');

  for (int i = 0; i < obj->length; i++)
  {
    JStr kvp_string = __kvp_to_str(&obj->ptr[i]);
    string_append(&str, kvp_string);

    if (i != obj->length - 1)
      string_push_char(&str, ',');

    free(kvp_string);
  }

  string_push_char(&str, '}');

  return str.ptr;
}

JStr j_obj_to_str(JObject *obj) { return __obj_to_str(obj); }

// String to json

int __validate_brackets(const JStr json_str)
{

  int l_cb_count = 0;
  int r_cb_count = 0;

  int l_sb_count = 0;
  int r_sb_count = 0;

  size_t i = 0;

  for (size_t i = 0; i < strlen(json_str); i++)
  {
    switch (json_str[i])
    {
    case JSON_L_CB:
      l_cb_count++;
      break;
    case JSON_R_CB:
      r_cb_count++;
      break;
    case JSON_L_SB:
      l_sb_count++;
      break;
    case JSON_R_SB:
      r_sb_count++;
      break;
    }
  }

  return ((l_cb_count == r_cb_count) && (l_sb_count == r_sb_count) ? 0 : -1);
}

JObject *j_str_to_obj(const JStr json_str)
{
  JObject *obj = j_new_object();

  // early return if there is an odd number of brackets
  if (__validate_brackets(json_str) != 0)
    return (JObject *)-1;

  return obj;
}
