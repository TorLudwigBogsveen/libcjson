/**
 * @file
 */
#ifndef LIST_H
#define LIST_H

typedef struct LNode {
  void *value;
  struct LNode *next;
} LNode;

typedef struct LList {
  LNode *first;
  int size;
} LList;

/**
 *  allocates space for a new list and returns a pointer to the memory location
 */
LList *l_new_list();

/**
 * appends a value to the end of the list
 */
int l_append(LList *list, void *value);

/**
 * removes the value at a specific index.
 */
int l_remove(LList *list, int index);

/**
 * get the value at a specific index and returns it as a int
 */
int l_get_int(LList *list, int index);

/**
 * get the value at a specific index and returns it as a char
 */
char l_get_char(LList *list, int index);

/**
 * get the value at a specific index and returns it as a char ptr
 */
char *l_get_char_ptr(LList *list, int index);

void *l_get_index(LNode *node, int index, int counter);

#endif