#include "cpy.h"
/*char* file_read(const char* filename) {
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




bool file_exists(const char* fn) {
	FILE* file = fopen(fn, "r");
	if (file) {
		fclose(file);
		return true;
	}
	return false;
}




void file_remove(const char* fn) {
	remove(fn);
}




bool dir_exists(const char* dirName) {
	#ifdef _WIN32
	if (_access(dirName, 0) == 0) {
		struct stat status;
		stat(dirName, &status);
		return (status.st_mode & S_IFDIR) != 0;
	}
	#else
	DIR* dir = opendir(dirName);
	if (dir) {
		closedir(dir);
		return true;
	}
	else closedir(dir);
	#endif

	return false;
}*/
