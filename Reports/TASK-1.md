# Gestion mémoire

## Analyse de la gestion des avions

> La création des avions est aujourd'hui gérée par les fonctions `TowerSimulation::create_aircraft` et `TowerSimulation::create_random_aircraft`.
Chaque avion créé est ensuite placé dans les files `GL::display_queue` et `GL::move_queue`.

> Si à un moment quelconque du programme, vous souhaitiez accéder à l'avion ayant le numéro de vol "AF1250", que devriez-vous faire ?

Comme chaque avion créé sont placés dans la file `GL::display_queue` et que cette dernière est static et public, on pourrait facillement accéder à l'avion voulu en regardant les numéro de vol de chacun grâce à la fonction `get_flight_num()`, mais comme il s'agit d'un vecteur de Displayable, il faudrait caster dynamiquement pour savoir si c'est des avions ou non. 

## Objectif 1 - Référencement des avions

### A - Choisir l'architecture

> Pour trouver un avion particulier dans le programme, ce serait pratique d'avoir une classe qui référence tous les avions et qui peut donc nous renvoyer celui qui nous intéresse.

> Vous avez 2 choix possibles :
- créer une nouvelle classe, `AircraftManager`, qui assumera ce rôle,
- donner ce rôle à une classe existante.

> Réfléchissez aux pour et contre de chacune de ces options.

### Nouvelle classe

| avantages | inconvénient |
| --------- | ------------ |
| respect du *Single Responsibility Principle* | implémentation plus compliqué |
| meilleur controle | |

### donner ce rôle à une classe existante

| avantages | inconvénient |
| --------- | ------------ |
| implémentation plus rapide | non respect du *Single Responsibility Principle* |
| | classe plus lourde |

### B - Déterminer le propriétaire de chaque avion

> 1. Qui est responsable de détruire les avions du programme ?

On détruit les avions dans la fonction `timer()` de la classe `opengl_interface`.

> 2. Quelles autres structures contiennent une référence sur un avion au moment où il doit être détruit ?

Au moment ou on doit détruire l'avion, ce dernier est référencé dans la map `AircraftToTerminal` de la classe tower. (bien qu'on pense à l'en retirer à ce moment précis).

> 3. Comment fait-on pour supprimer la référence sur un avion qui va être détruit dans ces structures ?

> 4. Pourquoi n'est-il pas très judicieux d'essayer d'appliquer la même chose pour votre `AircraftManager` ?