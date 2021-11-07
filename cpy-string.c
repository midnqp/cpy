#include <cpy.h>
char* __str_add_va__(const char* strings, ...) {
	va_list allstrings;
	va_start(allstrings, strings);

	char* parent = (char*)malloc(9000);
	strcpy(parent, "");
	char* _tmp = (char*)malloc(5000);
	strcpy(_tmp, "");
	strcpy(_tmp, strings);
	strcat(parent, _tmp);
	free(_tmp);

	char* tmp = va_arg(allstrings, char*);

	while (tmp != NULL) {
		strcat(parent, tmp);
		tmp = va_arg(allstrings, char*);
	}
	va_end(allstrings);
	return parent;
}




int str_eq(const char* a, const char* b) {
	if (strcmp(a, b) == 0) return 1;
	else return 0;
}




char* str_put(char* variable, char* value) {
	free(variable);
	return value;
}




void strPut(char* variable, char* value) {
	if (type(value) == t_str) {
		printf("We've got a string.\n");
	}
	else {printf("No idea what that was.\n");}
	strcpy(variable, value);
	free(value);
}




char* str_reverse(const char* string) {
	int len = strlen(string);
	char* tmp = new(char*, len);
	strcpy(tmp, "");
	for (int i = len; i >= 0; i--) {
		strncat(tmp, &string[i], 1);
	}
	return tmp;
}




// Checks if substr is in string.
// Returns up to what is matched.
char* str_substr(const char* string, const char* substr) {
	char* matched = (char*)malloc(strlen(substr));
	strcpy(matched, "");
	size_t i = 0;    // counter for substr
	size_t j = 0;    // counter for string

	for (j = 0; j < strlen(string); j++) {
		if (substr[i] == string[j]) {
			strncat(matched, &substr[i], 1);    
			//substr[i] matched!
			i++;
		}
		if (str_eq(matched, substr)) break;
	}
	return matched;
}




int str_index(const char* str, const char* substr, int start, int end) {
	int size = strlen(str) + 1;
	char* string = new(char*, size);   // temporary
	strcpy(string, str + start);  //makes perfect sense

	char* p = strstr(string, substr);
	if (!p) {
		free(string);
		return -1; 
		//substr doesn't exist in str
	}

	int loc = (p - string) + start;
	free(string);
	
	if (loc < end) return loc;
	else return -1;
}





int str_count(const char* string, const char* substr, int start, int end) {
	int count = 0;
	int i = str_index(string, substr, start, end);
	while (i != -1) {
		count++;
		i = str_index(string, substr, i + 1, end);
	}
	return count;
}


int str_isalpha(const char* string) {
	int result = 1; //true
	for (size_t i = 0; i < strlen(string); i++) {
		char* tmpSlice = str_slice(string, i, 1, i + 1);
		char ch = tmpSlice[0];
		free(tmpSlice);
		if (!isalpha(ch)) { result = 0; break; }  //false
	}
	return result;
}


char* str_replace(const char* main, const char* repl, const char* with, int start, int end) {
	int len_main = strlen(main);
	int occ = str_count(main, repl, start, end);   // occurences

	size_t size = (len_main - occ * strlen(repl)) + occ * strlen(with);
	char* Result = new(char*, size);
	strcpy(Result, "");

	int whereRepl = str_index(main, repl, start, end);

	int i = start;

	while (main[i] != '\0') {
		if (i >= whereRepl && whereRepl != -1) {
			for (size_t j = 0; j < strlen(with); j++)
				strncat(Result, &with[j], 1);

			whereRepl = str_index(main, repl, i + strlen(repl), end);
			i = i + strlen(repl);  //else block: main[i]
		}
		else {
			strncat(Result, &main[i], 1);
			i++;
		}
	}
	return Result;
}




char* str_slice(const char* string, int start, int step, int end) {
	char* tmp = new(char*, strlen(string));
	strcpy(tmp, "");
	for (int i = start; i < end; i += step) {
		strncat(tmp, &string[i], 1);
	}
	return tmp;
}




char** str_split(const char* a_str, const char* a_delim) {
	char** result;
	size_t count = 0;
	
	char* string = new(char*, strlen(a_str));
	strcpy(string, a_str);


	char* tmp = new(char*, strlen(a_str)); 
	strcpy(tmp, a_str);
	count = str_count(a_str, a_delim, 0, str_len(a_str));

	// Add space for trailing token
	count++;
	// Add space for NULL termination
	count++;

	result = (char**)malloc(sizeof(char*) * count); 

	size_t idx = 0;
	char* token = strtok(string, a_delim);

	while (token) {
		#ifdef _WIN32
		*(result + idx++) = token;
		#else
		result[idx++] = token;
		#endif
		
		token = strtok(0, a_delim);
	}
	*(result + idx) = 0;
	free(tmp);
	//free(string);
	return result;
}
