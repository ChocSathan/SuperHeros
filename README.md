
# SuperHeros 

Ce projet contient un programme en C qui permet de gérer une base de données de super-héros. Il utilise les bibliothèques `jansson` pour la gestion des fichiers JSON et `readline` pour une interaction utilisateur simplifiée via la ligne de commande.

## Développeurs

Ce projet a été développé par :

- Mathis Grattepanche
- Nathan Mariage

## Fonctionnalités principales
- Ajouter de nouveaux super-héros à la base de données.
- Rechercher des super-héros existants.
- Jouer a un quiz sur les Superhéros.
- Modifier ou supprimer des entrées.
- Afficher la liste complète des super-héros.

## Prérequis
Assurez-vous d'avoir les bibliothèques suivantes installées sur votre système :
- `jansson`
- `readline`

## Compilation
Suivez les commandes ci-dessous pour compiler le programme en fonction de votre système d'exploitation.

### Linux
```bash
gcc main.c -o main -I include -L/usr/lib -ljansson -lreadline
```

### Windows
```bash
gcc main.c -o bin/main -I include -L lib -ljansson -lreadline
```

## Exécution
Une fois compilé, exécutez le programme avec la commande suivante :
```bash
./main
```
ou, sur Windows :
```bash
bin\main.exe
```

## Structure du projet
- `main.c` : Contient le code principal du programme.
- `bin/` : Répertoire pour les fichiers exécutables.




