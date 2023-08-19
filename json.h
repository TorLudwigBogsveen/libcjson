/**
 * @file
 */
#ifndef JSON_H
#define JSON_H

#include "list.h"

#define JSON_L_CB '{'
#define JSON_R_CB '}'
#define JSON_COMMA ','
#define JSON_L_SB '['
#define JSON_R_SB ']'
#define JSON_DQ '"'

#define JSON_TYPE_BOOL 0
#define JSON_TYPE_STR 1
#define JSON_TYPE_NUM 3
#define JSON_TYPE_OBJECT 4
#define JSON_TYPE_DOUBLE 5

#define TRUE !0
#define FALSE 0

typedef char *JStr;
typedef enum JBool { T = !0, F = 0 } JBool;

typedef enum {
  BOOL = JSON_TYPE_BOOL,
  STR = JSON_TYPE_STR,
  NUM = JSON_TYPE_NUM,
  OBJECT = JSON_TYPE_OBJECT,
  DOUBLE = JSON_TYPE_DOUBLE
} JType;

struct JKVPair;
struct JObject;

typedef struct JKVPair {
  JType type;
  JStr key;
  void *value;
} JKVPair;

typedef struct JObject {
  int children;
  LList *data;
} JObject;


JObject *j_new_object();

int j_add_bool(JObject *object, JStr key, JBool value);
int j_add_int(JObject *object, JStr key, int value);
int j_add_str(JObject *object, JStr key, JStr value);
int j_add_obj(JObject *object, JStr key, JObject *value);
int j_add_double(JObject *object, JStr key, double value);


JBool *j_get_bool(JObject *object, JStr key);
int j_get_int(JObject *object, JStr key);
JStr j_get_str(JObject *object, JStr key);
JObject *j_get_obj(JObject *object, JStr key);
double j_get_double(JObject *object, JStr key);

JStr j_obj_to_str(JObject *obj);
JStr __obj_to_str(JObject *obj);

JObject *j_str_to_obj(const JStr json_str);

#endif