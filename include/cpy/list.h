#ifndef CPY_LIST_H
#define CPY_LIST_H

void list_free(List* list); 
int list_len(List* list);

/**
 * Pass any number of strings,
 * and numbers as argument.
 */
void _list_add(List* list, int argc, unsigned short argv[], ...);
#define listAdd(list, a...) ({\
	int count = __print_count(a);\
	unsigned short stack[count], *_p = stack + count;\
	__print_types(a);\
	_list_add(list, count, _p, a);\
	\
})


/** 
 * Get index of an item in a list.
 *
 * @param {List} list
 * @param {Str_t | Num_t} item 
 * @param optional {int} start
 * @param optional {int} end
 *
 * @returns {int} Index of item.
 * Returns -1 if not found.
 */
int _list_index(int count, unsigned short argv[], ...);
#define list_index(list, a...) ({\
	va_argv(_list_index, a);\
})
/*
int _list_index_str(List list, const char* item, int start, int end);
int _list_index_num(List list, double item, int start, int end);
#define list_index(list, item, start, end) ({\
	int t = typeof(item);\
	int index=-1;\
	switch(t) {\
		case Str_t:\
			index = _list_index_str(list, item, start, end);\
			break;\
		case Double_t:\
			index = _list_index_num(list, item, start, end);\
			break;\
	}\
	index;\
})*/


/*double list_get(List list, int index);*/
/*void list_set(List list, int index, double item);*/
/*bool list_includes(List list, double item);*/
/*void list_push(List list, double item);*/
/*#define list_append(...) list_push(__VA_ARGS__)*/
/*void list_remove(List list, int index);*/
/*int list_len(List list);*/
/*int list_index(List list, double item, int start, int end);*/
/*double list_max(List list);*/
/*double list_min(List list);*/
/*double list_sum(List list);*/
/*List list_dup(List list);*/
/*List list_sort(List list);*/

#endif
