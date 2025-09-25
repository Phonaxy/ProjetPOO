#include "../include/RessourceNumerique.h"

RessourceNumerique::RessourceNumerique(int id, const std::string& titre, const std::string& auteur, bool dispo,
                                       const std::string& type, double taille, const std::string& url)
        : Ressource(id, titre, auteur, dispo), type(type), taille(taille), url(url) {}

void RessourceNumerique::afficher() const {
    std::cout << "=== RESSOURCE NUMERIQUE ===\n";
    std::cout << "ID: " << id << "\n";
    std::cout << "Titre: " << titre << "\n";
    std::cout << "Auteur: " << auteur << "\n";
    std::cout << "Disponible: " << (dispo ? "Oui" : "Non") << "\n";
    std::cout << "Type: " << type << "\n";
    std::cout << "Taille: " << taille << " Mo\n";
    std::cout << "URL: " << url << "\n";
}

std::string RessourceNumerique::toFileString() const {
    return std::to_string(id) + ";RessourceNumerique;" + titre + ";" + auteur + ";" +
           (dispo ? "1" : "0") + ";" + type + ";" + std::to_string(taille) + ";" + url;
}