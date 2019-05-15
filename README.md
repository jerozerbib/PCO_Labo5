---
title: PCO - Étape 1 - Serveur de fichiers 
author: Pierre Kohler, Jeremy Zerbib
papersize: a4
geometry: "left=2.5cm,right=2.5cm,top=3cm,bottom=3cm"
lang: fr-CH
date: \today
...

## Description des fonctionnalités du logiciel

À cette étape du laboratoire, les fonctionnalités du logiciel sont les suivantes : 
    - Traitement de *N* requêtes concurrentes de façon *multi-thread*.

## Choix d'implémentation

### MessageBuffer
`MessageBuffer` est une classe spécifique de `AbstractBuffer` permettant de créer un tampon stockant les `Responses` et les `Requests`.
Il s'agit d'une classe abstraite, ce qui permet de rajouter n'importe quel type de message dans le tampon.
Cette classe comporte les méthodes `put` et `get`, qui permettent respectivement de rajouter et de lire des messages dans le tampon, et dont les accès concurrents sont contrôlés par un moniteur de Mesa.

### RequestDispatcherThread
Cette classe est une quasi copie de la classe `ResponseDispatcherThread`, qui permet de gérer l'envoi des requêtes dans le système de traitement de requêtes.
Dans notre implémentation, une fois la requête obtenue, un *thread* est exécuté pour la traiter.  
Ensuite, nous utilisons un *QPointer* pour stocker une référence vers le `RequestHandler` de façon à garantir la libération de ses ressources.
Finalement, quand le traitement des requêtes est abouti, nous nous envoyons l'information de la fin du traitement de façon à pouvoir nettoyer efficacement le *TCB* grâce à la ligne ci-dessous.  
`connect(reqHandler, &RequestHandler::finished, reqHandler, &QObject::deleteLater);`  
Nous connectons la fonction `finished` vers `deleteLater`, deux fonctions fournies par *Qt*.
La première est appelée lorsque le *thread* a fini son exécution, et la seconde nettoie le *TCB*.

### RequestHandler (héritant de thread)
De façon à *threader* le `RequestHandler` existant, nous avons fait hériter la classe de *QThread*.
Nous avons donc rajouter la fonction `run` pour respecter l'héritage.
Dans cette méthode, nous faisons simplement un appel vers la fonction `handle` existante, pour récupérer la réponse et enfin l'insérer dans le `MessageBuffer` de réponses.

## Tests effectués

### Comparez la performance de cette version concurrente avec celle de la version de base. Constatez vous une amélioration ?

Nous obtenions entre 3 minutes et 10 secondes et 3 minutes et 30 secondes lors de requêtes avec la version de base (en séquence) contre 40/45 secondes, suivant le contexte du système lors des tests, (un thread par requête). 

### Que se passe t il lorsqu'on lance un nombre de requêtes très important (par ex. 10’000), et comment l’expliquez vous ?
L'erreur survient :  `GLib-ERROR **: 09:26:04.617: Creating pipes for GWakeup: Too many open files`  
En effet, comme un nouveau thread s'occupera de chaque requête, le fichier sera ouvert trop de fois simultanément et fera donc effondrer le système. 

### Comment pourrait on protéger le serveur de cet effet néfaste ?
Il suffirait de limiter le nombre de requêtes exécutées simultanément, et donc le nombre de threads vivants en même temps.

