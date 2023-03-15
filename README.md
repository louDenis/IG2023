
# IG2023

Projet de rendu et d'animation. La partie rendu est sur la branche main, la partie animation est sur la branche anim.




## Installation

Les dépendances nécéssaires sont intégrées dans le git, en utilisant l'option --recursive. 
Une fois le dépot installé, il faut créer un nouveau dossier build (et supprimer celui déjà présent).

Il faut également ajouter les modèles utilisés par assimp. Pour cela, il faut créer un dossier "models" à l'emplacement "bin", et y ajouter :
- Pour la partie rendu, le modèle de l'oeuvre "la cathédrale" de Rodin, disponible ici : https://sketchfab.com/3d-models/la-cathedrale-d0ba1f143173484f87961fc50d46bdcf, et le nommer "la_cathedrale".
- Pour la partie animation, le fichier "Hands.glb", disponible dans le repertoire bin, ou téléchargeable ici : https://www.turbosquid.com/fr/3d-models/3d-cartoon-hand-model/409327#.

```bash
  git clone --recursive https://github.com/louDenis/IG2023
  cd IG2023/build
  cmake ..
  make
  cd ../bin && ./IG_project 
```
    
## OBJECTIFS DU PROJET

Cette année, j'ai pu voir à Paris, l'oeuvre "la cathédrale" de Rodin. Ayant beaucoup apprécié cette sculpture, je me suis dit qu'elle contituerait un bon objectif pour le projet IG. Le modèle étant disponible sur Internet, l'objectif étant donc de réaliser les tâches suivantes : 

- Repartir de 0 en OpenGL (car d'une année sur l'autre, j'avais oublié les fondamentaux en OpenGL) et créer un dépot portable sur Ubuntu.

- Charger le modèle de la cathédrale

- Appliquer et comparer différentes méthodes pour illuminer le modèle (Phong ou microfacettes)

- Appliquer le post processing HDR

- Appliquer le post processing Bloom

- Animer ce modèle via l'animation de squelette

Dans ce compte-rendu, je vais revenir sur les grandes étapes de développement ainsi que le niveau de réussite atteint pour chaque étape

## Partie Animation


En ce qui concerne la partie animation, mon objectif d'animer la main se révèle être un peu ambitieux pour quelqu'un ne sachant pas se servir de Blender et n'ayant eu qu'un seul cours à ce sujet. J'ai donc décidé d'abaisser la difficulté de mon objectif, en trouvant un modèle de main ayant déjà le squelette placé et les poids calculés.

Dans la partie animation, mes objectifs étaient :
- récupérer avec Assimp le modèle ainsi que son squelette
- afficher les poids (ceux précalculés par blender dans le modèle)
- calculer la hiérarchie du squelette et mettre en place une structure de données me permettant de stocker toutes ces informations
- afficher la position des différents bones
- calculer de nouveaux poids à partir des positions des os (avec la fonction la plus simple, la fonction de distance inverse)
- appliquer une transformation à un os en appliquant une rotation et calculer les nouvelles coordonnées des vertices

Parmis ces objectifs, j'ai pu récupérer le modèle avec Assimp en m'aidant du tutoriel learnOpenGL. J'ai ensuite pu afficher les poids sans difficultés (mise à part que Assimp ne parse pas correctement les fichiers ayant l'extension blender, l'extension choisie est importante). Je dirais que cette étape (en plus de trouver un modèle convenable m'a pris 2h)

Pour ce qui est de récupérer la hiérarchie, j'ai eu plus de difficultés, mais j'ai fini par y parvenir (youpi). Je ne suis pas la personne la plus à l'aise avec la recursivité, et tout les accès se font avec de la recursivité. J'ai quand même pu me débrouiller, et j'ai crée des fonctions dans model.h (pas très bien rangées d'ailleurs, je pense qu'un autre fichier dédié au squelette aurait été plus propre) pour remplir la structure "BoneInfo" pour qu'elle contienne l'indice du parent du Bone.

Je suis malheureusement restée bloquée pour récupérer la position globale d'un Bone, et je n'ai pas eu le temps de réussir à me débloquer. Je récupère des coordonnées, mais ce ne sont pas les bonnes et le temps commençait à me manquer pour continuer. J'en suis donc restée là pour la partie animation. J'ai tout de même pu apprendre beaucoup sur comment fonctionne l'animation de squelette, et je pense avoir gagné en aisance avec la recursivité. Je pense pouvoir progresser sur la manière dont je structure mes données.

NOTE IMPORTANTE : si vous testez la partie animation et que vous avez juste un fond rose, il faut regarder vers le bas avec la souris (ma caméra est mal positionnée)

## Partie Rendu

En ce qui concerne la partie rendu, je suis repartie de 0. J'ai donc passé une grande partie de mon temps (je dirais une dizaine d'heures) à ré apprendre les fondamentaux en OpenGL avant de pouvoir m'atteler au vif du sujet. Pour la partie rendu, j'ai suivi les cours learnOpenGL.

Une fois que toutes les bases ont été mises en place (classe Mesh, classe Camera, classe Shader), j'ai pu importer mon modèle de l'oeuvre avec Assimp. Cette partie ne m'a pas posé de difficultés en particulier, j'ai du y passer 2h environ. La partie m'ayant pris le plus de temps est la partie DES SAINTS FRAMEBUFFERS (j'y reviendrais). J'ai ensuite éclairé mon modèle et importé ses textures (l'éclairage a été fait avec le modèle de phong). 
A ce moment là, j'ai eu deux problèmes (qui après coup paraissent simplissime, mais étant donné que j'ai fait peu d'OpenGL dans ma vie, m'ont posé pas mal de soucis) :
- Certaines normales n'étaient pas dans le bon sens, donnant lieux à des résultats faux
- Je n'avais pas activé les options concernant le test de profondeur, et cela donnait également lieu à des résultats étrange. 

Cette partie à donc du me prendre environ 5h en comptant le temps passé à essayer de comprendre d'ou venaient les problèmes. J'ai également ajouté à mon modèle de Phong la notion d'atténuation de lumière.

Une fois mon modèle illuminé et texturé, je suis passé au vif du sujet : LES SAINTS FRAMEBUFFERS (dans le but de faire du hdr et du bloom)

Comprendre comment fonctionnent les framebuffers n'a pas été du gâteau. J'ai passé environ une journée sur le cours learnOpenGL à le lire et le relire en boucle. A force de persévérance, j'ai fini par pouvoir implémenter mon framebuffer (quelle joie), et j'ai pu utiliser mes connaissances pour réaliser l'hdr. Bien que l'HDR semble fonctionner, il y a un problème lors de la création des cubes que j'utilise pour faire un cube de lumière et le cube qui constitue la pièce dans laquelle se trouve le modèle. Les résultats peuvent donc être amélioré.

J'ai finalement implémenté le post processing bloom, mais il ne fonctionne pas comme je m'y attendais. Je n'ai malheureusement pas eu le temps (faut d'organisation) de bien explorer les résultats obtenus.


## Conclusion

Pour conclure, j'ai pu apprendre beaucoup de choses en OpenGL grâce à ce projet. Je me rends compte que je n'arrive pas du tout à estimer mon temps de développement d'une tâche, car, étant débutante en OpenGL, chaque erreur me prend un temps considérable à trouver. Je réalise tout de même que je développais de plus en plus efficacement au fur et à mesure du temps. 

Je n'ai pas pu remplir tout mes objectifs et explorer tout mes résultats en jouant avec les paramètres. J'aurai également bien aimé faire une interface utilisateur pour pouvoir jouer avec les différentes options. L'objectif ultime aurait été de fusionner les 2 parties (rendu et animation).

J'ai néanmoins pu apprendre beaucoup avec ce projet, qui m'a permit de mettre en application les connaissances vues en cours sur l'hdr, le bloom, et l'animation de squelette.
