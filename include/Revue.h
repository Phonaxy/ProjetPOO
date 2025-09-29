#ifndef PROJETPOO_REVUE_H
#define PROJETPOO_REVUE_H
#include "Ressource.h"
#include <vector>

class Revue : public Ressource {
private:
    int nbPages;
    std::string editeur;
    int nbArticles;
    std::vector<std::string> lesArticles;
    std::string resume;
    int annee;

public:
    Revue(int id, const std::string& titre, const std::string& auteur, bool dispo,
          int nbPages, const std::string& editeur, int nbArticles,
          const std::string& resume, int annee);

    void ajouterArticle(const std::string& article);
    void listerArticles() const;
    void afficher() const override;
    std::string toFileString() const override;

    void setArticlesFromString(const std::string& articlesString);
};

#endif
