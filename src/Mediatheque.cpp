#include <iostream>
#include <fstream>
#include <memory>
#include <limits>
#include <string>
#include "../include/Mediatheque.h"
#include "../include/Livre.h"
#include "../include/Revue.h"
#include "../include/CD.h"
#include "../include/DVD.h"
#include "../include/VHS.h"
#include "../include/RessourceNumerique.h"

// Mediatheque Implementation
std::vector<std::string> Mediatheque::split(const std::string& s, char delim) const {
    std::vector<std::string> elems;
    std::string item;
    std::stringstream ss(s);
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

std::string Mediatheque::sanitize(const std::string& s) const {
    std::string out = s;
    std::replace(out.begin(), out.end(), ';', ',');
    std::replace(out.begin(), out.end(), '\n', ' ');
    std::replace(out.begin(), out.end(), '\r', ' ');
    return out;
}

int Mediatheque::getNextIdInMemory() const {
    int maxId = 0;
    for (const auto& res : lesR) {
        if (res->getId() > maxId)
            maxId = res->getId();
    }
    return maxId + 1;
}

void Mediatheque::ajouterRessource() {
    std::cout << "\n=== AJOUT D'UNE RESSOURCE ===\n";
    std::cout << "1. Livre\n2. Revue\n3. CD\n4. DVD\n5. VHS\n6. Ressource numerique\nVotre choix : ";
    int choixType;

    if (!(std::cin >> choixType)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Choix invalide.\n";
        return;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::string titre, auteur;
    std::cout << "Titre : "; std::getline(std::cin, titre);
    std::cout << "Auteur : "; std::getline(std::cin, auteur);

    int id = getNextIdInMemory();
    bool dispo = true;

    try {
        switch (choixType) {
            case 1: { // Livre
                int nbPages, annee;
                std::string collection, resume;
                std::cout << "Nombre de pages : "; std::cin >> nbPages;
                std::cin.ignore();
                std::cout << "Collection : "; std::getline(std::cin, collection);
                std::cout << "Resume : "; std::getline(std::cin, resume);
                std::cout << "Annee : "; std::cin >> annee;

                auto livre = std::make_shared<Livre>(id, titre, auteur, dispo, nbPages, collection, resume, annee);
                lesR.push_back(livre);
                break;
            }
            case 2: { // Revue
                int nbPages, nbArticles, annee;
                std::string editeur, articlesLine, resume;
                std::cout << "Nombre de pages : "; std::cin >> nbPages;
                std::cin.ignore();
                std::cout << "Editeur : "; std::getline(std::cin, editeur);
                std::cout << "Nombre d'articles : "; std::cin >> nbArticles;
                std::cin.ignore();
                std::cout << "Noms des articles (separes par '|') : "; std::getline(std::cin, articlesLine);
                std::cout << "Resume : "; std::getline(std::cin, resume);
                std::cout << "Annee : "; std::cin >> annee;

                auto revue = std::make_shared<Revue>(id, titre, auteur, dispo, nbPages, editeur, nbArticles, resume, annee);
                revue->setArticlesFromString(articlesLine);
                lesR.push_back(revue);
                break;
            }
            case 3: { // CD
                int nbPistes;
                std::string maisonProd, duree;
                std::cout << "Maison de production : "; std::getline(std::cin, maisonProd);
                std::cout << "Nombre de pistes : "; std::cin >> nbPistes;
                std::cin.ignore();
                std::cout << "Duree : "; std::getline(std::cin, duree);

                auto cd = std::make_shared<CD>(id, titre, auteur, dispo, maisonProd, nbPistes, duree);
                lesR.push_back(cd);
                break;
            }
            case 4: { // DVD
                int nbChapitres;
                std::string maisonProd, duree;
                std::cout << "Maison de production : "; std::getline(std::cin, maisonProd);
                std::cout << "Duree : "; std::getline(std::cin, duree);
                std::cout << "Nombre de chapitres : "; std::cin >> nbChapitres;

                auto dvd = std::make_shared<DVD>(id, titre, auteur, dispo, maisonProd, duree, nbChapitres);
                lesR.push_back(dvd);
                break;
            }
            case 5: { // VHS
                std::string maisonProd, duree;
                std::cout << "Maison de production : "; std::getline(std::cin, maisonProd);
                std::cout << "Duree : "; std::getline(std::cin, duree);

                auto vhs = std::make_shared<VHS>(id, titre, auteur, dispo, maisonProd, duree);
                lesR.push_back(vhs);
                break;
            }
            case 6: { // Ressource numerique
                double taille;
                std::string typeF, url;
                std::cout << "Type (PDF, DOC, etc.) : "; std::getline(std::cin, typeF);
                std::cout << "Taille (Mo) : "; std::cin >> taille;
                std::cin.ignore();
                std::cout << "URL : "; std::getline(std::cin, url);

                auto resNum = std::make_shared<RessourceNumerique>(id, titre, auteur, dispo, typeF, taille, url);
                lesR.push_back(resNum);
                break;
            }
            default:
                std::cout << "Choix invalide.\n";
                return;
        }
        std::cout << "Ressource ajoutee avec succes (ID: " << id << ").\n";
    } catch (const std::exception& e) {
        std::cout << "Erreur lors de l'ajout : " << e.what() << "\n";
    }
}

void Mediatheque::supprimer(int id) {
    auto it = std::find_if(lesR.begin(), lesR.end(),
                           [id](const std::shared_ptr<Ressource>& res) {
                               return res->getId() == id;
                           });

    if (it != lesR.end()) {
        lesR.erase(it);
        std::cout << "Ressource " << id << " supprimee.\n";
    } else {
        std::cout << "Ressource " << id << " non trouvee.\n";
    }
}

std::shared_ptr<Ressource> Mediatheque::chercher(const std::string& critere) const {
    std::string critereLower = critere;
    std::transform(critereLower.begin(), critereLower.end(), critereLower.begin(), ::tolower);

    for (const auto& res : lesR) {
        std::string titre = res->getTitre();
        std::string auteur = res->getAuteur();
        std::transform(titre.begin(), titre.end(), titre.begin(), ::tolower);
        std::transform(auteur.begin(), auteur.end(), auteur.begin(), ::tolower);

        if (titre.find(critereLower) != std::string::npos ||
            auteur.find(critereLower) != std::string::npos) {
            return res;
        }
    }
    return nullptr;
}

void Mediatheque::lister() const {
    if (lesR.empty()) {
        std::cout << "Aucune ressource dans la mediatheque.\n";
        return;
    }

    std::cout << "\n=== LISTE DES RESSOURCES ===\n";
    for (const auto& res : lesR) {
        std::cout << "ID: " << res->getId() << " | "
                  << "Titre: " << res->getTitre() << " | "
                  << "Auteur: " << res->getAuteur() << " | "
                  << "Disponible: " << (res->estDisponible() ? "Oui" : "Non") << "\n";
    }
}

void Mediatheque::afficher(int id) const {
    auto it = std::find_if(lesR.begin(), lesR.end(),
                           [id](const std::shared_ptr<Ressource>& res) {
                               return res->getId() == id;
                           });

    if (it != lesR.end()) {
        (*it)->afficher();
    } else {
        std::cout << "Ressource " << id << " non trouvee.\n";
    }
}

void Mediatheque::clear() {
    lesR.clear();
    std::cout << "Mediatheque videe.\n";
}

void Mediatheque::save(const std::string& fichier) const {
    std::ofstream out(fichier);
    if (!out) {
        std::cerr << "Erreur : impossible d'ouvrir le fichier " << fichier << " en ecriture.\n";
        return;
    }

    out << "# Fichier mediatheque\n";
    for (const auto& res : lesR) {
        out << res->toFileString() << "\n";
    }

    std::cout << "Sauvegarde terminee dans " << fichier << " (" << lesR.size() << " ressources).\n";
}

void Mediatheque::load(const std::string& fichier) {
    std::ifstream in(fichier);
    if (!in) {
        std::cout << "Impossible d'ouvrir le fichier " << fichier << ".\n";
        return;
    }

    lesR.clear();
    std::string ligne;
    int count = 0;

    while (std::getline(in, ligne)) {
        if (ligne.empty() || ligne[0] == '#') continue;

        auto tokens = split(ligne, ';');
        if (tokens.size() < 5) continue;

        try {
            int id = std::stoi(tokens[0]);
            std::string type = tokens[1];
            std::string titre = tokens[2];
            std::string auteur = tokens[3];
            bool dispo = (tokens[4] == "1");

            if (type == "Livre" && tokens.size() >= 9) {
                int nbPages = std::stoi(tokens[5]);
                std::string collection = tokens[6];
                std::string resume = tokens[7];
                int annee = std::stoi(tokens[8]);
                lesR.push_back(std::make_shared<Livre>(id, titre, auteur, dispo, nbPages, collection, resume, annee));
                count++;
            }
            else if (type == "Revue" && tokens.size() >= 11) {
                int nbPages = std::stoi(tokens[5]);
                std::string editeur = tokens[6];
                int nbArticles = std::stoi(tokens[7]);
                std::string articles = tokens[8];
                std::string resume = tokens[9];
                int annee = std::stoi(tokens[10]);
                auto revue = std::make_shared<Revue>(id, titre, auteur, dispo, nbPages, editeur, nbArticles, resume, annee);
                revue->setArticlesFromString(articles);
                lesR.push_back(revue);
                count++;
            }
            else if (type == "CD" && tokens.size() >= 8) {
                std::string maisonProd = tokens[5];
                int nbPistes = std::stoi(tokens[6]);
                std::string duree = tokens[7];
                lesR.push_back(std::make_shared<CD>(id, titre, auteur, dispo, maisonProd, nbPistes, duree));
                count++;
            }
            else if (type == "DVD" && tokens.size() >= 8) {
                std::string maisonProd = tokens[5];
                std::string duree = tokens[6];
                int nbChapitres = std::stoi(tokens[7]);
                lesR.push_back(std::make_shared<DVD>(id, titre, auteur, dispo, maisonProd, duree, nbChapitres));
                count++;
            }
            else if (type == "VHS" && tokens.size() >= 7) {
                std::string maisonProd = tokens[5];
                std::string duree = tokens[6];
                lesR.push_back(std::make_shared<VHS>(id, titre, auteur, dispo, maisonProd, duree));
                count++;
            }
            else if (type == "RessourceNumerique" && tokens.size() >= 8) {
                std::string typeRes = tokens[5];
                double taille = std::stod(tokens[6]);
                std::string url = tokens[7];
                lesR.push_back(std::make_shared<RessourceNumerique>(id, titre, auteur, dispo, typeRes, taille, url));
                count++;
            }
        } catch (const std::exception& e) {
            std::cout << "Erreur lors du chargement de la ligne: " << ligne << "\n";
        }
    }

    std::cout << "Chargement termine : " << count << " ressources chargees.\n";
}

void Mediatheque::reinitialiser(const std::string& fichier) {
    lesR.clear();
    std::ofstream ofs(fichier, std::ofstream::trunc);
    ofs << "# Fichier mediatheque\n";
    std::cout << "Mediatheque reinitialisee.\n";
}
