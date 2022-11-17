#include <assert.h>
#include "./include/cpy.h"

cpy_list* example_list_any();
void string();
void numbers();
void print_any();

static char chars[] = {'c', 'h', '\0'};

int main()
{
  print(1, "hello", -212, chars);
  cpy_list* l = example_list_any();
  list_free(l);
  return 0;
}

cpy_list *example_list_any()
{
  cpy_list *l = cpy_new(list_t);
  list_add(l, 0, -0.03, "7");
  list_add(l, "any string");
  list_add(l, chars);

  assert(list_len(l) == 5);
  assert(list_index(l, -0.03) == 1);
  assert(list_index(l, "ch") == 4);
  assert(cpy_type(l) == cpy_list_t);

  // list_free(l);
  return l;
}
