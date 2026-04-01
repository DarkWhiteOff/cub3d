# cub3D - My First RayCaster
This project has been created as part of the 42 curriculum by [Telvin/tzizi and Ziggy/zamgar].

## Description
cub3D est un moteur de rendu graphique 3D utilisant la technique du Raycasting. Inspiré par le mythique Wolfenstein 3D (1992), ce projet a pour but de créer une vue dynamique et subjective à l'intérieur d'un labyrinthe.

Le moteur calcule la perspective en projetant des rayons à travers une carte 2D pour simuler un environnement 3D en temps réel, le tout développé en C avec la bibliothèque graphique miniLibX.

## Caractéristiques principales
- Rendu fluide de l'environnement en 3D.
- Gestion des collisions.
- Gestion des textures différentes selon l'orientation des murs (Nord, Sud, Est, Ouest).
- Couleurs personnalisables pour le sol et le plafond.
- Déplacements fluides (W, A, S, D) et rotation de la caméra.
- Parsing complet de fichiers de configuration de scène (.cub).
### Bonus
- Minimap.
- Rotation de la caméra avec la souris.

## Instructions
### Compilation mandatory 
```bash
make
```
### Compilation bonus 
```bash
make bonus
```
### Exécution
Le programme prend en argument un fichier de description de scène avec l'extension **.cub**
```bash
./cub3D maps/good/mandatory/map0.cub
./cub3D_bonus maps/good/bonus/cub3d.cub
```
## Commandes
| Touches | Action |
|:---------:|:-------------:|
| W, A, S, D | Se déplacer | 
| Flèches Gauche/Droite / Souris (bonus) | Faire pivoter la vue |
| Esc / Croix | Fermer le programme proprement |
