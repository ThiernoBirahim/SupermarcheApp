#pragma once
#include <queue>
#include <stdexcept>
#include "client.h"

class Caisse {
public:
    Caisse(int numero, bool estExpress = false);
    void ajouterClient(const Client& c);
    Client servirClient();
    bool estVide() const;
    int getTailleFile() const;
    int getTempsAttente() const;
    bool estOuverte() const;
    bool isExpress() const;
    int getNumero() const;
    void ouvrir();
    void fermer();

private:
    int numero;
    bool ouvert;
    bool express;
    std::queue<Client> file;
};