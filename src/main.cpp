#include <iostream>
#include "supermarche.h"

int main() {
    std::cout << "=== TEST PHASE 1 ===" << std::endl;

    // Test 1 : afficher 3 clients
    Client c1(1, "Alice", 12);
    Client c2(2, "Bob", 5);
    Client c3(3, "Carla", 20);
    std::cout << c1.toString();
    std::cout << c2.toString();
    std::cout << c3.toString();

    // Test 2 : ajouter 5 clients, en servir 2
    Caisse caisse(1);
    for (int i = 1; i <= 5; i++)
        caisse.ajouterClient(Client(i, "Client" + std::to_string(i), i * 2));
    caisse.servirClient();
    caisse.servirClient();
    std::cout << "Taille file apres 2 services : "
              << caisse.getTailleFile() << " (attendu : 3)" << std::endl;

    // Test 3 : fermer caisse non vide -> exception
    try {
        caisse.fermer();
        std::cout << "ERREUR : exception non levee !" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Exception correcte : " << e.what() << std::endl;
    }

    // Test 4 et 5 : Supermarche
    Supermarche sm;
    sm.initialiser(3);
    sm.ajouterClient("Diana", 5);    // -> express
    sm.ajouterClient("Eric", 15);    // -> ordinaire
    sm.ajouterClient("Fatou", 8);    // -> express
    sm.ajouterClient("Georges", 25); // -> ordinaire

    for (auto& c : sm.getCaisses()) {
        std::cout << "Caisse " << c.getNumero()
                  << (c.isExpress() ? " [EXPRESS]" : "")
                  << " : " << c.getTailleFile() << " client(s)"
                  << " | attente ~" << c.getTempsAttente() << "s"
                  << std::endl;
    }

    return 0;
}