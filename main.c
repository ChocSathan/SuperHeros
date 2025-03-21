#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <jansson.h>
#include <readline/readline.h>

#define FILE_PATH "bin/SuperHeros.json"

// Structure pour stocker les stats des super-héros
typedef struct {
    int id;
    char name[50];
    int intelligence;
    int strength;
    int speed;
    int durability;
    int power;
    int combat;
} SuperHero;

void afficherListeSuperHeros(const char *filePath);
void afficherDetailsSuperHeroParId(int id, const char *filePath);
void afficherDetailsSuperHeroParNom(char *name, const char *filepath);
void afficherDetailsSuperHeroParStat(char *stat, const char *filepath);
void afficherDetailsSuperHeroParStatSup(char *stat, int value, json_t *root);
void afficherDetailsSuperHeroParStatInf(char *stat, int value, json_t *root);
void afficherDetailsSuperHeroParStatEgal(char *stat, int value, json_t *root);
void comparaisonSuperHeros(int id1, int id2, const char *filePath);
void creationSuperHeros(const char *filepath);
void supprimerSuperHeros(int id, const char *filepath);
void sauvegardeSuperHeros(int n, int Tab[], const char *filepath);
void ajoutSuperHeros(int id, const char *filepath);
void suppSuperHero(int id, const char *filepath);
void quizz(const char *filepath);

int main() {
    int id, search;
    int choix = 0;

    while (choix != 7) {
        printf("\n--- Menu Super-Héros ---\n");
        printf("1. Afficher la liste des super-héros\n");
        printf("2. Rechercher un super-héros\n");
        printf("3. Comparaison de deux super-héros\n");
        printf("4. Modifier la liste de super-héros\n");
        printf("5. Sauvegarder une liste externe de super-héros\n");
        printf("6. Quizz sur les super-héros\n");
        printf("7. Quitter\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        if (choix == 1) {
            afficherListeSuperHeros(FILE_PATH);
            choix = 0;
        } else if (choix == 2) {
            search = 0;
            while (search != 9) {
                printf("\n--- Recherche Super-Héros ---\n");
                printf("1. Rechercher par ID\n");
                printf("2. Rechercher par nom\n");
                printf("3. Rechercher par intelligence\n");
                printf("4. Rechercher par force\n");
                printf("5. Rechercher par vitesse\n");
                printf("6. Rechercher par durabilité\n");
                printf("7. Rechercher par puissance\n");
                printf("8. Rechercher par combat\n");
                printf("9. Retour\n");
                printf("Votre choix : ");
                scanf("%d", &search);

                if (search == 1) {
                    printf("Entrez l'ID du super-héros : ");
                    scanf("%d", &id);
                    afficherDetailsSuperHeroParId(id, FILE_PATH);
                    search = 0;
                } else if (search == 2) {
                    char *name = readline("Entrez le nom du super-héros : ");
                    afficherDetailsSuperHeroParNom(name, FILE_PATH);
                    free(name);
                } else if (search == 3) {
                    afficherDetailsSuperHeroParStat("intelligence", FILE_PATH);
                } else if (search == 4) {
                    afficherDetailsSuperHeroParStat("strength", FILE_PATH);
                } else if (search == 5) {
                    afficherDetailsSuperHeroParStat("speed", FILE_PATH);
                } else if (search == 6) {
                    afficherDetailsSuperHeroParStat("durability", FILE_PATH);
                } else if (search == 7) {
                    afficherDetailsSuperHeroParStat("power", FILE_PATH);
                } else if (search == 8) {
                    afficherDetailsSuperHeroParStat("combat", FILE_PATH);
                } else if (search == 9) {
                    printf("Retour au menu principal.\n");
                    choix = 0;
                } else {
                    printf("Choix invalide, réessayez.\n");
                }
            }
        } else if (choix == 3) {
            printf("Entrez l'id du premier super-héros : ");
            int id1;
            scanf("%d", &id1);
            printf("Entrez l'id du deuxième super-héros : ");
            int id2;
            scanf("%d", &id2);
            comparaisonSuperHeros(id1, id2, FILE_PATH);
        } else if (choix == 4) {
            int modif = 0;
            while (modif != 3)
            {
                printf("\n--- Modification Super-Héros ---\n");
                printf("1. Création d'un super-héros\n");
                printf("2. Suppression d'un super-héros\n");
                printf("3. Retour\n");
                printf("Votre choix : ");
                scanf("%d", &modif);
                if (modif == 1) {
                    creationSuperHeros(FILE_PATH);
                } else if (modif == 2) {
                    printf("Entrez l'ID du super-héros à supprimer : ");
                    int id;
                    scanf("%d", &id);
                    supprimerSuperHeros(id, FILE_PATH);
                } else if (modif == 3) {
                    printf("Retour au menu principal.\n");
                    choix = 0;
                } else {
                    printf("Choix invalide, réessayez.\n");
                }
            }
        } else if (choix == 5) {
            int sauv = 0;
            while (sauv != 4)
            {   
                printf("\n--- Sauvegarde Super-Héros ---\n");
                printf("1. Creation du fichier\n");
                printf("2. Ajout d'un super hero\n");
                printf("3. Suppression d'un super hero\n");
                printf("4. Retour\n");
                printf("Votre choix : ");
                scanf("%d", &sauv);
                if (sauv == 1) {
                    printf("Combien de super-héros voulez-vous sauvegarder : ");
                    int n;
                    scanf("%d", &n);
                    int Tab[n];
                    for (int i = 0; i < n; i++) {
                        printf("Entrez l'id du super-héros : ");
                        scanf("%d", &Tab[i]);
                    }
                    sauvegardeSuperHeros(n, Tab, FILE_PATH);
            
                } else if (sauv == 2) {
                    FILE *file = fopen("SuperHeros_Saved.json", "r");
                    if (file) {
                        int id;
                        printf("Entrez l'ID du super-héros à ajouter : ");
                        scanf("%d", &id);
                        ajoutSuperHeros(id, FILE_PATH);  // Corrected function name
                    } else {
                        printf("Le fichier SuperHeros_Saved.json n'existe pas.\n");
                    }
                } else if (sauv == 3) {
                    FILE *file = fopen("SuperHeros_Saved.json", "r");
                    if (file) {
                        int id;
                        printf("Entrez l'ID du super-héros à supprimer : ");
                        scanf("%d", &id);
                        suppSuperHero(id, FILE_PATH);
                    } else {
                        printf("Le fichier SuperHeros_Saved.json n'existe pas.\n");
                    }
                } else if (sauv == 4) {
                    printf("Retour au menu principal.\n");
                    choix = 0;
                } else {
                    printf("Choix invalide, réessayez.\n");
                }
            }
        } else if (choix == 6) {
            printf("Quizz sur les super-héros\n");
            quizz(FILE_PATH);
        } else if (choix == 7) {
            printf("Au revoir !\n");
        } else {
            printf("Choix invalide, réessayez.\n");
        }
    }
    return 0;
}

void afficherListeSuperHeros(const char *filePath) {
    json_error_t error;
    json_t *root = json_load_file(filePath, 0, &error);

    if (!root) {
        fprintf(stderr, "Erreur de chargement JSON : %s\n", error.text);
        return;
    }

    size_t index;
    json_t *hero;

    printf("\nListe des super-héros :\n");
    json_array_foreach(root, index, hero) {
        int id = json_integer_value(json_object_get(hero, "id"));
        const char *name = json_string_value(json_object_get(hero, "name"));
        printf("ID: %d | Nom: %s\n", id, name);
    }

    json_decref(root);
}

void afficherDetailsSuperHeroParId(int id, const char *filePath) {
    json_error_t error;
    json_t *root = json_load_file(filePath, 0, &error);

    if (!root) {
        fprintf(stderr, "Erreur de chargement JSON : %s\n", error.text);
        return;
    }

    size_t index;
    json_t *hero;
    json_array_foreach(root, index, hero) {
        if (json_integer_value(json_object_get(hero, "id")) == id) {
            const char *name = json_string_value(json_object_get(hero, "name"));
            json_t *stats = json_object_get(hero, "powerstats");

            printf("\n\nDétails de %s :\n", name);
            printf("\nPowerstats:\n");
            printf("Intelligence: %lld\n", json_integer_value(json_object_get(stats, "intelligence")));
            printf("Force: %lld\n", json_integer_value(json_object_get(stats, "strength")));
            printf("Vitesse: %lld\n", json_integer_value(json_object_get(stats, "speed")));
            printf("Durabilité: %lld\n", json_integer_value(json_object_get(stats, "durability")));
            printf("Puissance: %lld\n", json_integer_value(json_object_get(stats, "power")));
            printf("Combat: %lld\n", json_integer_value(json_object_get(stats, "combat")));

            json_t *appearance = json_object_get(hero, "appearance");

            printf("\nApparence:\n");
            printf("Genre: %s\n", json_string_value(json_object_get(appearance, "gender")));
            printf("Race: %s\n", json_string_value(json_object_get(appearance, "race")));
            
            json_t *height = json_object_get(appearance, "height");
            printf("Taille: %s (%s)\n", json_string_value(json_array_get(height, 0)), json_string_value(json_array_get(height, 1)));
            
            json_t *weight = json_object_get(appearance, "weight");
            printf("Poids: %s (%s)\n", json_string_value(json_array_get(weight, 0)), json_string_value(json_array_get(weight, 1)));
            
            printf("Couleur des yeux: %s\n", json_string_value(json_object_get(appearance, "eyeColor")));
            printf("Couleur des cheveux: %s\n\n", json_string_value(json_object_get(appearance, "hairColor")));
            json_decref(root);
            return;
        }
    }

    printf("\nSuper-héros avec ID %d non trouvé.\n", id);
    json_decref(root);
}

void afficherDetailsSuperHeroParNom(char *name, const char *filepath) {
    json_error_t error;
    json_t *root = json_load_file(filepath, 0, &error);

    if (!root) {
        fprintf(stderr, "Erreur de chargement JSON : %s\n", error.text);
        return;
    }

    size_t index;
    json_t *hero;
    json_array_foreach(root, index, hero) {
        if (strcasecmp(json_string_value(json_object_get(hero, "name")), name) == 0) {
            json_t *stats = json_object_get(hero, "powerstats");

            printf("\nDétails de %s :\n", name);
            printf("Intelligence: %lld\n", json_integer_value(json_object_get(stats, "intelligence")));
            printf("Force: %lld\n", json_integer_value(json_object_get(stats, "strength")));
            printf("Vitesse: %lld\n", json_integer_value(json_object_get(stats, "speed")));
            printf("Durabilité: %lld\n", json_integer_value(json_object_get(stats, "durability")));
            printf("Puissance: %lld\n", json_integer_value(json_object_get(stats, "power")));
            printf("Combat: %lld\n", json_integer_value(json_object_get(stats, "combat")));
            
            json_t *appearance = json_object_get(hero, "appearance");

            printf("\nApparence:\n");
            printf("Genre: %s\n", json_string_value(json_object_get(appearance, "gender")));
            printf("Race: %s\n", json_string_value(json_object_get(appearance, "race")));
            
            json_t *height = json_object_get(appearance, "height");
            printf("Taille: %s (%s)\n", json_string_value(json_array_get(height, 0)), json_string_value(json_array_get(height, 1)));
            
            json_t *weight = json_object_get(appearance, "weight");
            printf("Poids: %s (%s)\n", json_string_value(json_array_get(weight, 0)), json_string_value(json_array_get(weight, 1)));
            
            printf("Couleur des yeux: %s\n", json_string_value(json_object_get(appearance, "eyeColor")));
            printf("Couleur des cheveux: %s\n\n", json_string_value(json_object_get(appearance, "hairColor")));
            json_decref(root);
            return;
        }
    }

    printf("\nSuper-héros avec le nom %s non trouvé.\n", name);
    json_decref(root);
}

void afficherDetailsSuperHeroParStat(char *stat, const char *filepath) {
    json_error_t error;
    json_t *root = json_load_file(filepath, 0, &error);

    if (!root) {
        fprintf(stderr, "Erreur de chargement JSON : %s\n", error.text);
        return;
    }
    int choix = 0;
    while (choix != 4) {
        printf("\n--- Type de Recherche ---\n");
        printf("1. Supérieur\n");
        printf("2. Inférieur\n");
        printf("3. Égal\n");
        printf("4. Retour\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        if (choix == 1) {
            printf("Entrez la valeur : ");
            int value;
            scanf("%d", &value);
            afficherDetailsSuperHeroParStatSup(stat, value, root);
            choix = 4;
        } else if (choix == 2) {
            printf("Entrez la valeur : ");
            int value;
            scanf("%d", &value);
            afficherDetailsSuperHeroParStatInf(stat, value, root);
            choix = 4;
        } else if (choix == 3) {
            printf("Entrez la valeur : ");
            int value;
            scanf("%d", &value);
            afficherDetailsSuperHeroParStatEgal(stat, value, root);
            choix = 4;
        } else if (choix == 4) {
            printf("Retour au menu principal.\n");
        } else {
            printf("Choix invalide, réessayez.\n");
        }
    }
}

void afficherDetailsSuperHeroParStatSup(char *stat, int value, json_t *root) {
    size_t index;
    json_t *hero;
    json_array_foreach(root, index, hero) {
        json_t *stats = json_object_get(hero, "powerstats");
        if (json_integer_value(json_object_get(stats, stat)) > value) {
            const char *name = json_string_value(json_object_get(hero, "name"));
            printf("\nDétails de %s :\n", name);
            printf("Intelligence: %lld\n", json_integer_value(json_object_get(stats, "intelligence")));
            printf("Force: %lld\n", json_integer_value(json_object_get(stats, "strength")));
            printf("Vitesse: %lld\n", json_integer_value(json_object_get(stats, "speed")));
            printf("Durabilité: %lld\n", json_integer_value(json_object_get(stats, "durability")));
            printf("Puissance: %lld\n", json_integer_value(json_object_get(stats, "power")));
            printf("Combat: %lld\n", json_integer_value(json_object_get(stats, "combat")));
        }
    }
}

void afficherDetailsSuperHeroParStatInf(char *stat, int value, json_t *root) {
    size_t index;
    json_t *hero;
    json_array_foreach(root, index, hero) {
        json_t *stats = json_object_get(hero, "powerstats");
        if (json_integer_value(json_object_get(stats, stat)) < value) {
            const char *name = json_string_value(json_object_get(hero, "name"));
            printf("\nDétails de %s :\n", name);
            printf("Intelligence: %lld\n", json_integer_value(json_object_get(stats, "intelligence")));
            printf("Force: %lld\n", json_integer_value(json_object_get(stats, "strength")));
            printf("Vitesse: %lld\n", json_integer_value(json_object_get(stats, "speed")));
            printf("Durabilité: %lld\n", json_integer_value(json_object_get(stats, "durability")));
            printf("Puissance: %lld\n", json_integer_value(json_object_get(stats, "power")));
            printf("Combat: %lld\n", json_integer_value(json_object_get(stats, "combat")));
        }
    }
}

void afficherDetailsSuperHeroParStatEgal(char *stat, int value, json_t *root) {
    size_t index;
    json_t *hero;
    json_array_foreach(root, index, hero) {
        json_t *stats = json_object_get(hero, "powerstats");
        if (json_integer_value(json_object_get(stats, stat)) == value) {
            const char *name = json_string_value(json_object_get(hero, "name"));
            printf("\nDétails de %s :\n", name);
            printf("Intelligence: %lld\n", json_integer_value(json_object_get(stats, "intelligence")));
            printf("Force: %lld\n", json_integer_value(json_object_get(stats, "strength")));
            printf("Vitesse: %lld\n", json_integer_value(json_object_get(stats, "speed")));
            printf("Durabilité: %lld\n", json_integer_value(json_object_get(stats, "durability")));
            printf("Puissance: %lld\n", json_integer_value(json_object_get(stats, "power")));
            printf("Combat: %lld\n", json_integer_value(json_object_get(stats, "combat")));
        }
    }
}

void comparaisonSuperHeros(int id1, int id2, const char *filePath) {
    json_error_t error;
    json_t *root = json_load_file(filePath, 0, &error);

    if (!root) {
        fprintf(stderr, "Erreur de chargement JSON : %s\n", error.text);
        return;
    }

    size_t index;
    json_t *hero1;
    json_t *hero2;
    json_array_foreach(root, index, hero1) {
        if (json_integer_value(json_object_get(hero1, "id")) == id1) {
            json_array_foreach(root, index, hero2) {
                if (json_integer_value(json_object_get(hero2, "id")) == id2) {
                    const char *name1 = json_string_value(json_object_get(hero1, "name"));
                    const char *name2 = json_string_value(json_object_get(hero2, "name"));
                    json_t *stats1 = json_object_get(hero1, "powerstats");
                    json_t *stats2 = json_object_get(hero2, "powerstats");

                    printf("\nComparaison entre\t %s \tet\t %s :\n", name1, name2);
                    printf("Intelligence:\t\t %lld \t\tvs\t %lld\n", json_integer_value(json_object_get(stats1, "intelligence")),
                           json_integer_value(json_object_get(stats2, "intelligence")));
                    printf("Force:\t\t\t %lld \t\tvs\t %lld\n", json_integer_value(json_object_get(stats1, "strength")),
                           json_integer_value(json_object_get(stats2, "strength")));
                    printf("Vitesse:\t\t %lld \t\tvs\t %lld\n", json_integer_value(json_object_get(stats1, "speed")),
                           json_integer_value(json_object_get(stats2, "speed")));
                    printf("Durabilité:\t\t %lld \t\tvs\t %lld\n", json_integer_value(json_object_get(stats1, "durability")),
                           json_integer_value(json_object_get(stats2, "durability")));
                    printf("Puissance:\t\t %lld \t\tvs\t %lld\n", json_integer_value(json_object_get(stats1, "power")),
                           json_integer_value(json_object_get(stats2, "power")));
                    printf("Combat:\t\t\t %lld \t\tvs\t %lld\n", json_integer_value(json_object_get(stats1, "combat")),
                           json_integer_value(json_object_get(stats2, "combat")));
                    json_decref(root);
                    return;
                }
            }
        }
    }

    printf("Super-héros avec ID %d ou %d non trouvé.\n", id1, id2);
    json_decref(root);
}

void creationSuperHeros(const char *filepath) {
    return ;
}

void supprimerSuperHeros(int id, const char *filepath) {
    return ;
}

void sauvegardeSuperHeros(int n, int Tab[], const char *filepath) {
    json_error_t error;
    json_t *root = json_load_file(filepath, 0, &error);

    if (!root) {
        fprintf(stderr, "Erreur de chargement JSON : %s\n", error.text);
        return;
    }

    json_t *new_root = json_array();
    size_t index;
    json_t *hero;

    for (int i = 0; i < n; i++) {
        json_array_foreach(root, index, hero) {
            if (json_integer_value(json_object_get(hero, "id")) == Tab[i]) {
                json_array_append(new_root, hero);
                break;
            }
        }
    }

    if (json_dump_file(new_root, "SuperHeros_Saved.json", JSON_INDENT(4)) != 0) {
        fprintf(stderr, "Erreur de sauvegarde du fichier JSON.\n");
    } else {
        printf("Super-héros sauvegardés avec succès dans SuperHeros_Saved.json\n");
    }

    json_decref(root);
    json_decref(new_root);
}

void ajoutSuperHeros(int id, const char *filepath) {
    return ;
}

void suppSuperHero(int id, const char *filepath) {
    return ;
}

void quizz(const char *filepath) {
    return ;
}