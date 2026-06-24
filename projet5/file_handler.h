#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include "person.h"

/* Prototypes */
int save_text_file(const char* filename, const Person* persons, int count);
int save_binary_file(const char* filename, const Person* persons, int count);
int load_binary_file(const char* filename, Person** persons);
void write_header(FILE* f, int record_size, int record_count);
int read_header(FILE* f, int* record_size, int* record_count);

#endif
