#ifndef PROJETPOO_VHS_H
#define PROJETPOO_VHS_H

#include "Ressource.h"
#include <string>

class VHS : public Ressource {
private:
    std::string maisonProd;
    std::string duree;

public:
    VHS(int id, const std::string& titre, const std::string& auteur,
        const std::string& maisonProd, const std::string& duree);

    void afficher() const override;
};

#endif
