# SAE 1.01 - RMAN Studio

## /!\ Message à l'attention des membres du groupe RMAN
Pensez à lire ce document **en entier** pour pas réécrire 50 fois la même chose dans 50 fichiers différents. (question -> ping Globo sur le serveur Discord).  
D'ailleurs si vous pouviez mettre à jour ce readme (notamment le 1. si vous ajoutez des trucs et le 3. dans la partie sur votre jeu) lorsque vous ajoutez des trucs c'est cool :)  
Aussi, pensez à commenter votre code sinon Casali va venir vous tabasser chez vous cette nuit.


## Introduction
Ce programme C++ simule un tournoi.


## Sommaire
1. ### L'accès global
	- Constantes
	- Fonctions
2. ### Le tournoi
	- Structs
	- Création des joueurs
	- Déroulement de la création des équipes
	- Matchmaking
	- Choix des jeux
3. ### Les jeux
	- Memory
	- Morpion
	- Puissance 4
	- Dames
	- Echecs


## 1. L'accès global

Certaines *constantes / fonctions* peuvent être nécessaire dans plusieurs programmes différents, il est donc préférable de les écrires une seule fois dans un fichier global. Cela permet de modifier leur *valeur / fonctionnement* dans tout le projet en une seule fois plutôt que de chercher dans tous les fichiers où elle est utilisée.  
Ces *constantes / fonctions* sont stockées dans le fichier `/global.hpp`. Pour les importer dans n'importe quel programme du projet il suffit d'ajouter la ligne :
```cpp
#include "./global.hpp"
```
On notera que le chemin est relatif, il faut donc adapter le chemin à l'emplacement du fichier où la commande est écrite.

### 1.1 Constantes
L'appel des constantes se fait avec la commande :
```cpp
global_const::nom_constante
```
Pour simplifier cela, il est aussi possible d'utiliser un espace de nom :
```cpp
using namespace global_const;
//dans ce cas, pas besoin de mettre "global_const::" devant le nom de la variable
```

#### 1.1.1 NAMEPATH
Contient le chemin relatif du fichier `/tournament/students.txt` du point de vue de l'exécutable créé lors de la compilation.
```cpp
const string NAMEPATH;
```
#### 1.1.2 waitMsg
Contient le message à afficher lorsque le programme attend la validation de l'utilisateur pour continuer.
```cpp
const string waitMsg;
```
#### 1.1.3 inputErrMsg
Contient le message à afficher lorsque le programme l'utilisateur fait une erreur dans sa saisie (mauvais type, en dehors des bornes...)
```cpp
const string inputErrMsg;
```
#### 1.1.4 MINTEAMS
Contient le nombre minimum d'équipes que l'utilisateur choisit au début du tournoi.
```cpp
const unsigned MINTEAMS;
```
#### 1.1.5 MAXTEAMS
Contient le nombre maximum d'équipes que l'utilisateur choisit au début du tournoi.
```cpp
const unsigned MAXTEAMS;
```
#### 1.1.6 GAMESNAME
Contient le nom de tous les jeux.
```cpp
const vector<string> GAMESNAME;
```
#### 1.1.7 NBGAMES
Contient le nombre de jeux total, sa valeur est la longueur de `GAMESNAME` (1.1.6)
```cpp
const unsigned NBGAMES;
```

### 1.2 Fonctions
L'appel des fonctions se fait avec la commande :
```cpp
global_func::nom_fonction()
```
Pour simplifier cela, il est aussi possible d'utiliser un espace de nom :
```cpp
using namespace global_func;
//dans ce cas, pas besoin de mettre "global_func::" devant le nom de la fonction
```

#### 1.2.1 test
Affiche *test* dans la console. Utile pour repérer à quel moment un programme plante quand le message d'erreur n'est pas assez explicite.
```cpp
void test();
```
#### 1.2.2 readFile
Récupère la liste de toutes les lignes d'un document texte dont le chemin est passé en paramètre (Un chemin relatif part toujours de l'exécutable créé lors de la copmilation).
```cpp
vector<string> readFile(const string & path);
```
#### 1.2.3 ask4UInput
Affiche l'invite passée en paramètre et renvoie la saisie de l'utilisateur.
```cpp
string ask4UInput(const string & invite);
```
#### 1.2.4 pressEnter
Attend que l'utilisateur appuye sur la touche Enter (utilise `waitMsg` (1.1.2) comme message d'invite)
```cpp
void pressEnter();
```
#### 1.2.5 randomSort
Mélange une liste aléatoirement avec des permutations
```cpp
template <typename T>
vector<T> randomSort(const vector<T> & v);
```
#### 1.2.6 leftAlign
Complète une chaîne de caractères par `nb_char-txt.size()` espaces à droite (utile pour `cuteLilBoard()` (1.2.9)
```cpp
string leftAlign(const string & txt, const unsigned & nb_char);
```
#### 1.2.7 rightAlign
Complète une chaîne de caractères par `nb_char-txt.size()` espaces à gauche (utile pour `cuteLilBoard()` (1.2.9)
```cpp
string rightAlign(const string & txt, const unsigned & nb_char);
```
#### 1.2.8 centerAlign
Complète une chaîne de caractères par `nb_char-txt.size()` espaces répartis à gauche et à droite (utile pour `cuteLilBoard()` (1.2.9)
```cpp
string centerAlign(const string & txt, const unsigned & nb_char);
```
#### 1.2.9 cuteLilBoard
Affiche un tableau dans la console.
```cpp
void cuteLilBoard(const vector<vector<string>> & content, const vector<char> & align={}, const bool & header=false);
```
`content` est la liste des éléments du tableau. Exemple : `{ {"a", "b", "c"}, {"d", "e", "f"} }` fera un tableau comme celui-ci :
```
---------
| a | d |
---------
| b | e |
---------
| c | f |
---------
```
`align` correspond à l'alignement dans chaque colonne (voir 1.2.6/1.2.7/1.2.8). Si le paramètre n'est pas renseigné, les colonnes seront centrées par défaut. Exemple : `{'r', 'l', 'c'}` fera un tableau comme celui-ci :
```
----------------------
|    a | a    |  a   |
----------------------
|   bb | bb   |  bb  |
----------------------
|  ccc | ccc  | ccc  |
----------------------
| dddd | dddd | dddd |
----------------------
```
`header` est l'argument d'entête, qui permet de séparer et de centrer la première ligne du tableau, exemple :
```
----------------
|   a   |  d   |
----------------
|     b |    b |
|    cc |   cc |
|   ddd |  ddd |
|  eeee | eeee |
| fffff |   ab |
----------------
```


## 2. Le tournoi

### Exemple :
Supposons que nous nous trouvons dans le fichier `.../file01.cpp` et que nous voulons utiliser une fonction qui se trouve dans le fichier `.../file02.cpp`, il suffit d'ajouter la ligne suivant dans le fichier `.../file01.cpp` :
```cpp
#include "./file02.cpp"
```

/!\ A faire


## 3. Les jeux
/!\ A faire
