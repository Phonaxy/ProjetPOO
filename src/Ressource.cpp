#include "../include/Ressource.h"


Ressource::Ressource(int id, const std::string& titre, const std::string& auteur, bool dispo)
        : id(id), titre(titre), auteur(auteur), dispo(dispo) {}

void Ressource::reserver() {
    if (dispo) {
        dispo = false;
        std::cout << "Ressource reservee.\n";
    } else {
        std::cout << "Ressource non disponible.\n";
    }
}

void Ressource::emprunter() {
    if (dispo) {
        dispo = false;
        std::cout << "Ressource empruntee.\n";
    } else {
        std::cout << "Ressource non disponible.\n";
    }
}

void Ressource::rendre() {
    dispo = true;
    std::cout << "Ressource rendue.\n";
}

int Ressource::getId() const { return id; }
const std::string& Ressource::getTitre() const { return titre; }
const std::string& Ressource::getAuteur() const { return auteur; }
bool Ressource::estDisponible() const { return dispo; }
