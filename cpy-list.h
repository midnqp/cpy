#ifndef CPY_LIST_H
#define CPY_LIST_H

#define list_free(list) \
	free(list.value);\
	free(list.types);


#define _list_push(list, item, T)                \
	int len = list.alloc;                        \
	for (int i=0; i < list.alloc/8; i++) {       \
		if (list.types[i] == INT_MAX) {          \
			((T*)list.value)[i] = item;          \
			list.types[i] = typeOf(item);        \
			break;                               \
		}                                        \
	}                                            


#define list_add(list, item)                     \
	_list_push(list, item, type(item))

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
