#ifndef PERSON_H
#define PERSON_H

#include <time.h>

#define MAX_NAME_LENGTH 256
#define MAX_FIRSTNAME_LENGTH 256
#define MAX_FILENAME 256

typedef struct {
    int id;
    char name[MAX_NAME_LENGTH];
    char firstname[MAX_FIRSTNAME_LENGTH];
    int age;
    time_t timestamp;
} Person;

/* Prototypes */
Person* create_person(int id, const char* name, const char* firstname, int age);
void process_name(const char* input, char* output);
void process_firstname(const char* input, char* output);
void free_person(Person* p);
void display_person(const Person* p);

#endif
