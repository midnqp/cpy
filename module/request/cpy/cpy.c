/************************************************
 * cpyb.h
 * Python builtins implemented in C
 * Source: github.com/midnqp/cpyb
 *
 * Copyright (C) 2021 Muhammad <midnqp@gmail.com>
 * Licensed under MIT License
 ************************************************/
#include "cpy.h"





char* file_read(const char* filename) {
	FILE* file = fopen(filename, "r");
	if (file != NULL) {
		fseek(file, 0, SEEK_END);
		long length = ftell(file);
		rewind(file);
		char* buffer = new(char*, length);
		strcpy(buffer, "");
		fseek(file, 0, SEEK_SET);
		if (buffer) fread(buffer, 1, length, file); 

		//fread doesn't terminate strings
		buffer[length] = '\0'; 
		fclose(file);

		return buffer;
	}
	else { 
		printf("file_read: Couldn't read file: %s\n", filename); 
		exit(1); 
	}
}




long file_size(const char* filename) {
	FILE* file = fopen(filename, "r");
	if (file) {
		fseek(file, 0, SEEK_END);
		long size = ftell(file);
		fclose(file);
		return size;
	}
	return -1;
}




void file_write(const char* filename, const char* buffer) {
	FILE* f = fopen(filename, "w");
	if (f == NULL) { printf("file_write: Couldn't open file: %s\n", filename); exit(1); }
	fprintf(f, "%s", buffer);
	fclose(f);
}




void file_append(const char* filename, const char* buffer) {
	FILE* f = fopen(filename, "a");
	if (f == NULL) { printf("file_append: Couldn't open file: %s\n", filename); exit(1); }
	fprintf(f, "%s", buffer);
	fclose(f);
}




int file_exists(const char* fn) {
	FILE* file = fopen(fn, "r");
	if (file) {
		fclose(file);
		return 1;
	}
	else {
		return 0;
	}
}




int file_remove(const char* fn) {
	return remove(fn);
}




int dir_exists(const char* dirName) {
	#ifdef _WIN32
	// dirName needs to absolute path?
	
	if (_access(dirName, 0) == 0) {
		struct stat status;
		stat(dirName, &status);

		return (status.st_mode & S_IFDIR) != 0;
	}
	return false;


	#else
	DIR* dir = opendir(dirName);
	if (dir) {
		closedir(dir);
		return 1;
	}
	else {
		closedir(dir);
		return 0;
	}
	#endif
}






char* input(const char* prompt) {
	char* tmp = new(char*, 10000); //10 KB
	strcpy(tmp, "");
	printf("%s", prompt); 
	fgets(tmp, 10000, stdin);
	
	size_t len = strlen(tmp);
	tmp = (char*)realloc(tmp, len);  
	tmp[len - 1] = '\0';  
	return tmp;
	// if allocation > input, realloc to save space
	// fgets adds a newline, while reading from stdin
}




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




#define COLOR(_COLOR, string, ...) ESC _COLOR string R0




/*
 * Generic Print
 * Copyright 2021 Exebook
 * Licensed under the MIT License
 */


int __print_enable_color = 1;

int __print_color_normal = -1; // -1 means default terminal foreground color
int __print_color_number = 4;
int __print_color_string = 1;
int __print_color_hex = 2;
int __print_color_float = 5;

void __print_color(FILE* fd, int a) {
	if (!__print_enable_color) return;
	if (a == -1) fprintf(fd, "\x1b(B\x1b[m");
	else fprintf(fd, "\x1b[38;5;%im", a);
}


void __print_setup_colors(int normal, int number, int string, int hex, int fractional) {
	__print_color_string = string;
	__print_color_number = number;
	__print_color_hex = hex;
	__print_color_normal = normal;
	__print_color_float = fractional;
}

void __print_func (FILE *fd, int count, unsigned short types[], ...) {
	va_list v;
	va_start(v, types);
	#ifdef __print_DEBUG
	fprintf(fd, "args[%i]: ", count);
	for (int i = 0; i < count; i++) {
		char type = types[i] & 0x1F;
		char size = types[i] >> 5;
		if (i > 0) fprintf(fd, " ");
		fprintf(fd, "%i[%i]", type, size);
	}
	fprintf(fd, "\n");
	#endif // __print_DEBUG

	for (int i = 0; i < count; i++) {
		if (i > 0) fprintf(fd, " ");
		char type = types[i] & 0x1F;
		char size = types[i] >> 5;
		if (type == 1) {
			__print_color(fd, __print_color_float);
			double d = va_arg(v, double);
			fprintf(fd, "%'G", d);
		}
		else if (type == 2) {
			__print_color(fd, __print_color_string);
			char c = va_arg(v, int);
			fprintf(fd, "'%c'", c); __print_color(fd, __print_color_number);
			fprintf(fd, "%i", (int)c);
		}
		else if (type == 3) {
			__print_color(fd, __print_color_number);
			char c = va_arg(v, int);
			fprintf(fd, "%i", (unsigned char)c);
			__print_color(fd, __print_color_normal);
			fprintf(fd, "<");
			__print_color(fd, __print_color_hex);
			fprintf(fd, "0x%X", (unsigned char)c);
			__print_color(fd, __print_color_normal);
			fprintf(fd, ">");
		}
		else if (type == 4) {
			__print_color(fd, __print_color_number);
			fprintf(fd, "%'i", va_arg(v, int));
		}
		else if (type == 5) {
			__print_color(fd, __print_color_number);
			fprintf(fd, "%'u", va_arg(v, int));
		}
		else if (type == 6) {
			__print_color(fd, __print_color_number);
			fprintf(fd, "%'li", va_arg(v, unsigned long));
		}
		else if (type == 7) {
			__print_color(fd, __print_color_number);
			fprintf(fd, "%'lu", va_arg(v, long));
		}
		else if (type == 8) {
			__print_color(fd, __print_color_string);
			fprintf(fd, "\"%s\"", va_arg(v, char*));
		}
		else if (type == 9) {
			__print_color(fd, __print_color_normal);
			fprintf(fd, "%s", va_arg(v, char*));
		}
		else if (type == 10) {
			__print_color(fd, __print_color_hex);
			fprintf(fd, "%p", va_arg(v, void*));
		}
		else if (type == 11) {
			__print_array(fd, double, "%.2lf", __print_color_number);
		}
		else if (type == 12) {
			__print_array(fd, unsigned int, "%u", __print_color_number);
		}
		else if (type == 13) {
			__print_array(fd, short, "%i", __print_color_number);
		}
		else if (type == 14) {
			__print_array(fd, unsigned short, "%i", __print_color_number);
		}
		else if (type == 15) {
			__print_array(fd, char*, "\"%s\"", __print_color_string);
		}
		else {
			fprintf(fd, "print: unsupported type (of size %i)\n", size); break;
		}
	}
	va_end(v);
	__print_color(fd, -1);
	fprintf(fd, "\n");
}

