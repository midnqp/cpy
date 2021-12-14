#include <cpy.h>
/**
 * Generic Print
 * Copyright 2021 Exebook
 * Licensed under the MIT License
 */

int __print_enable_color = 1;

int __print_color_normal = -1; // -1 means default terminal foreground color
int __print_color_number = 4;
int __print_color_string = 3;
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
		fprintf(fd, "type: %i size: %i", type, size);
	}
	fprintf(fd, "\n");
	#endif // __print_DEBUG

	for (int i = 0; i < count; i++) {
		if (i > 0) fprintf(fd, " ");

		char type = types[i] & 0x1F;
		char size = types[i] >> 5;
		
		if (type == 16) {
			double* list = va_arg(v, double*);
			fprintf(fd, "[");
			__print_color(fd, __print_color_number);
			int j=0;
			while (list[j] != DBL_MAX) {
				if (j>0) fprintf(fd, " ");
				fprintf(fd, "%.2lf", list[j]);
				j++;
			}
			__print_color(fd, __print_color_normal);
			fprintf(fd, "]");
		}
		else if (type == 1) {
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
			fprintf(fd, "%s", va_arg(v, char*));
			//fprintf(fd, "\"%s\"", va_arg(v, char*));
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
