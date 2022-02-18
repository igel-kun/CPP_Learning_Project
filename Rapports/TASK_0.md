# Se familiariser avec l'existant

## A- Exécution

> Allez dans le fichier `tower_sim.cpp` et recherchez la fonction responsable de gérer les inputs du programme.
Sur quelle touche faut-il appuyer pour ajouter un avion ?

Il faut appuyer sur la touche c pour ajouter un avion.

> Comment faire pour quitter le programme ?

Pour quitter le programme on peut appuyer sur les touches 'Q' et 'X'.

>A quoi sert la touche 'F' ?

La touche 'F' sert à mettre la fenêtre en plein écran.

>Ajoutez un avion à la simulation et attendez.
Que est le comportement de l'avion ?

Dans l'ordre :
- l'avion arrive dans la scène.
- il se pose sur la piste d'atterrissage.
- il prends des passagers.
- puis re-décolle et tourne en rond autour de l'aéroport. 

>Quelles informations s'affichent dans la console ?

Dans la console on affiche les actions de chaque avion. (il décolle, récupère des passagers ...)

>Ajoutez maintenant quatre avions d'un coup dans la simulation.
Que fait chacun des avions ?

Ils vont chacun leur tour attendre qu'ils puissent récupérer des passagers (seulement s'il y a de la place) puis ils vont partir vers leur déstination pour revenir et répéter le cycle.

## B- Analyse du code

>Listez les classes du programme à la racine du dossier src/.
Pour chacune d'entre elle, expliquez ce qu'elle représente et son rôle dans le programme.

| classe        | représentation |
| ------------- | -------------- |
| aircraft_type | représente les différents types d'avions, permets de stocker les informations propre à un avion |
|aircraft       | représente les à proprement parler un avion ainsi que ses actions | 
| airport_type  | représente les informations d'un aéroports |
| airport       | représente à proprement parler un aéroport |
| geometry      | représente les actions possible sur les géométrie du projet |
| main          | permet de lancer la simulation |
| runaway       | représente le point dans l'espace qui indique aux avions qu'ils se sont éloignés de l'aéroport |
| terminal      | représente les terminaux de l'aéroport, permets aux avions de récupérer des passagers |
| tower_sim     | gère toute la simulations ainsi que les inputs de l'utilisateur |
| tower         | représente les tours de controle |
| waypoint      | représente un point sur le chemin d'un avion |

>Pour les classes `Tower`, `Aircaft`, `Airport` et `Terminal`, listez leurs fonctions-membre publiques et expliquez précisément à quoi elles servent.
Réalisez ensuite un schéma présentant comment ces différentes classes intéragissent ensemble.

### Tower :

| fonction        | explication    |
| --------------- | -------------- |
| Tower() | c'est le constructor |
| get_instructions() | gère les actions que doit faire un avion selon s'il estsur le terminal de la ou non |
| arrived_at_terminal() | enclenche le service d'un avion une fois qu'il est arrivé au terminal |

### Aircraft :

| fonction        | explication    |
| --------------- | -------------- |
| Aircraft() | c'est le constructor |
| get_flight_num() | retourne le numéro de l'avion |
| distance_to() | retourne la distance entre l'avion et un point donné |
| display() | affiche la texture de l'avion |
| move() | déplace l'avion entre les waypoints |

### Airport :

| fonction        | explication    |
| --------------- | -------------- |
| Airport() | c'est le constructor |
| get_tower() | retourne la tour de contrôle |
| display() | affiche la texture de l'aéroport |
| move() | déplace les terminaux |

### Terminal :

| fonction        | explication    |
| --------------- | -------------- |
| Terminal() | c'est le constructor |
| in_use() | retourne si l'avion courant est null ou non |
| is_servicing() | retourne s'il y a un service en cours |
| assign_craft() | assigne un avion au terminal |
| start_service() | commence le service seulement si l'avion est en suffisament proche |
| finish_service() | désassigne l'avion une fois le service fini |
| move() | change le terminal si un avion y est assigné et qu'un service est en cours |

>Quelles classes et fonctions sont impliquées dans la génération du chemin d'un avion ?
Quel conteneur de la librairie standard a été choisi pour représenter le chemin ?
Expliquez les intérêts de ce choix.