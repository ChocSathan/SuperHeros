#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cjson/cJSON.h>

/*
Example of JSON data:
[
{
    "id": 1,
    "name": "Superman",
    "id-api": 644,
    "slug": "644-superman",
    "powerstats": {
        "intelligence": 94,
        "strength": 100,
        "speed": 100,
        "durability": 100,
        "power": 100,
        "combat": 85
    },
    "appearance": {
        "gender": "Male",
        "race": "Kryptonian",
        "height": [
            "6'3",
            "191 cm"
        ],
        "weight": [
            "225 lb",
            "101 kg"
        ],
        "eyeColor": "Blue",
        "hairColor": "Black"
    },
    "weight": [
        "225 lb",
        "101 kg"
    ],
    "eyeColor": "Blue",
    "hairColor": "Black"
},
{
    "id": 2,
    "name": "Batman",
    "id-api": 69,
    "slug": "69-batman",
    "powerstats": {
        "intelligence": 81,
        "strength": 40,
        "speed": 29,
        "durability": 55,
        "power": 63,
        "combat": 90
    },
    "appearance": {
        "gender": "Male",
        "race": "Human",
        "height": [
            "5'10",
            "178 cm"
        ],
        "weight": [
            "170 lb",
            "77 kg"
        ],
        "eyeColor": "Blue",
        "hairColor": "Black"
    },
    "weight": [
        "170 lb",
        "77 kg"
    ],
    "eyeColor": "Blue",
    "hairColor": "Black"
}
]
*/

cJSON *read_json_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Unable to open file");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *data = (char *)malloc(length + 1);
    if (data == NULL) {
        perror("Unable to allocate memory");
        fclose(file);
        return NULL;
    }

    fread(data, 1, length, file);
    data[length] = '\0';

    fclose(file);

    cJSON *json = cJSON_Parse(data);
    if (json == NULL) {
        printf("Error parsing JSON: %s\n", cJSON_GetErrorPtr());
        free(data);
        return NULL;
    }
        return json;
}

void print_json_data(cJSON *json) {
    /* 
    Exemple of data in parametters

    {
    "id": 1,
    "name": "Superman",
    "id-api": 644,
    "slug": "644-superman",
    "powerstats": {
        "intelligence": 94,
        "strength": 100,
        "speed": 100,
        "durability": 100,
        "power": 100,
        "combat": 85
    },
    "appearance": {
        "gender": "Male",
        "race": "Kryptonian",
        "height": [
            "6'3",
            "191 cm"
        ],
        "weight": [
            "225 lb",
            "101 kg"
        ],
        "eyeColor": "Blue",
        "hairColor": "Black"
    },
    "weight": [
        "225 lb",
        "101 kg"
    ],
    "eyeColor": "Blue",
    "hairColor": "Black"
    }
    */
    cJSON *item = NULL;
}

void get_data_by_id(cJSON *json, int id) {
    cJSON *item = NULL;
    cJSON_ArrayForEach(item, json) {
        if (cJSON_IsObject(item)) {
            cJSON *subitem = NULL;
            cJSON_ArrayForEach(subitem, item) {
                if (cJSON_IsNumber(subitem) && subitem->valuedouble == id) {
                    return;
                }
            }
        }
    }
    printf("No data found for id %d\n", id);
}

int main() {
    cJSON *data = read_json_file("SuperHeros.json");
    if (data == NULL) {
        return 1;
    }
    get_data_by_id(data, 2);
    return 0;
}