# SAE 1.01 - RMAN Studio


## Introduction
Ce programme C++ simule un tournoi.


## Sommaire
1. ### Message à l'attention de l'examinateur
2. ### L'accès global
	- Constantes
	- Fonctions
3. ### Le tournoi
	- Structs
	- Création des joueurs
	- Déroulement de la création des équipes
	- Matchmaking
	- Choix des jeux
4. ### Les jeux
	- Memory
	- Morpion
	- Puissance 4
	- Echecs
	- Pierre feuille ciseaux
	- Juste prix
        
## 1. Message à l'attention de l'examinateur

Bonjour/soir, voici un court tutoriel sur la procédure à suivre pour faire fonctionner le programme.  
Tout d'abord, il faut être muni du projet (je suppose que c'est déjà le cas si vous lisez ce readme :D), par la suite il est nécessaire de lancer Qt Creator puis d'ouvrir le projet.  
Ensuite, allez dans `Projects > Run > Command line arguements:`, puis dans la zone de texte à côté, il faut écrire le chemin relatif jusqu'au fichier d'entree (soit `input.txt`)
Pour la prochaine étape, c'est très simple il suffit de compiler (sans exécuter) le projet. Puis, il vous suffit de déplacer les fichier `input.txt` et `oracle.txt` dans le build qui a été conçu lors de la compilation.  
Si une erreur persiste, contactez R. Clement par email à `romain.clement.1@etu.univ-amu.fr`.


## 2. L'accès global

Certaines *constantes / fonctions* peuvent être nécessaire dans plusieurs programmes différents, il est donc préférable de les écrires une seule fois dans un fichier global. Cela permet de modifier leur *valeur / fonctionnement* dans tout le projet en une seule fois plutôt que de chercher dans tous les fichiers où elle est utilisée.  
Ces *constantes / fonctions* sont déclarées dans le fichier `global.h` et définies dans le fichier `global.cxx`. Pour les importer dans n'importe quel programme du projet il suffit d'ajouter la ligne :
```cpp
#include "./global.h"
```
On notera que le chemin est relatif, il faut donc adapter le chemin à l'emplacement du fichier où l'instruction est écrite.

### 2.1 Constantes
L'appel des constantes se fait avec l'instruction :
```cpp
global_const::nom_constante
```
Pour simplifier cela, il est aussi possible d'utiliser un espace de nom :
```cpp
using namespace global_const;
//dans ce cas, pas besoin de mettre "global_const::" devant le nom de la variable
```
#### 2.1.1 WAIT_MSG
Contient le message à afficher lorsque le programme attend la validation de l'utilisateur pour continuer.
```cpp
const string WAIT_MSG;
```
#### 2.1.2 INPUT_ERR_MSG
Contient le message à afficher lorsque le programme l'utilisateur fait une erreur dans sa saisie (mauvais type, en dehors des bornes...)
```cpp
const string INPUT_ERR_MSG;
```
#### 2.1.3 MIN_TEAMS
Contient le nombre minimum d'équipes que l'utilisateur choisit au début du tournoi.
```cpp
const unsigned MIN_TEAMS;
```
#### 2.1.4 MAX_TEAMS
Contient le nombre maximum d'équipes que l'utilisateur choisit au début du tournoi.
```cpp
const unsigned MAX_TEAMS;
```
#### 2.1.5 GAMES_NAME
Contient le nom de tous les jeux.
```cpp
const vector<string> GAMES_NAME;
```
#### 2.1.7 NB_GAMES
Contient le nombre de jeux total, sa valeur est la longueur de `GAMES_NAME` (2.1.5)
```cpp
const unsigned NB_GAMES;
```

### 2.2 Fonctions
L'appel des fonctions se fait avec la commande :
```cpp
global_func::nom_fonction()
```
Pour simplifier cela, il est aussi possible d'utiliser un espace de nom :
```cpp
using namespace global_func;
//dans ce cas, pas besoin de mettre "global_func::" devant le nom de la fonction
```

#### 2.2.1 ask4UInput
Affiche l'invite passée en paramètre si <putInOutput> est vraie (ofs) et renvoie la saisie de l'utilisateur (ifs).
```cpp
string ask4UInput(const string & invite="", const bool & putInOutput=true);
```
#### 2.2.2 pressEnter
Attend que l'utilisateur (ifs) appuye sur la touche Enter (utilise `WAIT_MSG` (2.1.1) comme message d'invite)
```cpp
void pressEnter();
```
#### 2.2.3 randomSort
Mélange une liste aléatoirement avec des permutations
```cpp
template <typename T>
void randomSort(vector<T> & v);
```
#### 2.2.4 leftAlign
Complète une chaîne de caractères par `nb_char-txt.size()` espaces à droite (utile pour `cuteLilBoard()` (2.2.7)
```cpp
string leftAlign(const string & txt, const unsigned & nb_char);
```
#### 2.2.5 rightAlign
Complète une chaîne de caractères par `nb_char-txt.size()` espaces à gauche (utile pour `cuteLilBoard()` (2.2.7)
```cpp
string rightAlign(const string & txt, const unsigned & nb_char);
```
#### 2.2.6 centerAlign
Complète une chaîne de caractères par `nb_char-txt.size()` espaces répartis à gauche et à droite (utile pour `cuteLilBoard()` (2.2.7)
```cpp
string centerAlign(const string & txt, const unsigned & nb_char);
```
#### 2.2.7 cuteLilBoard
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
`align` correspond à l'alignement dans chaque colonne (voir 2.2.4/2.2.5/2.2.6). Si le paramètre n'est pas renseigné, les colonnes seront centrées par défaut. Exemple : `{'r', 'l', 'c'}` fera un tableau comme celui-ci :
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


## 3. Le tournoi

### 3.1 Création des joueurs
Au début du tournoi, le nom de chaque joueur est récupéré depuis ifs. Par la suite, on crée une liste qui contient l'intégralité des joueurs grace à la structure de donnée définie par :
```cpp
struct player {
    string last_name;	// Nom de famille
    string first_name;	// Prénom
};
```

### 3.2 Création des équipes
Lors de la création des équipes, l'utilisateur renseigne d'abord le nombre d'équipes qui participent au tournoi, ainsi le programme éjecte aléatoirement des joueurs qui sont de trop, si le nombre de joueurs n'est pas un multiple du nombre d'équipes.  
Ensuite, l'utilisateur saisi au fur et à mesure le nom des équipes tout en voyant quel joueur a été placé dans quel équipe (les joueurs sont regroupés aléatoirement). Pour ce faire, on utilise la structure de donnée d'équipe qui prend la forme :
```cpp
struct team {
    string name;		    // Nom de l'équipe
    unsigned points;		// Nombre de points
    vector<player> players;	// Tableau des joueurs de l'équipe
};
```
(NB: les équipes sont stockées dans un tableau de type `vector<team>`)

### 3.3 Matchmaking
La partie du matchmaking est assez simple puisqu'il s'agit simplement d'une fonction qui permet de regrouper les équipes 2 par 2 à partir de la liste préalablement triée par nombre de points des équipes. Cette fonction transforme le tableau d'équipes de type `vector<team>` en tableau de tableaux d'équipes de type `vector<vector<team>>`, ainsi chaque tableau du tableau a pour longueur 2  
(NB: si on a un nombre impaire d'équipes, le dernier tableau du tableau a une longueur de 1)

### 3.4 Rencontres des équipes
Pour lancer une rencontre, il faut au préalable avoir récupéré un tableau de tableau d'équipes (avec la fonction de `matchmaking` (3.3)). Ainsi, quelque soit le jeu qui est lancé, on appelle la fonction correspondante qui prend pour paramètre le nom des deux équipes qui participent à la rencontre.  
Puis, il suffit de réitérer l'appel de la fonction pour chaque tableau du tableau de matchmaking pour faire en sorte que chaque équipe joue sa rencontre. On notera que si la dernière rencontre est une équipe seule, elle est exmptée et gagne automatiquement 1 point.  
La dernière étape est d'ajouter les points à l'équipe gagnante de chaque rencontre (réponse de la fonction du mini-jeu) de la manière suivante, si une équipe gagne la rencontre, elle marque 2 points, si elle perd elle n'en marque aucun et si les équipes dont égalité dans la rencontre (possible dans certains cas tels que le morpion, le puissance 4 ou encore les échecs) les deux équipes marquent 1 point chacune.



## 4. Les jeux
Chaque programme renvoie soit 0 pour annoncer la victoire de l'équipe désignée comme équipe 1, 1 pour annoncer la victoire de l'équipe désignée en équipe 2 et 2 si jamais il y a une égalité.

### 4.1 Memory
Au Memory, le but du jeu est de retourner le plus de paire possible avant la fin de la partie. La partie se fini donc quand plus aucune carte n'est retournée sachant qu'on est obligée d'en trouver deux identiques pour qu'elles le restent. Lorsque une équipe retourne correctement deux carte d'une même paire, elle peuvent retenter sa chance pour en trouver une autre. Au final c'est l'équipe qui en a trouvé le plus qui gagne la partie.

### 4.2 Morpion
Le principe du morpion est de réussir à aligner trois pions horizontalement, verticalement ou même en diagonale dans une grille de jeu de 3x3 avant son adversaire pour gagner la partie.
Pour placer un pion, il suffit de suivre les instructions données par le terminal, c'est à dire entrer le numéro de la ligne puis le numéro de la colonne de la case où vous souhaitez placer votre pion.

### 4.3 Puissance 4
Le jeu du puissance 4 suis les mêmes règles que le jeu de base, l'équipe gagne lorsqu'elle aligne 4 pions dans la grille.

### 4.4 Echecs
Le mini-jeu d'échec reprend les règles basiques du jeu d'échec.  
Le fonctionnement du jeu se fait au travers de plusieurs étapes qui sont les suivantes :
	- récuperer le coup de l'utilisateur
	- vérifier que :
	    - la piece que l'on veut bouger existe
	    - le mouvement est légal (on n'essaye pas de déplacer une tour en diagonale ou on ne se met pas soit même en échec)
	- déplacer la piece
	- si on a un échec et mat
	    - on renvoie le gagnant de la partie
	- sinon si on a un match nul (pat ou insuffisance de matériel)
	    - on revoie 2 (égalité)
	- si aucun de ses cas n'est vrai
	    - on recommence au premier tiret en changeant la couleur de l'équipe qui joue

### 4.5 Pierre feuille ciseaux
Le but du jeu est simple. Il faut essayer de gagner en choississant l'une des possibilités qui sont la pierre, qui gagne contre les ciseaux, la feuille qui gagne contre la pierre et les ciseaux qui gagnent contre la feuille. La première équipe à arriver au score max définit au début de la partie gagne.  
Le programme fonctionne de sorte à ce que chaque combinaisons possibles soit prises en compte (victoire pour un des deux, égalité ou réessayer si jamais le choix n'est pas dans les choix proposés).

### 4.6 Juste prix
Le but de ce jeu est de trouver le nombre généré aléatoirement entre 1 et un maximum choisis avant son adversaire.  
L'équipe qui commence est sélectionné de manière aléatoire et commence la partie. Le programme renverra "c'est plus" si le nombre mystère est plus grand, "c'est moins" si le nombre mystère est plus petit, "bravo" si le nombre a été trouvé ou "un nombre entre 1 et 'max'" si jamais le nombre entré par une équipe est en dehors de l'intervalle. Ensuite l'autre équipe fait une proposition et le jeu continue jusqu'à ce que quelqu'un trouve le nombre. La première équipe à trouver le nombre mystère gagne.
