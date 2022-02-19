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

Il y a :

- la classe Aircraft : 
    - arrive_at_terminal()
    - add_waypoint()
    - operate_landing_gear()

- la classe waypoint

- la classe tower :
    - get_circle()
    - get_instructions()

>Quel conteneur de la librairie standard a été choisi pour représenter le chemin ?
Expliquez les intérêts de ce choix.

Le conteneur choisi est std::deque, comme l'avion va se déplacer entre plusieurs points différents, utiliser une deque plutôt qu'un vector est plus intéréssant car la deque permets un ajout et une suppression plus efficace, donc on va pouvoir ajouter et retirer des points sur la trajectoire de l'avion plus facilement.

## C- Bidouillons !

> Déterminez à quel endroit du code sont définies les vitesses maximales et accélération de chaque avion.

Les vitesses maximales et accélération de chaque avion sont définis dans aircraft_types.hpp.

> Le Concorde est censé pouvoir voler plus vite que les autres avions.
Modifiez le programme pour tenir compte de cela.

```cpp
aircraft_types[2] = new AircraftType { /*.02f*/.05f,/*.05f*/ .08f, .02f, MediaPath { "concorde_af.png" } };
```

> Identifiez quelle variable contrôle le framerate de la simulation.

La variable controlant le framerate est la variable GL::ticks_per_sec dans opengl_interface.hpp.

> Ajoutez deux nouveaux inputs au programme permettant d'augmenter ou de diminuer cette valeur.

```cpp
GL::keystrokes.emplace('*', []() { GL::ticks_per_sec = std::min(GL::ticks_per_sec + 1u, 200u); });
GL::keystrokes.emplace('/', []() { GL::ticks_per_sec = std::max(GL::ticks_per_sec - 1u, 1u); });
```

ici il s'agit de la version final, on fait un min pour l'augmentation du framerate pour éviter de trop augmenter le framerate (la valeur 200u est complètement arbitraire), de plus on fait un max pour la réduction du framerate pour éviter de passer à 0 et faire crasher l'application.

> Essayez maintenant de mettre en pause le programme en manipulant ce framerate. Que se passe-t-il ?

Le programme crash.

> Ajoutez une nouvelle fonctionnalité au programme pour mettre le programme en pause, et qui ne passe pas par le framerate.

On va d'abord créer une nouvelle variable global dans opengl_interface.hpp nommé is_paused initialiser à false. puis on va modifier la fonction timer pour qu'elle prenne en compte la variable, ce qui nous donnes :

```cpp
void timer(const int step)
{
    if (!is_paused)
    {
        for (auto& item : move_queue)
        {
            item->move();
        }
        glutPostRedisplay();
    }
    glutTimerFunc(1000u / ticks_per_sec, timer, step + 1);
}
```

et dans tower_sim.cpp on vas ajouter un nouvel input qui va inverser la variable is_paused :

```cpp
GL::keystrokes.emplace('p', []() { GL::is_paused = !GL::is_paused; });
```

> Identifiez quelle variable contrôle le temps de débarquement des avions et doublez-le.

La variable controlant le temps de débarquement des avions est la variable SERVICE_CYCLES dans config.hpp qui était à 20u et que l'on passe donc à 40u.

> Lorsqu'un avion a décollé, il réattérit peu de temps après. Faites en sorte qu'à la place, il soit retiré du programme.

