#include "../include/ajout.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <limits>

using namespace std;

// Permet d'extraire un champs ici l'id
static vector<string> split(const string &s, char delim) {
    vector<string> elems;
    string item;
    stringstream ss(s);
    while (getline(ss, item, delim)) elems.push_back(item);
    return elems;
}

// remplace les ';' et retours à la ligne pour ne pas casser le format
static string sanitize(const string &s) {
    string out = s;
    replace(out.begin(), out.end(), ';', ',');
    replace(out.begin(), out.end(), '\n', ' ');
    replace(out.begin(), out.end(), '\r', ' ');
    return out;
}

// récupère le prochain id libre en scannant le fichier (max id + 1)
int getNextId(const string &fichier) {
    ifstream in(fichier);
    if (!in) return 1; // fichier absent -> commencer à 1

    string ligne;
    int maxId = 0;
    while (getline(in, ligne)) {
        if (ligne.empty() || ligne[0] == '#') continue;
        auto toks = split(ligne, ';');
        if (toks.size() > 1) {
            try {
                int id = stoi(toks[0]); // On prend à l'indice 0 l'id
                if (id > maxId) maxId = id;
            } catch (...) {

            }
        }
    }
    return maxId + 1;
}

// procédure ajouter ressource
void ajouterRessource(const string &fichier) {
    cout << "\n=== AJOUT D'UNE RESSOURCE ===\n";
    cout << "1. Livre\n2. Revue\n3. CD\n4. DVD\n5. VHS\n6. Ressource numerique\nVotre choix : ";
    int choixType;
    if (!(cin >> choixType)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Choix invalide.\n";
        return;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // vider le buffer

    string titre, auteur;
    cout << "Titre : "; getline(cin, titre);
    cout << "Auteur : "; getline(cin, auteur);

    int id = getNextId(fichier);
    string dispo = "1"; // 1 = disponible par défaut

    ofstream out(fichier, ios::app);
    if (!out) {
        cerr << "Erreur : impossible d'ouvrir le fichier " << fichier << " en ecriture.\n";
        return;
    }

    switch (choixType) {
        case 1: { // Livre
            string nbPagesStr, collection, resume, anneeStr;
            cout << "Nombre de pages : "; getline(cin, nbPagesStr);
            cout << "Collection : "; getline(cin, collection);
            cout << "Resume : "; getline(cin, resume);
            cout << "Annee (ex: 1999) : "; getline(cin, anneeStr);

            out << id << ";Livre;" << sanitize(titre) << ";" << sanitize(auteur) << ";" << dispo
                << ";" << sanitize(nbPagesStr) << ";" << sanitize(collection) << ";" << sanitize(resume)
                << ";" << sanitize(anneeStr) << "\n";
            break;
        }
        case 2: { // Revue
            string nbPagesStr, editeur, nbArticlesStr, articlesLine, resume, anneeStr;
            cout << "Nombre de pages : "; getline(cin, nbPagesStr);
            cout << "Editeur : "; getline(cin, editeur);
            cout << "Nombre d'articles : "; getline(cin, nbArticlesStr);
            cout << "Noms des articles (separes par '|' ) : "; getline(cin, articlesLine);
            cout << "Resume : "; getline(cin, resume);
            cout << "Annee : "; getline(cin, anneeStr);

            out << id << ";Revue;" << sanitize(titre) << ";" << sanitize(auteur) << ";" << dispo
                << ";" << sanitize(nbPagesStr) << ";" << sanitize(editeur) << ";" << sanitize(nbArticlesStr)
                << ";" << sanitize(articlesLine) << ";" << sanitize(resume) << ";" << sanitize(anneeStr) << "\n";
            break;
        }
        case 3: { // CD
            string maisonProd, nbPistesStr, dureeStr;
            cout << "Maison de production : "; getline(cin, maisonProd);
            cout << "Nombre de pistes : "; getline(cin, nbPistesStr);
            cout << "Duree (minutes ou hh:mm:ss) : "; getline(cin, dureeStr);

            out << id << ";CD;" << sanitize(titre) << ";" << sanitize(auteur) << ";" << dispo
                << ";" << sanitize(maisonProd) << ";" << sanitize(nbPistesStr) << ";" << sanitize(dureeStr) << "\n";
            break;
        }
        case 4: { // DVD
            string maisonProd, dureeStr, nbChapitresStr;
            cout << "Maison de production : "; getline(cin, maisonProd);
            cout << "Duree : "; getline(cin, dureeStr);
            cout << "Nombre de chapitres : "; getline(cin, nbChapitresStr);

            out << id << ";DVD;" << sanitize(titre) << ";" << sanitize(auteur) << ";" << dispo
                << ";" << sanitize(maisonProd) << ";" << sanitize(dureeStr) << ";" << sanitize(nbChapitresStr) << "\n";
            break;
        }
        case 5: { // VHS
            string maisonProd, dureeStr;
            cout << "Maison de production : "; getline(cin, maisonProd);
            cout << "Duree : "; getline(cin, dureeStr);

            out << id << ";VHS;" << sanitize(titre) << ";" << sanitize(auteur) << ";" << dispo
                << ";" << sanitize(maisonProd) << ";" << sanitize(dureeStr) << "\n";
            break;
        }
        case 6: { // Ressource numérique
            string typeF, tailleStr, url;
            cout << "Type (PDF, DOC, etc.) : "; getline(cin, typeF);
            cout << "Taille (Mo) : "; getline(cin, tailleStr);
            cout << "URL : "; getline(cin, url);

            out << id << ";RessourceNumerique;" << sanitize(titre) << ";" << sanitize(auteur) << ";" << dispo
                << ";" << sanitize(typeF) << ";" << sanitize(tailleStr) << ";" << sanitize(url) << "\n";
            break;
        }
    }

    out.flush();
    out.close();
}

