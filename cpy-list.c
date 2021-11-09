#include <cpy.h>
double list_max(double numbers[], int arrlen) {
	double maxitem = numbers[0];
	for (int i = 1; i < arrlen; i++) {
		if (numbers[i] > maxitem) {
			maxitem = numbers[i];
		}
	}
	return maxitem;
}




double list_min(double numbers[], int arrlen) {
	double minitem = numbers[0];
	for (int i = 1; i < arrlen; i++) {
		if (numbers[i] < minitem) {
			minitem = numbers[i];
		}
	}
	return minitem;
}




int _list_sort_func(const void* a, const void* b) {
	if (*(double*)a > *(double*)b) return 1;
	else if (*(double*)a < *(double*)b) return -1;
	else return 0;  
}


double* list_sort(double* list, size_t len) {
	qsort(list, len, sizeof(double), _list_sort_func);
	return list;
}




double list_sum(double numbers[], int arrlen) {
	double sum = 0;
	for (int i = 0; i < arrlen; i++) { sum += numbers[i]; }
	return sum;
}




void listAdd(double* list, double item) {
	
}
