# PROJ731 - Répartiteur de charge

Par RISS Ryan et NGOR Calvin

## Lors du lancement de programme on peut soit choisir de lancer :

- Un serveur (s)
- Un aiguilleur (a)
- Un client (c)

L'ordre est à respecter pour ne pas avoir de problèmes (les différentes connexions par les différents port sont codées, tout est en localhost).

Ou bien un test de connexion aiguilleur-aiguilleur

## Le code 

Le projet a été codé entièrement en C++ et utilise la libraire SFML pour la partie réseau.

- Classe TcpObject : classe "abstraite" ayant des méthodes de réception et d'envoie de données
- Classe ServerObject : classe abstraite hérité de TcpObject ayant des méthodes permettant d'accepter des connexions et de bloquer sur un groupe de socket (utile lorsqu'on communique avec plusieurs clients/serveurs).
- Classe Client : hérité de TcpObject, méthodes pour le client
- Classe Aiguilleur : hérité de ServerObject, méthodes pour l'aiguilleur
- Classe Server : hérité de ServerObject, méthodes pour le serveur

## Ce qui aurait pu être fait ou amélioré

- Faire en sorte que la réponse ne passe pas par le repartiteur de charge mais directement au client
- Tester l'écriture de fichier (notamment concurrente)
- Ajout et retrait dynamique de serveurs
- Tester avec une data commune et non une copie par serveur