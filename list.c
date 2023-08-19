#include "malloc.h"
#include "stdio.h"

#include "list.h"
#include <stdlib.h>

LList *l_new_list() {
  LList *list = (LList *)malloc(sizeof(LList));
  list->first = NULL;
  list->size = 0;

  return list;
}

LNode *__new_node(void *value) {
  LNode *n = (LNode *)malloc(sizeof(LNode));
  n->value = malloc(sizeof(void*));
  n->value = value;
  n->next = NULL;
  return n;
}

int __append_to_empty(LNode *node, void *value) {
  if (node->next != NULL) {
    return __append_to_empty(node->next, value);
  } else {
    node->next = __new_node(value);
    return 0;
  }
  return -1;
}

int l_append(LList *list, void *value) {

  if (list->first == NULL) {
    list->size++;
    list->first = __new_node(value);
    return 0;
  }

  int ret = __append_to_empty(list->first, value);
  if (ret == 0) {
    list->size++;
    return ret;
  }

  return -1;
}

int __remove_at_index(LNode *node, int index, int counter, int list_size) {

  if (counter > index || node->next == NULL)
    return -1;

  if (counter != index - 1)
    return __remove_at_index(node->next, index, counter + 1, list_size);

  LNode *before = node;
  LNode *to_remove = node->next;

  if (index != list_size - 1) {
    LNode *after = to_remove->next;
    before->next = after;
  }

  free(to_remove);

  return 0;
}

int l_remove(LList *list, int index) {

  if (index == 0) {
    LNode *new_first = list->first->next;
    free(list->first);
    list->first = new_first;
    list->size--;
    return 0;
  }

  int ret = __remove_at_index(list->first, index, 0, list->size);
  if (ret == 0)
    list->size--;
  return ret;
}

void *l_get_index(LNode *node, int index, int counter) {

  if (counter == index)
    return node->value;

  if (node->next == NULL)
    return (void *)-1;

  return l_get_index(node->next, index, (counter + 1));
}

int l_get_int(LList *list, int index) {
  void *val = l_get_index(list->first, index, 0);
  return (int)(size_t)val;
}

char l_get_char(LList *list, int index) {
  void *val = l_get_index(list->first, index, 0);
  return (char)(size_t)val;
}

char *l_get_char_ptr(LList *list, int index) {
  void *val = l_get_index(list->first, index, 0);
  return (char *)(size_t)val;
}

