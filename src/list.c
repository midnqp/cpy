#include "../include/cpy.h"
#include <stdarg.h>

void listFree(List* list) {
  for (int i = 0; i < listLen(list); i++) {
    if (list->type[i] == Str_t) free(list->string[i]);
  }

  free(list->string);
  free(list->num);
  free(list->type);
}

int listLen(List* list) {
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
#define realloc_check(pointer, bytes)            \
  ({                                             \
    void* r = realloc(pointer, bytes);           \
    if (r == NULL) {                             \
      cpyErr("Couldn't realloc memory.", false); \
      return;                                    \
    }                                            \
    pointer = r;                                 \
  })

#define list_add_num(list, T)                           \
  ({                                                    \
    T d = va_arg(v, T);                                 \
    realloc_check(list->num, sizeof(double) * (i + 1)); \
    list->num[i] = (double)d;                           \
    realloc_check(list->type, sizeof(int) * (i + 1));   \
    list->type[i] = Double_t;                           \
    list->numc++;                                       \
  })

void list_add(int argc, unsigned short argv[], ...) {
  va_list v;
  va_start(v, argv);

  // Unpack.
  List* ls = va_arg(v, List*);

  for (int j = 0; j < argc; j++) {
    char type = va_type(argv[j]);
    int i = listLen(ls);
    if (type == CharArray_t) {
      const char* str = va_arg(v, char*);

      // Make space for new string.
      /*size_t sz = sizeof(char*) * (list->stringc + 1);*/
      ls->string = realloc(ls->string, sizeof(char*) * (i + 1));

      // Allocating for the string itself.
      ls->string[i] = malloc((strlen(str) + 1) * sizeof(char));
      strcpy(ls->string[i], str);

      // Storing index.
      realloc_check(ls->type, sizeof(int) * (i + 1));
      ls->type[i] = Str_t;

      ls->stringc++;
    } else if (type == Double_t)
      list_add_num(ls, double);
    else if (type == Int_t)
      list_add_num(ls, int);
  }
  va_end(v);
}

int list_index(int argc, unsigned short* argv, ...) {
  va_list v;
  va_start(v, argv);

  // Arg declare & init default.
  List* list;
  char item_t;
  const char* item_str;
  double item_num;
  int start = 0;
  int end = -1;

  // Unpack.
  list = va_arg(v, List*);

  item_t = va_type(argv[1]);
  if (item_t == Num_t)
    item_num = va_arg(v, double);
  else if (item_t == Str_t)
    item_str = va_arg(v, char*);

  if (argc >= 3) {
    start = va_arg(v, int);
    if (argc > 3) end = va_arg(v, int);
  }

  // Sanity.
  if (start < 0) start = 0;
  if (end > listLen(list) || end == -1) end = listLen(list);
  if (end != -1 && end < start) end = start;

  // Exec.
  switch (item_t) {
    case Num_t:
      for (int i = start; i < end; i++) {
        if (list->type[i] == Num_t && list->num[i] == item_num) return i;
      }
      break;
    case Str_t:
      for (int i = start; i < end; i++) {
        if (list->type[i] == Str_t && strEq(list->string[i], item_str))
          return i;
      }
      break;
    default:
      break;
  }
  return -1;
}

double listMax(List* ls) {
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

/*double list_min(List list) {*/
/*double a = list.value[0];*/
/*for (int i = 1; i < list.len; i++) {*/
/*if (list.value[i] < a) {*/
/*a = list.value[i];*/
/*}*/
/*}*/
/*return a;*/
/*}*/

/*List list_dup(List list) {*/
/*List tmp;*/
/*var(tmp, t_num_list, list.len);*/
/*for (int i=0; i<list.len; i++) {*/
/*tmp.value[i] = list.value[i];*/
/*} */
/*return tmp;*/
/*}*/

/*int _list_len(List list) {*/
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

/*List list_sort(List list) {*/
/*List n = list_dup(list);*/
/*qsort(n.value, n.len, sizeof(double), _list_sort);*/
/*return n;*/
/*}*/

/*double list_sum(List list) {*/
/*double sum = 0;*/
/*for (int i = 0; i < list.len; i++) {*/
/*double v = list.value[i];*/
/*if (v != DBL_MAX) sum += v; */
/*}*/
/*return sum;*/
/*}*/

/*double list_get(List list, int index) {*/
/*return list.value[index];*/
/*}*/

/*void list_set(List list, int index, double value) {*/
/*list.value[index] = value;*/
/*}*/

/*bool list_includes(List list, double item) {*/
/*for (int i=0; i<list.len; i++) {*/
/*if (list.value[i] == item) return true;*/
/*}*/
/*return false;*/
/*}*/

/*void _list_fill_gap(List list) {*/
/*int l = list.len;*/
/*for (int i=0; i<l; i++) {*/
/*if (list.value[i] == DBL_MAX && i < l-1) {*/
/*list.value[i] = list.value[i+1];*/
/*list.value[i+1] = DBL_MAX;*/
/*}*/
/*}*/
/*}*/

/*void list_remove(List list, int index) {*/
/*list.value[index] = DBL_MAX;*/
/*_list_fill_gap(list);*/
/*}*/
