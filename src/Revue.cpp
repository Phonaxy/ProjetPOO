#include "../include/Revue.h"


Revue::Revue(int id, const std::string& titre, const std::string& auteur, bool dispo,
             int nbPages, const std::string& editeur, int nbArticles,
             const std::string& resume, int annee)
        : Ressource(id, titre, auteur, dispo), nbPages(nbPages), editeur(editeur),
          nbArticles(nbArticles), resume(resume), annee(annee) {}

void Revue::ajouterArticle(const std::string& article) {
    lesArticles.push_back(article);
}

void Revue::listerArticles() const {
    std::cout << "Articles:\n";
    for (const auto& article : lesArticles) {
        std::cout << "- " << article << "\n";
    }
}

void Revue::afficher() const {
    std::cout << "=== REVUE ===\n";
    std::cout << "ID: " << id << "\n";
    std::cout << "Titre: " << titre << "\n";
    std::cout << "Auteur: " << auteur << "\n";
    std::cout << "Disponible: " << (dispo ? "Oui" : "Non") << "\n";
    std::cout << "Nombre de pages: " << nbPages << "\n";
    std::cout << "Editeur: " << editeur << "\n";
    std::cout << "Nombre d'articles: " << nbArticles << "\n";
    listerArticles();
    std::cout << "Resume: " << resume << "\n";
    std::cout << "Annee: " << annee << "\n";
}

std::string Revue::toFileString() const {
    std::string articlesStr;
    for (size_t i = 0; i < lesArticles.size(); ++i) {
        if (i > 0) articlesStr += "|";
        articlesStr += lesArticles[i];
    }
    return std::to_string(id) + ";Revue;" + titre + ";" + auteur + ";" +
           (dispo ? "1" : "0") + ";" + std::to_string(nbPages) + ";" +
           editeur + ";" + std::to_string(nbArticles) + ";" + articlesStr + ";" +
           resume + ";" + std::to_string(annee);
}

void Revue::setArticlesFromString(const std::string& articlesString) {
    lesArticles.clear();
    std::stringstream ss(articlesString);
    std::string article;
    while (std::getline(ss, article, '|')) {
        lesArticles.push_back(article);
    }
}
