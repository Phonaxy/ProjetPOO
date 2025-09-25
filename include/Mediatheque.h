#ifndef PROJETPOO_MEDIATHEQUE_H
#define PROJETPOO_MEDIATHEQUE_H

#include "Ressource.h"
#include <vector>
#include <memory>

// ==================== MEDIATHEQUE.H ====================
class Mediatheque {
private:
    std::vector<std::shared_ptr<Ressource>> lesR;

public:
    Mediatheque() = default;

    void ajouterRessource();
    void supprimer(int id);
    std::shared_ptr<Ressource> chercher(const std::string& critere) const;
    void lister() const;
    void afficher(int id) const;
    void clear();

    void save(const std::string& fichier) const;
    void load(const std::string& fichier);
    void reinitialiser(const std::string& fichier);

    int getNextIdInMemory() const;

private:
    std::vector<std::string> split(const std::string& s, char delim) const;
    std::string sanitize(const std::string& s) const;
};

#endif
