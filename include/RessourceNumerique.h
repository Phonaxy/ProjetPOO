#ifndef PROJETPOO_RESSOURCENUMERIQUE_H
#define PROJETPOO_RESSOURCENUMERIQUE_H

#include "Ressource.h"

class RessourceNumerique : public Ressource {
private:
    std::string type;
    double taille;
    std::string url;

public:
    RessourceNumerique(int id, const std::string& titre, const std::string& auteur, bool dispo,
                       const std::string& type, double taille, const std::string& url);

    void afficher() const override;
    std::string toFileString() const override;
};

#endif