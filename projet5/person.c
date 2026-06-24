#include "person.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

/* Traite les noms : premier mot complet + initiales des autres */
void process_name(const char* input, char* output) {
    if (!input || !output) return;

    char temp[MAX_NAME_LENGTH];
    strncpy(temp, input, MAX_NAME_LENGTH - 1);
    temp[MAX_NAME_LENGTH - 1] = '\0';

    /* Compter les mots */
    int word_count = 0;
    char* token = strtok(temp, " ");
    char words[10][MAX_NAME_LENGTH];

    while (token && word_count < 10) {
        strcpy(words[word_count], token);
        word_count++;
        token = strtok(NULL, " ");
    }

    if (word_count == 0) {
        strcpy(output, ".");
        return;
    }

    if (word_count == 1) {
        strcpy(output, words[0]);
        return;
    }

    /* Premier mot complet + initiales */
    strcpy(output, words[0]);
    for (int i = 1; i < word_count; i++) {
        strcat(output, ".");
        strncat(output, words[i], 1);
    }
}

/* Traite les prénoms : même logique que les noms */
void process_firstname(const char* input, char* output) {
    if (!input || !output) {
        strcpy(output, ".");
        return;
    }

    if (strlen(input) == 0) {
        strcpy(output, ".");
        return;
    }

    process_name(input, output);
}

/* Crée une personne avec traitement des noms */
Person* create_person(int id, const char* name, const char* firstname, int age) {
    Person* p = (Person*)malloc(sizeof(Person));
    if (!p) return NULL;

    p->id = id;
    p->age = age;
    p->timestamp = time(NULL);

    process_name(name, p->name);
    process_firstname(firstname, p->firstname);

    return p;
}

/* Libère la mémoire */
void free_person(Person* p) {
    if (p) free(p);
}

/* Affiche une personne */
void display_person(const Person* p) {
    if (!p) return;
    printf("  ID: %d | Nom: %s | Prénom: %s | Âge: %d\n",
           p->id, p->name, p->firstname, p->age);
}

/* Trouve l'index d'une personne par ID */
int find_person_index(Person* persons, int count, int id) {
    for (int i = 0; i < count; i++) {
        if (persons[i].id == id) {
            return i;
        }
    }
    return -1;
}

/* Supprime une personne par ID */
int delete_person(Person* persons, int* count, int id) {
    int index = find_person_index(persons, *count, id);
    
    if (index == -1) {
        return 0; /* Personne non trouvée */
    }

    /* Décaler tous les éléments après l'index */
    for (int i = index; i < *count - 1; i++) {
        persons[i] = persons[i + 1];
    }

    (*count)--;
    return 1; /* Succès */
}

/* Modifie une personne par ID */
int update_person(Person* persons, int count, int id, const char* name, const char* firstname, int age) {
    int index = find_person_index(persons, count, id);
    
    if (index == -1) {
        return 0; /* Personne non trouvée */
    }

    /* Modifier les champs */
    process_name(name, persons[index].name);
    process_firstname(firstname, persons[index].firstname);
    persons[index].age = age;
    persons[index].timestamp = time(NULL);

    return 1; /* Succès */
}
