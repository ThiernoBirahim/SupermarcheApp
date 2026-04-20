#pragma once
#include "../lib/json.hpp"
#include "caisse.h"
#include "supermarche.h"

using json = nlohmann::json;

inline json caisseToJson(const Caisse& c) {
    return {
        {"numero",      c.getNumero()},
        {"ouverte",     c.estOuverte()},
        {"express",     c.isExpress()},
        {"nbClients",   c.getTailleFile()},
        {"tempsAttente",c.getTempsAttente()}
    };
}

inline json supermarcheToJson(Supermarche& s) {
    json tableau = json::array();
    for (auto& c : s.getCaisses())
        tableau.push_back(caisseToJson(c));
    return {
        {"caisses",      tableau},
        {"totalServis",  s.getTotalClientsServis()}
    };
}