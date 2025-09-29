#include <iostream>
#include <algorithm>
#include "../include/Utilisateur.h"

// Mot de passe administrateur par défaut
const std::string Administrateur::MOT_DE_PASSE_ADMIN = "admin123";

Utilisateur::Utilisateur(const std::string& nom, TypeUtilisateur type)
        : nom(nom), type(type) {}

const std::string& Utilisateur::getNom() const {
    return nom;
}

TypeUtilisateur Utilisateur::getType() const {
    return type;
}

const std::vector<Droit>& Utilisateur::getDroits() const {
    return droits;
}

void Utilisateur::ajouterDroit(Droit droit) {
    // Éviter les doublons
    if (std::find(droits.begin(), droits.end(), droit) == droits.end()) {
        droits.push_back(droit);
    }
}

std::string Utilisateur::droitToString(Droit droit) const {
    switch (droit) {
        case Droit::LIRE: return "Lecture";
        case Droit::AJOUTER: return "Ajout";
        case Droit::MODIFIER: return "Modification";
        case Droit::SUPPRIMER: return "Suppression";
        case Droit::GERER_FICHIERS: return "Gestion fichiers";
        case Droit::RELOAD: return "Rechargement";
        default: return "Inconnu";
    }
}

// ==================== Classe Client ====================
Client::Client(const std::string& nom)
        : Utilisateur(nom, TypeUtilisateur::CLIENT) {
    // Les clients ont des droits limités
    ajouterDroit(Droit::LIRE);
    ajouterDroit(Droit::RELOAD);
}

bool Client::peutExecuter(Droit droit) const {
    return std::find(droits.begin(), droits.end(), droit) != droits.end();
}

bool Client::estAdministrateur() const {
    return false;
}

void Client::afficherDroits() const {
    std::cout << "=== DROITS CLIENT ===\n";
    std::cout << "Type d'utilisateur: Client\n";
    std::cout << "Droits accordes:\n";
    for (const auto& droit : droits) {
        std::cout << "- " << droitToString(droit) << "\n";
    }
    std::cout << "\nFonctionnalites disponibles:\n";
    std::cout << "- Lister les ressources\n";
    std::cout << "- Rechercher des ressources\n";
    std::cout << "- Afficher les details d'une ressource\n";
    std::cout << "- Recharger les donnees\n";
}

// ==================== Classe Administrateur ====================
Administrateur::Administrateur(const std::string& nom)
        : Utilisateur(nom, TypeUtilisateur::ADMINISTRATEUR) {
    // Les administrateurs ont tous les droits
    ajouterDroit(Droit::LIRE);
    ajouterDroit(Droit::AJOUTER);
    ajouterDroit(Droit::MODIFIER);
    ajouterDroit(Droit::SUPPRIMER);
    ajouterDroit(Droit::GERER_FICHIERS);
    ajouterDroit(Droit::RELOAD);
}

bool Administrateur::peutExecuter(Droit droit) const {
    // L'administrateur peut tout faire
    return true;
}

bool Administrateur::estAdministrateur() const {
    return true;
}

void Administrateur::afficherDroits() const {
    std::cout << "=== DROITS ADMINISTRATEUR ===\n";
    std::cout << "Type d'utilisateur: Administrateur\n";
    std::cout << "Droits accordes: TOUS\n";
    std::cout << "\nFonctionnalites disponibles:\n";
    std::cout << "- Toutes les fonctionnalites client\n";
    std::cout << "- Ajouter des ressources\n";
    std::cout << "- Supprimer des ressources\n";
    std::cout << "- Modifier des ressources\n";
    std::cout << "- Gerer les fichiers (Load/Save/Clear)\n";
    std::cout << "- Reinitialiser la mediathèque\n";
}

bool Administrateur::authentifier(const std::string& motDePasse) {
    return motDePasse == MOT_DE_PASSE_ADMIN;
}

void Administrateur::changerMotDePasse(const std::string& ancienMdp, const std::string& nouveauMdp) {
    // Cette fonction pourrait être etendue pour modifier le mot de passe
    // Pour l'instant, elle est juste une ebauche
    if (ancienMdp == MOT_DE_PASSE_ADMIN && !nouveauMdp.empty()) {
        std::cout << "Changement de mot de passe non implemente dans cette version.\n";
        std::cout << "Le mot de passe reste: " << MOT_DE_PASSE_ADMIN << "\n";
    } else {
        std::cout << "Ancien mot de passe incorrect ou nouveau mot de passe vide.\n";
    }
}