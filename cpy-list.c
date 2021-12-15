#include "cpy.h"


int list_len(List list) {
	int len = 0;
	for (int i=0; ;i++) {
		int t = list.type[i];
		if  (t != 0 && t != INT_MAX) len++;
	}
	return len;
}


// TODO Maybe you can store int, float, double. But do later.
void _list_push_num(List list, double item) {
	for (int i=0; ; i++) {
		if (list.type[i] == INT_MAX) {
			print("Index ", i, "of this list was empty. Filling it!");
			void* n = realloc(list.num, sizeof(list.num)+sizeof(item));
			if (n != NULL) list.num = n;
			else print("----Error realloc");
			list.num[i] = item;
			print("list.num[i] = ", list.num[i], " Type = ", typeOf(list.num[i]), Double_t);
		

			void* r = realloc(list.type, sizeof(list.type)+sizeof(int)*2);
			if (r!=NULL) list.type = r;
			else print("----Error realloc");
			list.type[i] = Double_t;
			list.type[i+1] = INT_MAX;
			print("list.type[0]: ", list.type[0], "  list.type[i+1]", list.type[i+1]);
			break;
		}                  
	}
}

void  _list_push_str(List list, char* item) {
	print("---- List push str: ", item, strlen(item));
	for (int i=0; ; i++) {
		if (list.type[i] == INT_MAX) {
			void* s = realloc(list.string[i], sizeof(list.string[i]) + strlen(item)+1);
			if (s != NULL) list.string[i] = s;
			else print("--String Error realloc");
			strcpy(list.string[i], item);
			print("==== After strcpy: ", list.string[i]);

			void* r = realloc(list.type, sizeof(list.type)+sizeof(int)*2);
			if (r!=NULL) list.type = r;
			else print("----Error realloc");
			list.type[i] = Str_t;
			list.type[i+1] = INT_MAX;
			break;
		}
	}
}


void _list_add(List list, int count, unsigned short argv[], ...) {
	va_list v;
	va_start(v, argv);
	for (int i=0; i < count; i++) {
		char t = argv[i] & 0x1F;
		print("-- list_add type: ", t);
		if (t == CharArray_t) {
			char* str = va_arg(v, char*);
			print("-- Here's the string: ", str);
			_list_push_str(list, str);
		}
		else if (t == Double_t) {
			double d = va_arg(v, double);
			_list_push_num(list, d);
		}
	}
}

/*void _list_add(List list, void* item, int t) {*/
	/*if (t == StrArray_t) {*/
		/*_list_push_str(list, (const char*)item);*/
	/*}*/
	/*else if (t == Double_t) {*/
		/*double* _itemP = (double*)item;*/
		/*double _item = *_itemP;*/
		/*_list_push_num(list, _item);*/
	/*}*/
	/*else print("idk");*/
/*}*/

/*int list_index(List list, double item, int start, int end) {*/
	/*if (start < 0) start=0;*/
	/*if (end > list.len || end == -1) end = list_len(list);*/
	/*if (end != -1 && end < start) end=start;*/
	/*for (int i=start; i<end; i++) {*/
		/*if (list.value[i] == item)*/
			/*return i;*/
	/*}*/
	/*return -1;*/
/*}*/




/*double list_max(List list) {*/
	/*double a = list.value[0];*/
	/*for (int i = 1; i < list.len; i++) {*/
		/*if (list.value[i] > a) {*/
			/*a = list.value[i];*/
		/*}*/
	/*}*/
	/*return a;*/
/*}*/




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
