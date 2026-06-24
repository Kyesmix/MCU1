#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "person.h"
#include "file_handler.h"
#include "console.h"

#define MAX_PERSONS 100

int main() {
    Person* persons = (Person*)malloc(sizeof(Person) * MAX_PERSONS);
    int person_count = 0;
    int next_id = 1;
    int choice;

    if (!persons) {
        print_error("Erreur: allocation mémoire échouée");
        return 1;
    }

    while (1) {
        clear_screen();
        print_header("GESTION DES PERSONNES");
        printf("\nNombre de personnes: %d\n\n", person_count);
        printf("1. Ajouter une personne\n");
        printf("2. Afficher toutes les personnes\n");
        printf("3. Sauvegarder (texte + binaire)\n");
        printf("4. Charger depuis fichier binaire\n");
        printf("5. Quitter\n\n");
        printf("Choix: ");
        scanf("%d", &choice);
        getchar(); /* Enlève le '\n' du buffer */

        switch (choice) {
            case 1: {
                if (person_count >= MAX_PERSONS) {
                    print_error("Maximum de personnes atteint!");
                    break;
                }

                char name[MAX_NAME_LENGTH];
                char firstname[MAX_FIRSTNAME_LENGTH];
                int age;

                print_info("Entrez le nom (ex: RAKOTO NOMENJANAHARY):");
                fgets(name, MAX_NAME_LENGTH, stdin);
                name[strcspn(name, "\n")] = '\0';

                print_info("Entrez le prénom (ex: Safidy Jean Honoré):");
                fgets(firstname, MAX_FIRSTNAME_LENGTH, stdin);
                firstname[strcspn(firstname, "\n")] = '\0';

                print_info("Entrez l'âge:");
                scanf("%d", &age);
                getchar();

                Person* p = create_person(next_id, name, firstname, age);
                if (p) {
                    persons[person_count] = *p;
                    person_count++;
                    next_id++;
                    free_person(p);
                    print_success("Personne ajoutée!");
                } else {
                    print_error("Erreur lors de la création!");
                }
                break;
            }

            case 2: {
                if (person_count == 0) {
                    print_warning("Aucune personne enregistrée");
                } else {
                    print_header("LISTE DES PERSONNES");
                    for (int i = 0; i < person_count; i++) {
                        display_person(&persons[i]);
                    }
                }
                break;
            }

            case 3: {
                if (person_count == 0) {
                    print_error("Aucune personne à sauvegarder");
                } else {
                    save_text_file("personnes.txt", persons, person_count);
                    save_binary_file("personnes.bin", persons, person_count);
                    print_success("Fichiers sauvegardés!");
                }
                break;
            }

            case 4: {
                Person* loaded = NULL;
                int count = load_binary_file("personnes.bin", &loaded);
                if (count > 0) {
                    person_count = count;
                    free(persons);
                    persons = loaded;
                    next_id = persons[count - 1].id + 1;
                    print_success("Fichier chargé!");
                }
                break;
            }

            case 5: {
                print_info("Au revoir!");
                free(persons);
                return 0;
            }

            default:
                print_error("Choix invalide");
        }

        printf("\nAppuyez sur Entrée...");
        getchar();
    }

    free(persons);
    return 0;
}
