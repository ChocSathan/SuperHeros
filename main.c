#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <jansson.h>

#define FILE_PATH "SuperHeros.json"

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
void afficherDetailsSuperHero(int id, const char *filePath);

int main() {
    int choix, id;

    while (1) {
        printf("\n--- Menu Super-Héros ---\n");
        printf("1. Afficher la liste des super-héros\n");
        printf("2. Afficher les détails d'un super-héros\n");
        printf("3. Quitter\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                afficherListeSuperHeros(FILE_PATH);
                break;
            case 2:
                printf("Entrez l'ID du super-héros : ");
                scanf("%d", &id);
                afficherDetailsSuperHero(id, FILE_PATH);
                break;
            case 3:
                printf("Au revoir !\n");
                return 0;
            default:
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

void afficherDetailsSuperHero(int id, const char *filePath) {
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

            printf("\nDétails de %s :\n", name);
            printf("Intelligence: %lld\n", json_integer_value(json_object_get(stats, "intelligence")));
            printf("Force: %lld\n", json_integer_value(json_object_get(stats, "strength")));
            printf("Vitesse: %lld\n", json_integer_value(json_object_get(stats, "speed")));
            printf("Durabilité: %lld\n", json_integer_value(json_object_get(stats, "durability")));
            printf("Puissance: %lld\n", json_integer_value(json_object_get(stats, "power")));
            printf("Combat: %lld\n", json_integer_value(json_object_get(stats, "combat")));
            json_decref(root);
            return;
        }
    }

    printf("Super-héros avec ID %d non trouvé.\n", id);
    json_decref(root);
}
