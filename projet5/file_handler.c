#include "file_handler.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Écrit l'en-tête du fichier binaire */
void write_header(FILE* f, int record_size, int record_count) {
    fwrite(&record_size, sizeof(int), 1, f);
    fwrite(&record_count, sizeof(int), 1, f);
}

/* Lit l'en-tête du fichier binaire */
int read_header(FILE* f, int* record_size, int* record_count) {
    if (fread(record_size, sizeof(int), 1, f) != 1) return 0;
    if (fread(record_count, sizeof(int), 1, f) != 1) return 0;
    return 1;
}

/* Sauvegarde en fichier texte */
int save_text_file(const char* filename, const Person* persons, int count) {
    FILE* f = fopen(filename, "w");
    if (!f) {
        printf("Erreur: impossible d'ouvrir %s\n", filename);
        return 0;
    }

    fprintf(f, "=== ENREGISTREMENTS DES PERSONNES ===\n");
    fprintf(f, "Nombre total: %d\n\n", count);

    for (int i = 0; i < count; i++) {
        fprintf(f, "Enregistrement #%d:\n", i + 1);
        fprintf(f, "  ID: %d\n", persons[i].id);
        fprintf(f, "  Nom: %s\n", persons[i].name);
        fprintf(f, "  Prénom: %s\n", persons[i].firstname);
        fprintf(f, "  Âge: %d\n", persons[i].age);
        fprintf(f, "\n");
    }

    fclose(f);
    printf("✓ Fichier texte sauvegardé: %s\n", filename);
    return 1;
}

/* Sauvegarde en fichier binaire */
int save_binary_file(const char* filename, const Person* persons, int count) {
    FILE* f = fopen(filename, "wb");
    if (!f) {
        printf("Erreur: impossible d'ouvrir %s\n", filename);
        return 0;
    }

    int record_size = sizeof(Person);
    write_header(f, record_size, count);

    for (int i = 0; i < count; i++) {
        fwrite(&persons[i], sizeof(Person), 1, f);
    }

    fclose(f);
    printf("✓ Fichier binaire sauvegardé: %s\n", filename);
    return 1;
}

/* Charge depuis fichier binaire */
int load_binary_file(const char* filename, Person** persons) {
    FILE* f = fopen(filename, "rb");
    if (!f) {
        printf("Erreur: impossible d'ouvrir %s\n", filename);
        return 0;
    }

    int record_size, record_count;
    if (!read_header(f, &record_size, &record_count)) {
        printf("Erreur: en-tête invalide\n");
        fclose(f);
        return 0;
    }

    *persons = (Person*)malloc(sizeof(Person) * record_count);
    if (!*persons) {
        printf("Erreur: allocation mémoire échouée\n");
        fclose(f);
        return 0;
    }

    for (int i = 0; i < record_count; i++) {
        if (fread(&(*persons)[i], sizeof(Person), 1, f) != 1) {
            printf("Erreur: lecture échouée\n");
            free(*persons);
            fclose(f);
            return 0;
        }
    }

    fclose(f);
    printf("✓ %d enregistrements chargés\n", record_count);
    return record_count;
}
