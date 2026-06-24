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
        printf("3. Modifier une personne\n");
        printf("4. Supprimer une personne\n");
        printf("5. Sauvegarder (texte + binaire)\n");
        printf("6. Charger depuis fichier binaire\n");
        printf("7. Quitter\n\n");
        printf("Choix: ");
        scanf("%d", &choice);
        getchar(); /* Enlève le '\\n' du buffer */

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
                    print_error("Aucune personne à modifier");
                    break;
                }

                print_header("MODIFIER UNE PERSONNE");
                printf("Personnes disponibles:\n");
                for (int i = 0; i < person_count; i++) {
                    display_person(&persons[i]);
                }

                int id;
                printf("\nEntrez l'ID de la personne à modifier: ");
                scanf("%d", &id);
                getchar();

                int index = find_person_index(persons, person_count, id);
                if (index == -1) {
                    print_error("Personne non trouvée!");
                    break;
                }

                char name[MAX_NAME_LENGTH];
                char firstname[MAX_FIRSTNAME_LENGTH];
                int age;

                printf("\nDonnées actuelles:\n");
                display_person(&persons[index]);

                print_info("Entrez le nouveau nom:");
                fgets(name, MAX_NAME_LENGTH, stdin);
                name[strcspn(name, "\n")] = '\0';

                print_info("Entrez le nouveau prénom:");
                fgets(firstname, MAX_FIRSTNAME_LENGTH, stdin);
                firstname[strcspn(firstname, "\n")] = '\0';

                print_info("Entrez le nouvel âge:");
                scanf("%d", &age);
                getchar();

                if (update_person(persons, person_count, id, name, firstname, age)) {
                    print_success("Personne modifiée!");
                    printf("\nNouvelles données:\n");
                    display_person(&persons[index]);
                } else {
                    print_error("Erreur lors de la modification!");
                }
                break;
            }

            case 4: {
                if (person_count == 0) {
                    print_error("Aucune personne à supprimer");
                    break;
                }

                print_header("SUPPRIMER UNE PERSONNE");
                printf("Personnes disponibles:\n");
                for (int i = 0; i < person_count; i++) {
                    display_person(&persons[i]);
                }

                int id;
                printf("\nEntrez l'ID de la personne à supprimer: ");
                scanf("%d", &id);
                getchar();

                int index = find_person_index(persons, person_count, id);
                if (index == -1) {
                    print_error("Personne non trouvée!");
                    break;
                }

                printf("\nPersonne à supprimer:\n");
                display_person(&persons[index]);

                printf("\nÊes-vous sûr? (O/N): ");
                char confirm;
                scanf("%c", &confirm);
                getchar();

                if (confirm == 'O' || confirm == 'o') {
                    if (delete_person(persons, &person_count, id)) {
                        print_success("Personne supprimée!");
                    } else {
                        print_error("Erreur lors de la suppression!");
                    }
                } else {
                    print_info("Suppression annulée");
                }
                break;
            }

            case 5: {
                if (person_count == 0) {
                    print_error("Aucune personne à sauvegarder");
                } else {
                    save_text_file("personnes.txt", persons, person_count);
                    save_binary_file("personnes.bin", persons, person_count);
                    print_success("Fichiers sauvegardés!");
                }
                break;
            }

            case 6: {
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

            case 7: {
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
