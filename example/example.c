#define _CRT_SECURE_NO_WARNINGS
#include <assert.h>

#include "../include/cpy.h"

cpy_list* example_list_any();
void string();
void numbers();
void print_any();

static char chars[] = {'c', 'h', '\0'};

int main() {
  _CrtSetDbgFlag(CPY_CRTDBG_MEMCHECK);

  char* string = malloc(10);
  strcpy(string, "hello");
  free(string);
  return 0;
}

cpy_list* example_list_any() {
  printf("hello\n");
  cpy_list* l = cpy_new(cpy_list_t);
  // list_add(l, 0, -0.03, "7");
  // list_add(l, "any string");
  // list_add(l, chars);

  // assert(list_len(l) == 5);
  // assert(list_index(l, -0.03) == 1);
  // assert(list_index(l, "ch") == 4);
  // assert(cpy_type(l) == cpy_list_t);

  return l;
}
