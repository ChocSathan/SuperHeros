
# SuperHeros 

Ce projet contient un programme en C qui permet de gérer une base de données de super-héros. Il utilise les bibliothèques `jansson` pour la gestion des fichiers JSON et `readline` pour une interaction utilisateur simplifiée via la ligne de commande.

## Développeurs

Ce projet a été développé par :

- Mathis Grattepanche
- Nathan Mariage

## Fonctionnalités principales
- Afficher la liste des Super-héros enregistré dans un fichier json.
- Rechercher des Super-héros et voir les détails.
- Jouer a un quiz sur les Super-héros.
- Créer et modifier un fichier json externe en rajoutant/supprimant des Super-héros

## Prérequis
Assurez-vous d'avoir les bibliothèques suivantes installées sur votre système :
- jansson
- readline

## Compilation
Suivez les commandes ci-dessous pour compiler le programme en fonction de votre système d'exploitation.

### Linux

gcc main.c -o main -I include -L/usr/lib -ljansson -lreadline


### Windows

gcc main.c -o bin/main -I include -L lib -ljansson -lreadline


## Exécution
Une fois compilé, exécutez le programme avec la commande suivante :

./main

ou, sur Windows :

bin\main.exe


## Structure du projet
-  README.md : Ce fichier même qui contient les informations du Projet
-  main.c : Contient le code principal du programme.
-  bin/ : Répertoire pour les fichiers exécutables.




