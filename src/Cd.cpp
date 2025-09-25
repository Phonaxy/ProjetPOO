#include "../include/Cd.h"

CD::CD(int id, const std::string& titre, const std::string& auteur, bool dispo,
       const std::string& maisonProd, int nbPistes, const std::string& duree)
        : Ressource(id, titre, auteur, dispo), maisonProd(maisonProd), nbPistes(nbPistes), duree(duree) {}

void CD::afficher() const {
    std::cout << "=== CD ===\n";
    std::cout << "ID: " << id << "\n";
    std::cout << "Titre: " << titre << "\n";
    std::cout << "Auteur: " << auteur << "\n";
    std::cout << "Disponible: " << (dispo ? "Oui" : "Non") << "\n";
    std::cout << "Maison de production: " << maisonProd << "\n";
    std::cout << "Nombre de pistes: " << nbPistes << "\n";
    std::cout << "Duree: " << duree << "\n";
}

std::string CD::toFileString() const {
    return std::to_string(id) + ";CD;" + titre + ";" + auteur + ";" +
           (dispo ? "1" : "0") + ";" + maisonProd + ";" +
           std::to_string(nbPistes) + ";" + duree;
}