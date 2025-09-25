#include "../include/Livre.h"

Livre::Livre(int id, const std::string& titre, const std::string& auteur, bool dispo,
             int nbPages, const std::string& collection, const std::string& resume, int annee)
        : Ressource(id, titre, auteur, dispo), nbPages(nbPages), collection(collection), resume(resume), annee(annee) {}

void Livre::afficher() const {
    std::cout << "=== LIVRE ===\n";
    std::cout << "ID: " << id << "\n";
    std::cout << "Titre: " << titre << "\n";
    std::cout << "Auteur: " << auteur << "\n";
    std::cout << "Disponible: " << (dispo ? "Oui" : "Non") << "\n";
    std::cout << "Nombre de pages: " << nbPages << "\n";
    std::cout << "Collection: " << collection << "\n";
    std::cout << "Resume: " << resume << "\n";
    std::cout << "Annee: " << annee << "\n";
}

std::string Livre::toFileString() const {
    return std::to_string(id) + ";Livre;" + titre + ";" + auteur + ";" +
           (dispo ? "1" : "0") + ";" + std::to_string(nbPages) + ";" +
           collection + ";" + resume + ";" + std::to_string(annee);
}