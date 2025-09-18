#ifndef PROJETPOO_MEDIATHEQUE_H
#define PROJETPOO_MEDIATHEQUE_H

#include "Ressource.h"
#include <vector>
#include <memory>

class Mediatheque {
private:
    std::vector<std::shared_ptr<Ressource>> lesR;

public:
    Mediatheque() = default;

    void ajouter(std::shared_ptr<Ressource> r);
    void supprimer(int id);
    [[nodiscard]] std::shared_ptr<Ressource> chercher(const std::string& critere) const;
    void lister() const;
    void afficher(int id) const;

    void save(const std::string& fichier) const;
    void load(const std::string& fichier);
    void reinitialiser();
};

#endif
