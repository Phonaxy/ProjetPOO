#include "../include/Dvd.h"

DVD::DVD(int id, const std::string& titre, const std::string& auteur, bool dispo,
         const std::string& maisonProd, const std::string& duree, int nbChapitres)
        : Ressource(id, titre, auteur, dispo), maisonProd(maisonProd), duree(duree), nbChapitres(nbChapitres) {}

void DVD::afficher() const {
    std::cout << "=== DVD ===\n";
    std::cout << "ID: " << id << "\n";
    std::cout << "Titre: " << titre << "\n";
    std::cout << "Auteur: " << auteur << "\n";
    std::cout << "Disponible: " << (dispo ? "Oui" : "Non") << "\n";
    std::cout << "Maison de production: " << maisonProd << "\n";
    std::cout << "Duree: " << duree << "\n";
    std::cout << "Nombre de chapitres: " << nbChapitres << "\n";
}

std::string DVD::toFileString() const {
    return std::to_string(id) + ";DVD;" + titre + ";" + auteur + ";" +
           (dispo ? "1" : "0") + ";" + maisonProd + ";" + duree + ";" +
           std::to_string(nbChapitres);
}