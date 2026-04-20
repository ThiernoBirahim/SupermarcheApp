#include "serveur.h"
#include "../lib/httplib.h"
#include "json_helper.h"
#include <iostream>

void Serveur::demarrer(Supermarche& sm) {
    httplib::Server srv;

    // GET /api/etat - retourne l'etat complet
    srv.Get("/api/etat", [&](const httplib::Request&, httplib::Response& res) {
        try {
            json j = supermarcheToJson(sm);
            res.set_header("Access-Control-Allow-Origin", "*");
            res.set_content(j.dump(), "application/json");
        } catch (const std::exception& e) {
            res.status = 500;
            res.set_content(json{{"erreur", e.what()}}.dump(), "application/json");
        }
    });

    // POST /api/client/ajouter
    srv.Post("/api/client/ajouter", [&](const httplib::Request& req, httplib::Response& res) {
        try {
            json body = json::parse(req.body);
            sm.ajouterClient(body["nom"], body["nbArticles"]);
            res.set_header("Access-Control-Allow-Origin", "*");
            res.set_content(supermarcheToJson(sm).dump(), "application/json");
        } catch (const std::exception& e) {
            res.status = 400;
            res.set_header("Access-Control-Allow-Origin", "*");
            res.set_content(json{{"erreur", e.what()}}.dump(), "application/json");
        }
    });

    // POST /api/caisse/ouvrir
    srv.Post("/api/caisse/ouvrir", [&](const httplib::Request& req, httplib::Response& res) {
        try {
            json body = json::parse(req.body);
            sm.ouvrirCaisse(body["numero"]);
            res.set_header("Access-Control-Allow-Origin", "*");
            res.set_content(supermarcheToJson(sm).dump(), "application/json");
        } catch (const std::exception& e) {
            res.status = 400;
            res.set_header("Access-Control-Allow-Origin", "*");
            res.set_content(json{{"erreur", e.what()}}.dump(), "application/json");
        }
    });

    // POST /api/caisse/fermer
    srv.Post("/api/caisse/fermer", [&](const httplib::Request& req, httplib::Response& res) {
        try {
            json body = json::parse(req.body);
            sm.fermerCaisse(body["numero"]);
            res.set_header("Access-Control-Allow-Origin", "*");
            res.set_content(supermarcheToJson(sm).dump(), "application/json");
        } catch (const std::exception& e) {
            res.status = 400;
            res.set_header("Access-Control-Allow-Origin", "*");
            res.set_content(json{{"erreur", e.what()}}.dump(), "application/json");
        }
    });

    // POST /api/caisse/servir
    srv.Post("/api/caisse/servir", [&](const httplib::Request& req, httplib::Response& res) {
        try {
            json body = json::parse(req.body);
            sm.servirClient(body["numero"]);
            res.set_header("Access-Control-Allow-Origin", "*");
            res.set_content(supermarcheToJson(sm).dump(), "application/json");
        } catch (const std::exception& e) {
            res.status = 400;
            res.set_header("Access-Control-Allow-Origin", "*");
            res.set_content(json{{"erreur", e.what()}}.dump(), "application/json");
        }
    });

    // GET /api/stats
    srv.Get("/api/stats", [&](const httplib::Request&, httplib::Response& res) {
        try {
            json j = {{"totalServis", sm.getTotalClientsServis()}};
            res.set_header("Access-Control-Allow-Origin", "*");
            res.set_content(j.dump(), "application/json");
        } catch (const std::exception& e) {
            res.status = 500;
            res.set_content(json{{"erreur", e.what()}}.dump(), "application/json");
        }
    });

    // Servir les fichiers web
    srv.set_mount_point("/", "./web");

    std::cout << "Serveur demarre : http://localhost:8080" << std::endl;
    srv.listen("0.0.0.0", 8080);
}