# SAE 1.01 - RMAN Studio


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
	- Echecs
	- Pierre feuille ciseaux
	- Juste prix

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
`content` est la liste des éléments du tableau. Exemple : `{{"a", "b", "c"}, {"d", "e", "f"}}` fera un tableau comme celui-ci :
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

### 2.1 Création des joueurs
Au début du tournoi, le nom de chaque joueur est récupéré depuis le fichier `students.txt`. Par la suite, on crée une liste qui contient l'intégralité des joueurs grace à la structure de donnée définie par :
```cpp
struct player {
    string last_name;	// Nom de famille
    string first_name;	// Prénom
};
```

### 2.2 Création des équipes
Lors de la création des équipes, l'utilisateur renseigne d'abord le nombre d'équipes qui participent au tournoi, ainsi le programme éjecte aléatoirement des joueurs qui sont de trop, si le nombre de joueurs n'est pas un multiple du nombre d'équipes.  
Ensuite, l'utilisateur saisi au fur et à mesure le nom des équipes tout en voyant quel joueur a été placé dans quel équipe (les joueurs sont regroupés aléatoirement). Pour ce faire, on utilise la structure de donnée d'équipe qui prend la forme :
```cpp
struct team {
    string name;		// Nom de l'équipe
    unsigned points;		// Nombre de points
    vector<player> players;	// Tableau des joueurs de l'équipe
};
```
(NB: les équipes sont stockées dans un tableau de type `vector<team>`)

### 2.3 Matchmaking
La partie du matchmaking est assez simple puisqu'il s'agit simplement d'une fonction qui permet de regrouper les équipes 2 par 2 à partir de la liste préalablement triée par nombre de points des équipes. Cette fonction transforme le tableau d'équipes de type `vector<team>` en tableau de tableaux d'équipes de type `vector<vector<team>>`, ainsi chaque tableau du tableau a pour longueur 2  
(NB: si on a un nombre impaire d'équipes, le dernier tableau du tableau a une longueur de 1)

### 2.4 Rencontres des équipes
Pour lancer une rencontre, il faut au préalable avoir récupéré un tableau de tableau d'équipes (avec la fonction de `matchmaking` (2.3)). Ainsi, quelque soit le jeu qui est lancé, on appelle la fonction correspondante qui prend pour paramètre le nom des deux équipes qui participent à la rencontre.  
Puis, il suffit de réitérer l'appel de la fonction pour chaque tableau du tableau de matchmaking pour faire en sorte que chaque équipe joue sa rencontre. On notera que si la dernière rencontre est une équipe seule, elle est exmptée et gagne automatiquement 1 point.  
La dernière étape est d'ajouter les points à l'équipe gagnante de chaque rencontre (réponse de la fonction du mini-jeu) de la manière suivante, si une équipe gagne la rencontre, elle marque 2 points, si elle perd elle n'en marque aucun et si les équipes dont égalité dans la rencontre (possible dans certains cas tels que le morpion, le puissance 4 ou encore les échecs) les deux équipes marquent 1 point chacune.



## 3. Les jeux
Chaque programme renvoie soit 0 pour annoncer la victoire de l'équipe désignée comme équipe 1, 1 pour annoncer la victoire de l'équipe désignée en équipe 2 et 2 si jamais il y a une égalité.

### 3.1 Memory

### 3.2 Morpion

### 3.3 Puissance 4
Le jeu du puissance 4 est très simple à comprendre. Les deux équipes reçoivent aléatoirement, une couleur différente rouge ou jaune et doivent aligner 4 jetons adjacent, de manière linéaire ou diagonale pour remporter la partie. Le fonctionnement du jeu se fait ainsi : 
	-récupération des deux équipes, 
	-choix aléatoire des couleurs, 
	-un tableau vierge de puissance 4 est généré, 
	-les jaunes choisissent une colonne, 
	-si cette dernière a au moins une case vide ils mettent un jeton à la case libre la plus basse du tableau, sinon ils choisissent une autre colonne, 
	-le programme vérifie qu'il n'y a aucune condition de victoire remplit, 
	-les rouges jouent à leur tour, 
	-le programme vérifie qu'il n'y a aucune condition de victoire remplit, 
	-il vérifie que toutes les cases du tableau ne soient pas remplit, 
	-si une condition de victoire est remplit le programme renvoie 0 si l'équipe n°1 gagne, 1 si l'équipe n°2 gagne et 2 si toutes les cases du tableau sont remplit et qu'il n'y a aucune victoire.

### 3.4 Echecs
Le mini-jeu d'échec reprend les règles basiques du jeu d'échec.  
Le fonctionnement du jeu se fait au travers de plusieurs étapes qui sont les suivantes :
	- 

### 3.5 Pierre feuille ciseaux
Le but du jeu est simple. Il faut essayer de gagner en choississant l'une des possibilités qui sont la pierre, qui gagne contre les ciseaux, la feuille qui gagne contre la pierre et les ciseaux qui gagnent contre la feuille. La première équipe à arriver au score max définit au début de la partie gagne.  
Le programme fonctionne de sorte à ce que chaque combinaisons possibles soit prises en compte (victoire pour un des deux, égalité ou réessayer si jamais le choix n'est pas dans les choix proposés).

### 3.6 Juste prix
Le but de ce jeu est de trouver le nombre généré aléatoirement entre 1 et un maximum choisis avant son adversaire.  
L'équipe qui commence est sélectionné de manière aléatoire et commence la partie. Le programme renverra "c'est plus" si le nombre mystère est plus grand, "c'est moins" si le nombre mystère est plus petit, "bravo" si le nombre a été trouvé ou "un nombre entre 1 et 'max'" si jamais le nombre entré par une équipe est en dehors de l'intervalle. Ensuite l'autre équipe fait une proposition et le jeu continue jusqu'à ce que quelqu'un trouve le nombre. La première équipe à trouver le nombre mystère gagne.
