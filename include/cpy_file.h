#ifndef CPY_FILE_H
#define CPY_FILE_H

char* file_read(const char* filename);
void file_write(const char* filename, const char* buffer);
void file_remove(const char* fn);
void file_append(const char* filename, const char* buffer);
long file_size(const char* filename);
bool file_exists(const char* fn);
bool dir_exists(const char* dirName);
char* input(const char* prompt);

#endif
