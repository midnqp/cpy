#include "include/cpy.h"

int main() {

	double numbers[] = {0, -1, 2.3, -4.5};
	print("array <number> ", numbers);

	List* listAny = new (List_t);
	listAdd(listAny, 1, -2, 3.4, "5", -6.7);
	print("array <any> ", listAny);

	char* str = malloc(sizeof(char*) * 64);
	strcpy(str, "this is a malloc'ed string");
	listAdd(listAny, str);

	char charLiteral[] = {'a', ' ', 'c', 'h', 'a', 'r', ' ', 'a', 'r', 'r', 'a', 'y', '\0'};
	listAdd(listAny, charLiteral);

	print("array <any> ", listAny);
	print("array length ", listLen(listAny));

	free(str);
	listFree(listAny);
}
