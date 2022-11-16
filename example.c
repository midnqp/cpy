#include "include/cpy.h"

int main() {

	double numbers[] = {1, -2, 3.4, -5.6};
	print("Array<Number> ", numbers);

	List* listAny = new (List_t);
	listAdd(listAny, 1, -2, 3.4, "5", -6.7);
	print("Array<any> ", listAny);

	char* str = malloc(sizeof(char*) * 100);
	strcpy(str, "Malloc-ed string");
	listAdd(listAny, str);

	char charLiteral[] = {'c', 'h', 'a', 'r', 'A', 'r', 'r', '\0'};
	listAdd(listAny, charLiteral, "String literal (considered char array literal)");

	print("Array<any> ", listAny);
	print("Length ", listLen(listAny));
	free(str);
	listFree(listAny);
}
