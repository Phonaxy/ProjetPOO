#ifndef PROJETPOO_DVD_H
#define PROJETPOO_DVD_H

#include "Ressource.h"
#include <string>

class DVD : public Ressource {
private:
    std::string maisonProd;
    std::string duree;
    int nbChapitres;

public:
    DVD(int id, const std::string& titre, const std::string& auteur,
        const std::string& maisonProd, const std::string& duree, int nbChapitres, bool dispo);

    void afficher() const override;
};

#endif
