---
title: PCO - Étape 2 - Serveur de fichiers
author: Pierre Kohler, Jeremy Zerbib
papersize: a4
geometry: "left=2.5cm,right=2.5cm,top=3cm,bottom=3cm"
lang: fr-CH
date: \today
...

## Description des fonctionnalités du logiciel

À cette étape du laboratoire, les fonctionnalités du logiciel sont les suivantes : 
    - Traitement de *N* requêtes de façon *multi-thread*
    - Recyclage des *threads* et temporisation de ces derniers

## Choix d'implémentation

### ThreadPool

Le principe de cette classe réside dans la temporisation et le recyclages des *threads*, basé sur une taille maximale.  
Le but de cette classe est donc de donner un nombre maximal de *threads* pouvant être exécuté en même temps sur le serveur.
Ce nombre ne pourra pas être dépassé sous peine de mettre le serveur sous l'eau et de le surcharger au point qu'il ne puisse plus rien faire.
de le surcharger au point qu'il ne puisse plus rien faire.  

Le fait d'augmenter le nombre de *threads*, donc de requêtes, continuera à ralentir les temps de réponse pour tous les clients.
En revanche, l'implémentation de notre système garantie que le serveur ne pourra pas s'écrouler.  

Pour ce faire, nous avons simplement implémenté un constructeur, un destructeur, un signal permettant de si un *thread* est terminé et une méthode `start`.
Nous nous attarderons sur le destructeur et sur la méthode `start` car les deux autres implémentations sont triviales.  

#### Destructeur
Dans le destructeur de cette classe, nous parcourons chaque liste créée de façon à détruire chaque *thread* présent dans cette dernière.
Il est impératif de faire cette destruction car nous devons nous assurer qu'aucun *thread* ne continue à tourner pour éviter d'utiliser des ressources en vain.

#### `start`
Tout d'abord, nous nous assurons que le nombre de *threads* tournant ne soit pas supérieur au nombre maximal de *threads* ni que le nombre de *threads* disponible ne soit pas nul.
Si c'est le cas, nous demandons au *thread* d'attendre.  
Sinon, si la liste de disponibilité n'est pas vide, nous voulons créer une nouvelle requête qui sera mise dans la liste des *threads* occupés et on enlève un élément de la liste de *threads* disponible. 
Suite à cela, nous assignons un `Runnable` à cette dernière et la lançons.  
Si la liste de disponibilité est vide et que le nombre de *threads* tournant est inférieur au nombre de *threads* maximal, nous créons une nouvelle requête.
Nous connectons cette dernière au signal `hasFinished`, créé pour les besoins de cette classe, rajoutons ce *thread* dans la liste de *threads* occupés et lançons la requête.

### Runnable

Classe permettant d'abstraire la notion de *threads* pour les requêtes.  

Nous nous sommes contentés de donner les signatures des méthodes sans en donner la définition car les classes l'étendant devront le faire.

### RequestHandler

Cette classe étend `Runnable` de façon à pouvoir passer aux requêtes un `Runnable` plutôt qu'un *thread*.
Les méthodes abstraites de `Runnable` sont donc redéfinies dans cette classe avec le suffixe `override` en fin de déclaration de la méthode.


### RequestThread

Cette classe a été modifiée de façon à pouvoir lancer une instance de `Runnable` plutôt qu'un *thread* directement.
Cela était nécessaire car comme le `ThreadPool` gère lui-même ces *threads*, nous avions besoin "d'abstraire" la notion de requêtes *threadées*.  
Pour ce faire, nous avons rajouté une instance de `Runnable` dans le constructeur de la classe existante ainsi qu'un *setter* permettant de définir le `Runnable` à lancer dans la requête.

### filerserver

Cette classe a été modifiée de façon à ne plus utiliser la méthode `put` et utiliser `tryPut`.
Nous avons simplement remplacé l'appel à la méthode `put` par cela : 
```c+++
if(!requests->tryPut(req)) {
            pClient->sendTextMessage(Response(req, "Server overloaded, try later").toJson());
}
```  
Cela permet de notifier l'utilisateur que le serveur est en surcharge de travail et que plus rien ne peut être fait pour le moment.

## Tests effectués



