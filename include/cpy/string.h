#ifndef CPY_STRING_H
#define CPY_STRING_H


char* __str_add_va__(const char* strings, ...);
#define str_add(...) __str_add_va__(__VA_ARGS__, NULL)
#define str_len(pointer) strlen(pointer)
int str_count(const char* string, const char* substr, int start, int end);
int str_eq(const char* a, const char* b);
int str_index(const char* str, const char* substr, int start, int end);
int str_isalpha(const char* string);
char* str_put(char* variable, char* value);
void strPut(char* variable, char* value); 
#define strAdd(variable, ...) {\
	char* __strAddInternal = str_add(variable, __VA_ARGS__);\
	strPut(variable, __strAddInternal);\
}
char* str_replace(const char* main, const char* repl, const char* with, int start, int end);
char* str_reverse(const char* string);
char* str_slice(const char* string, int start, int step, int end);
char** str_split(const char* a_str, const char* a_delim);
char* str_substr(const char* string, const char* substr);

#endif
