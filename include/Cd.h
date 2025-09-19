#ifndef PROJETPOO_CD_H
#define PROJETPOO_CD_H

#include "Ressource.h"

class CD : public Ressource {
private:
    std::string maisonProd;
    int nbPistes;
    double duree;

public:
    CD(int id, const std::string& titre, const std::string& auteur,
       const std::string& maisonProd, int nbPistes, double duree,bool dispo);

    void afficher() const override;
};

#endif

