#ifndef PROJETPOO_RESSOURCE_H
#define PROJETPOO_RESSOURCE_H

#include <string>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include <sstream>
#include <algorithm>
#include <limits>

class Ressource {
protected:
    int id{};
    std::string titre;
    std::string auteur;
    bool dispo{};

public:
    Ressource(int id, const std::string& titre, const std::string& auteur, bool dispo = true);
    virtual ~Ressource() = default;

    virtual void afficher() const = 0;
    virtual void reserver();
    virtual void emprunter();
    virtual void rendre();

    int getId() const;
    const std::string& getTitre() const;
    const std::string& getAuteur() const;
    bool estDisponible() const;

    // Pour la sauvegarde
    virtual std::string toFileString() const = 0;
};

#endif
