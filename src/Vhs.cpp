#include "../include/Vhs.h"

VHS::VHS(int id, const std::string& titre, const std::string& auteur, bool dispo,
         const std::string& maisonProd, const std::string& duree)
        : Ressource(id, titre, auteur, dispo), maisonProd(maisonProd), duree(duree) {}

void VHS::afficher() const {
    std::cout << "=== VHS ===\n";
    std::cout << "ID: " << id << "\n";
    std::cout << "Titre: " << titre << "\n";
    std::cout << "Auteur: " << auteur << "\n";
    std::cout << "Disponible: " << (dispo ? "Oui" : "Non") << "\n";
    std::cout << "Maison de production: " << maisonProd << "\n";
    std::cout << "Duree: " << duree << "\n";
}

std::string VHS::toFileString() const {
    return std::to_string(id) + ";VHS;" + titre + ";" + auteur + ";" +
           (dispo ? "1" : "0") + ";" + maisonProd + ";" + duree;
}