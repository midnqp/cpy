#include <stdarg.h>

#include "../include/cpy.h"

void list_free(cpy_list* list) {
  for (int i = 0; i < list_len(list); i++) {
    if (list->type[i] == cpy_str_t) free(list->string[i]);
  }

  free(list->string);
  free(list->num);
  free(list->type);
}

int list_len(cpy_list* list) {
  int len = list->stringc + list->numc;
  return len;
}

/**
 * Reallocates and then checks for error.
 * If realloc failed, exit().
 * Otherwise, assign to itself.
 *
 * @param {void*} Pointer
 * @param {size_t} Bytes to allocate
 */
#define realloc_check(pointer, bytes)               \
  ({                                                \
    void* r = realloc(pointer, bytes);              \
    if (r == NULL) {                                \
      fprintf(stderr, "[libcpy] realloc failed\n"); \
      return;                                       \
    }                                               \
    pointer = r;                                    \
  })

#define list_add_num(list, T)                           \
  ({                                                    \
    T d = va_arg(v, T);                                 \
    realloc_check(list->num, sizeof(double) * (i + 1)); \
    list->num[i] = (double)d;                           \
    realloc_check(list->type, sizeof(int) * (i + 1));   \
    list->type[i] = cpy_double_t;                       \
    list->numc++;                                       \
  })

void __list_add(int argc, unsigned short argv[], ...) {
  va_list v;
  va_start(v, argv);

  // Unpack.
  cpy_list* ls = va_arg(v, cpy_list*);

  for (int j = 0; j < argc; j++) {
    char type = va_type(argv[j]);
    int i = list_len(ls);
    if (type == cpy_arrc_t || type == cpy_str_t || type == cpy_char_t) {
      const char* str = va_arg(v, char*);

      // Make space for new string.
      /*size_t sz = sizeof(char*) * (list->stringc + 1);*/
      ls->string = realloc(ls->string, sizeof(char*) * (i + 1));

      // Allocating for the string itself.
      ls->string[i] = malloc((strlen(str) + 1) * sizeof(char));
      strcpy(ls->string[i], str);

      // Storing index.
      realloc_check(ls->type, sizeof(int) * (i + 1));
      ls->type[i] = cpy_str_t;

      ls->stringc++;
    }
    /*else if (type == cpy_char_t) {}*/
    else if (type == cpy_double_t) {
      list_add_num(ls, double);
    } else if (type == cpy_int_t) {
      list_add_num(ls, int);
    }
  }
  va_end(v);
}

int __list_index(int argc, unsigned short* argv, ...) {
  va_list v;
  va_start(v, argv);

  // Arg declare & init default.
  cpy_list* list;
  char item_t;
  const char* item_str;
  char item_arrc[1024];
  double item_num;

  // Unpack.
  list = va_arg(v, cpy_list*);

  item_t = va_type(argv[1]);
  if (item_t == cpy_num_t)
    item_num = va_arg(v, double);
  else if (item_t == cpy_str_t)
    item_str = va_arg(v, char*);
  else if (item_t == cpy_arrc_t) {
    item_str = va_arg(v, char*);
  } else {
    print("[libcpy] unexpected datatype in", __FUNCTION__);
    return -1;
  }

  int start = 0;
  int len = list_len(list);
  int end = len;
  if (argc >= 3) {
    start = va_arg(v, int);
    if (argc > 3) end = va_arg(v, int);
  }

  // Sanity.
  // TODO support reverse index!
  if (start < 0 || start > len) start = 0;
  if (end < 0 || end > len) end = len;

  // Exec.
  print("[libcpy] item_str", item_str);
  switch (item_t) {
    case cpy_num_t:
      for (int i = start; i < end; i++) {
        bool foundtype = list->type[i] == cpy_num_t;
        bool equalval = false;
        if (foundtype) equalval = list->num[i] == item_num;
        if (equalval) return i;
      }
      break;

    case cpy_str_t:
    case cpy_arrc_t:
      for (int i = start; i < end; i++) {
        bool foundtype =
            list->type[i] == cpy_arrc_t || list->type[i] == cpy_str_t;
        bool equalval = false;
        if (foundtype) equalval = strEq(list->string[i], item_str);
        if (equalval) return i;
      }
      break;
  }
  return -1;
}

double listMax(cpy_list* ls) {
  print(ls);
  return 0;
  /*double a = list.;*/
  /*for (int i = 0; i < listLen(list); i++) {*/
  /*if (list-> > a) {*/
  /*a = list.value[i];*/
  /*}*/
  /*}*/
  /*return a;*/
}

/*double list_min(list list) {*/
/*double a = list.value[0];*/
/*for (int i = 1; i < list.len; i++) {*/
/*if (list.value[i] < a) {*/
/*a = list.value[i];*/
/*}*/
/*}*/
/*return a;*/
/*}*/

/*cpy_list list_dup(cpy_list list) {*/
/*cpy_list tmp;*/
/*var(tmp, t_num_list, list.len);*/
/*for (int i=0; i<list.len; i++) {*/
/*tmp.value[i] = list.value[i];*/
/*} */
/*return tmp;*/
/*}*/

/*int _list_len(cpy_list list) {*/
/*int len = 0;*/
/*for (int i=0; i < list.len; i++) {*/
/*if (list.value[i] != DBL_MAX) len++;*/
/*}*/
/*return len;*/
/*}*/

/*int _list_sort(const void* a, const void* b) {*/
/*if (*(double*)a > *(double*)b) return 1;*/
/*else if (*(double*)a < *(double*)b) return -1;*/
/*else return 0;  */
/*}*/

/*cpy_list list_sort(cpy_list list) {*/
/*cpy_list n = list_dup(list);*/
/*qsort(n.value, n.len, sizeof(double), _list_sort);*/
/*return n;*/
/*}*/

/*double list_sum(cpy_list list) {*/
/*double sum = 0;*/
/*for (int i = 0; i < list.len; i++) {*/
/*double v = list.value[i];*/
/*if (v != DBL_MAX) sum += v; */
/*}*/
/*return sum;*/
/*}*/

/*double list_get(cpy_list list, int index) {*/
/*return list.value[index];*/
/*}*/

/*void list_set(cpy_list list, int index, double value) {*/
/*list.value[index] = value;*/
/*}*/

/*bool list_includes(cpy_list list, double item) {*/
/*for (int i=0; i<list.len; i++) {*/
/*if (list.value[i] == item) return true;*/
/*}*/
/*return false;*/
/*}*/

/*void _list_fill_gap(cpy_list list) {*/
/*int l = list.len;*/
/*for (int i=0; i<l; i++) {*/
/*if (list.value[i] == DBL_MAX && i < l-1) {*/
/*list.value[i] = list.value[i+1];*/
/*list.value[i+1] = DBL_MAX;*/
/*}*/
/*}*/
/*}*/

/*void list_remove(cpy_list list, int index) {*/
/*list.value[index] = DBL_MAX;*/
/*_list_fill_gap(list);*/
/*}*/
