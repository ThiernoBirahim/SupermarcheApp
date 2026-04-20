#include "supermarche.h"
#include <stdexcept>

Supermarche::Supermarche() : compteurId(1), totalServis(0) {}

void Supermarche::initialiser(int nbCaisses) {
    caisses.clear();
    caisses.emplace_back(0, true); // caisse express numero 0
    for (int i = 1; i <= nbCaisses; i++) {
        caisses.emplace_back(i, false);
    }
}

void Supermarche::ouvrirCaisse(int numero) {
    for (auto& c : caisses)
        if (c.getNumero() == numero) { c.ouvrir(); return; }
    throw std::runtime_error("Caisse introuvable.");
}

void Supermarche::fermerCaisse(int numero) {
    for (auto& c : caisses) {
        if (c.getNumero() == numero) {
            if (c.isExpress())
                throw std::runtime_error("La caisse express ne peut pas etre fermee.");
            c.fermer();
            return;
        }
    }
    throw std::runtime_error("Caisse introuvable.");
}

void Supermarche::ajouterClient(const std::string& nom, int nbArticles) {
    Client client(compteurId++, nom, nbArticles);
    Caisse& cible = choisirCaisse(nbArticles);
    cible.ajouterClient(client);
}

void Supermarche::servirClient(int numeroCaisse) {
    for (auto& c : caisses) {
        if (c.getNumero() == numeroCaisse) {
            c.servirClient();
            totalServis++;
            return;
        }
    }
    throw std::runtime_error("Caisse introuvable.");
}

std::vector<Caisse>& Supermarche::getCaisses() { return caisses; }

int Supermarche::getTotalClientsServis() const { return totalServis; }

Caisse& Supermarche::choisirCaisse(int nbArticles) {
    if (nbArticles <= 10) {
        for (auto& c : caisses)
            if (c.isExpress()) return c;
    }
    Caisse* meilleure = nullptr;
    for (auto& c : caisses) {
        if (!c.isExpress() && c.estOuverte()) {
            if (!meilleure || c.getTailleFile() < meilleure->getTailleFile())
                meilleure = &c;
        }
    }
    if (!meilleure)
        throw std::runtime_error("Aucune caisse ordinaire ouverte disponible.");
    return *meilleure;
}