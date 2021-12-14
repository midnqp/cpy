#include "cpy.h"
#include <float.h>




int list_index(List list, double item, int start, int end) {
	if (start < 0) start=0;
	if (end > list.len || end == -1) end = list_len(list);
	if (end != -1 && end < start) end=start;
	for (int i=start; i<end; i++) {
		if (list.value[i] == item)
			return i;
	}
	return -1;
}




double list_max(List list) {
	double a = list.value[0];
	for (int i = 1; i < list.len; i++) {
		if (list.value[i] > a) {
			a = list.value[i];
		}
	}
	return a;
}




double list_min(List list) {
	double a = list.value[0];
	for (int i = 1; i < list.len; i++) {
		if (list.value[i] < a) {
			a = list.value[i];
		}
	}
	return a;
}



List list_dup(List list) {
	List tmp;
	var(tmp, t_num_list, list.len);
	for (int i=0; i<list.len; i++) {
		tmp.value[i] = list.value[i];
	} 
	return tmp;
}




int list_len(List list) {
	int len = 0;
	for (int i=0; i < list.len; i++) {
		if (list.value[i] != DBL_MAX) len++;
	}
	return len;
}




int _list_sort(const void* a, const void* b) {
	if (*(double*)a > *(double*)b) return 1;
	else if (*(double*)a < *(double*)b) return -1;
	else return 0;  
}


List list_sort(List list) {
	List n = list_dup(list);
	qsort(n.value, n.len, sizeof(double), _list_sort);
	return n;
}




double list_sum(List list) {
	double sum = 0;
	for (int i = 0; i < list.len; i++) {
		double v = list.value[i];
		if (v != DBL_MAX) sum += v; 
	}
	return sum;
}




void list_push(List list, double item) {
	int len = list.len;
	for (int i=0; i < len; i++) {
		if (list.value[i] == DBL_MAX) {
			list.value[i] = item;
			break;
		}
	}
}




double list_get(List list, int index) {
	return list.value[index];
}





void list_set(List list, int index, double value) {
	list.value[index] = value;
}





bool list_includes(List list, double item) {
	for (int i=0; i<list.len; i++) {
		if (list.value[i] == item) return true;
	}
	return false;
}





void _list_fill_gap(List list) {
	int l = list.len;
	for (int i=0; i<l; i++) {
		if (list.value[i] == DBL_MAX && i < l-1) {
			list.value[i] = list.value[i+1];
			list.value[i+1] = DBL_MAX;
		}
	}
}





void list_remove(List list, int index) {
	list.value[index] = DBL_MAX;
	_list_fill_gap(list);
}
