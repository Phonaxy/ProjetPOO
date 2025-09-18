#ifndef PROJETPOO_LIVRE_H
#define PROJETPOO_LIVRE_H
#include "Ressource.h"

class Livre : public Ressource {
private:
    int nbPages;
    std::string collection;
    std::string resume;
    int annee;

public:
    Livre(int id, const std::string& titre, const std::string& auteur,
          int nbPages, const std::string& collection, const std::string& resume, int annee);

    void afficher() const override;
};

#endif

