#ifndef PROJETPOO_CD_H
#define PROJETPOO_CD_H

#include "Ressource.h"

class CD : public Ressource {
private:
    std::string maisonProd;
    int nbPistes;
    std::string duree;

public:
    CD(int id, const std::string& titre, const std::string& auteur, bool dispo,
       const std::string& maisonProd, int nbPistes, const std::string& duree);

    void afficher() const override;
    std::string toFileString() const override;
};

#endif
