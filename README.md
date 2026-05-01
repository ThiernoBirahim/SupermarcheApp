# Système de Gestion de Caisse de Supermarché

Application complète de gestion de caisses développée en C++ (serveur) 
et JavaScript (interface navigateur).

## Membres du groupe

- Thierno Birahim | Licence 2 Informatique | Groupe ISI

## Prérequis

- g++ >= 8.0
- make
- Git
- Navigateur Chrome ou Firefox

## Bibliothèques utilisées

- [cpp-httplib](https://github.com/yhirose/cpp-httplib) — serveur HTTP
- [nlohmann/json](https://github.com/nlohmann/json) — manipulation JSON

## Installation

1. Cloner le dépôt :
git clone https://github.com/ThiernoBirahim/SupermarcheApp.git
cd SupermarcheApp

2. Compiler le projet :
make

## Lancement

1. Lancer le serveur :
make run

2. Ouvrir dans le navigateur :
http://localhost:8080

## Fonctionnalités

- Gestion de 3 caisses ordinaires + 1 caisse express
- Ajout de clients avec orientation automatique
- Clients avec 10 articles ou moins → caisse express
- Clients avec plus de 10 articles → caisse la moins chargée
- Servir, ouvrir et fermer les caisses
- Statistiques en temps réel
- Alerte visuelle si file dépasse 5 clients
- Rafraîchissement automatique toutes les 3 secondes

## Routes API

| Méthode | Route | Description |
|---------|-------|-------------|
| GET | /api/etat | État complet des caisses |
| POST | /api/client/ajouter | Ajouter un client |
| POST | /api/caisse/ouvrir | Ouvrir une caisse |
| POST | /api/caisse/fermer | Fermer une caisse |
| POST | /api/caisse/servir | Servir le premier client |
| GET | /api/stats | Statistiques globales |

## Structure du projet

SupermarcheApp/
├── lib/
│   ├── httplib.h
│   └── json.hpp
├── src/
│   ├── client.h / client.cpp
│   ├── caisse.h / caisse.cpp
│   ├── supermarche.h / supermarche.cpp
│   ├── serveur.h / serveur.cpp
│   ├── json_helper.h
│   └── main.cpp
├── web/
│   ├── index.html
│   ├── style.css
│   └── app.js
├── Makefile
└── README.md