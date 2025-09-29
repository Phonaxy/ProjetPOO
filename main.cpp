#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <vector>
#include <limits>
#include "include/Mediatheque.h"
#include "include/Utilisateur.h"

using namespace std;
namespace fs = std::filesystem;

void afficherFichiersDonnees() {
    string dataPath = "C:\\Users\\Phona\\CLionProjects\\ProjetPOO\\data";
    cout << "\n=== FICHIERS DE DONNEES DISPONIBLES ===\n";
    cout << "Repertoire : " << dataPath << "\n\n";

    try {
        if (fs::exists(dataPath) && fs::is_directory(dataPath)) {
            int index = 1;
            for (const auto& entry : fs::directory_iterator(dataPath)) {
                if (entry.is_regular_file() && entry.path().extension() == ".txt") {
                    string filename = entry.path().filename().string();
                    cout << index << ". " << filename;

                    // Ajouter une description basée sur le nom du fichier
                    if (filename.find("bibliotheque") != string::npos) {
                        cout << " (Collection de livres classiques)";
                    } else if (filename.find("numerique") != string::npos) {
                        cout << " (Ressources numeriques et e-books)";
                    } else if (filename.find("multimedia") != string::npos) {
                        cout << " (CD, DVD, VHS)";
                    } else if (filename.find("revues") != string::npos) {
                        cout << " (Magazines et revues)";
                    } else if (filename.find("enfants") != string::npos) {
                        cout << " (Collection jeunesse)";
                    }
                    cout << "\n";
                    index++;
                }
            }
            if (index == 1) {
                cout << "Aucun fichier .txt trouve dans le repertoire.\n";
                cout << "Conseil : Creez des fichiers de donnees avec des ressources pre-remplies\n";
            }
        } else {
            cout << "Le repertoire n'existe pas ou n'est pas accessible.\n";
            cout << "Creez le repertoire : " << dataPath << "\n";
        }
    } catch (const fs::filesystem_error& e) {
        cout << "Erreur d'acces au systeme de fichiers: " << e.what() << "\n";
    }
}

string choisirFichierDonnees() {
    string dataPath = "C:\\Users\\Phona\\CLionProjects\\ProjetPOO\\data";
    vector<string> fichiers;

    try {
        if (fs::exists(dataPath) && fs::is_directory(dataPath)) {
            for (const auto& entry : fs::directory_iterator(dataPath)) {
                if (entry.is_regular_file() && entry.path().extension() == ".txt") {
                    fichiers.push_back(entry.path().string());
                }
            }
        }
    } catch (const fs::filesystem_error& e) {
        cout << "Erreur d'acces au repertoire: " << e.what() << "\n";
        return "";
    }

    if (fichiers.empty()) {
        cout << "Aucun fichier .txt trouve dans le repertoire de donnees.\n";
        return "";
    }

    afficherFichiersDonnees();
    cout << "Choisissez un fichier (numero) ou 0 pour annuler: ";

    int choix;
    if (!(cin >> choix) || choix < 0 || choix > static_cast<int>(fichiers.size())) {
        cout << "Choix invalide.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return "";
    }

    if (choix == 0) return "";

    return fichiers[choix - 1];
}

void afficherMenuClient() {
    cout << "\n===== MENU CLIENT =====\n";
    cout << "1. Lister les ressources\n";
    cout << "2. Rechercher une ressource\n";
    cout << "3. Afficher une ressource (SHOW id)\n";
    cout << "4. Recharger les donnees (RELOAD)\n";
    cout << "5. Quitter\n";
    cout << "Votre choix : ";
}

void afficherMenuAdmin() {
    cout << "\n===== MENU ADMINISTRATEUR =====\n";
    cout << "1. Ajouter une ressource\n";
    cout << "2. Charger un fichier (LOAD)\n";
    cout << "3. Sauvegarder (SAVE)\n";
    cout << "4. Rechercher (SEARCH)\n";
    cout << "5. Vider la mediatheque (CLEAR)\n";
    cout << "6. Lister les ressources (LIST)\n";
    cout << "7. Afficher une ressource (SHOW id)\n";
    cout << "8. Supprimer une ressource (DELETE id)\n";
    cout << "9. Reinitialiser la mediatheque\n";
    cout << "10. Recharger les donnees (RELOAD)\n";
    cout << "11. Quitter\n";
    cout << "Votre choix : ";
}

void gererSessionClient(Mediatheque& mediatheque, const string& fichier) {
    int choix;
    do {
        afficherMenuClient();
        cin >> choix;

        switch (choix) {
            case 1: // Lister
                mediatheque.lister();
                break;

            case 2: { // Rechercher
                cout << "Chaine de recherche : ";
                cin.ignore();
                string critere;
                getline(cin, critere);
                auto ressource = mediatheque.chercher(critere);
                if (ressource) {
                    cout << "\nRessource trouvee :\n";
                    ressource->afficher();
                } else {
                    cout << "Aucune ressource trouvee contenant '" << critere << "'.\n";
                }
                break;
            }

            case 3: { // Afficher
                cout << "ID de la ressource a afficher : ";
                int id;
                if (cin >> id) {
                    mediatheque.afficher(id);
                } else {
                    cout << "ID invalide.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                break;
            }

            case 4: // Recharger
                cout << "Rechargement des donnees...\n";
                mediatheque.load(fichier);
                break;

            case 5: // Quitter
                cout << "Au revoir !\n";
                break;

            default:
                cout << "Choix invalide pour un client.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while (choix != 5);
}

void gererSessionAdmin(Mediatheque& mediatheque, const string& fichier) {
    int choix;
    do {
        afficherMenuAdmin();
        cin >> choix;

        switch (choix) {
            case 1: // Ajouter
                mediatheque.ajouterRessource();
                break;

            case 2: { // Load avec choix de fichier
                cout << "=== CHARGEMENT DE DONNEES ===\n";
                cout << "1. Charger depuis le dossier data (ressources pre-remplies)\n";
                cout << "2. Charger un fichier local\n";
                cout << "Votre choix : ";

                int choixLoad;
                if (cin >> choixLoad) {
                    if (choixLoad == 1) {
                        // Charger depuis le dossier data
                        string fichierChoisi = choisirFichierDonnees();
                        if (!fichierChoisi.empty()) {
                            cout << "Chargement du fichier de donnees : " << fs::path(fichierChoisi).filename().string() << "\n";
                            mediatheque.load(fichierChoisi);
                            cout << "Les donnees ont ete chargees dans la mediatheque.\n";
                            cout << "Voulez-vous sauvegarder ces donnees dans " << fichier << " ? (o/n) : ";
                            char reponse;
                            cin >> reponse;
                            if (reponse == 'o' || reponse == 'O') {
                                mediatheque.save(fichier);
                                cout << "Donnees sauvegardees dans " << fichier << "\n";
                            }
                        }
                    } else if (choixLoad == 2) {
                        // Charger un fichier local
                        cout << "Nom du fichier a charger : ";
                        cin.ignore();
                        string fichierLocal;
                        getline(cin, fichierLocal);
                        if (!fichierLocal.empty()) {
                            mediatheque.load(fichierLocal);
                        }
                    } else {
                        cout << "Choix invalide.\n";
                    }
                } else {
                    cout << "Choix invalide.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                break;
            }

            case 3: { // Save
                cout << "Nom du fichier de sauvegarde (ou ENTER pour " << fichier << ") : ";
                cin.ignore();
                string fichierSave;
                getline(cin, fichierSave);
                if (fichierSave.empty()) {
                    fichierSave = fichier;
                }
                mediatheque.save(fichierSave);
                break;
            }

            case 4: { // Search
                cout << "Chaine de recherche : ";
                cin.ignore();
                string critere;
                getline(cin, critere);
                auto ressource = mediatheque.chercher(critere);
                if (ressource) {
                    cout << "\nRessource trouvee :\n";
                    ressource->afficher();
                } else {
                    cout << "Aucune ressource trouvee contenant '" << critere << "'.\n";
                }
                break;
            }

            case 5: // Clear
                mediatheque.clear();
                break;

            case 6: // List
                mediatheque.lister();
                break;

            case 7: { // Show
                cout << "ID de la ressource a afficher : ";
                int id;
                if (cin >> id) {
                    mediatheque.afficher(id);
                } else {
                    cout << "ID invalide.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                break;
            }

            case 8: { // Delete
                cout << "ID de la ressource a supprimer : ";
                int id;
                if (cin >> id) {
                    mediatheque.supprimer(id);
                } else {
                    cout << "ID invalide.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                break;
            }

            case 9: // Réinitialiser
                mediatheque.reinitialiser(fichier);
                cout << "Mediatheque reinitialisee.\n";
                break;

            case 10: // Reload
                cout << "Rechargement des donnees...\n";
                mediatheque.load(fichier);
                break;

            case 11: // Quitter
                cout << "Sauvegarde automatique...\n";
                mediatheque.save(fichier);
                cout << "Au revoir !\n";
                break;

            default:
                cout << "Choix invalide, veuillez reessayer.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

    } while (choix != 11);
}

int main() {
    string fichier = "mediatheque.txt";
    Mediatheque mediatheque;

    // Phase d'authentification
    cout << "=== SYSTEME D'AUTHENTIFICATION ===\n";
    cout << "Entrez le mot de passe administrateur (ou ENTER pour acces client) : ";

    string motDePasse;
    getline(cin, motDePasse);

    // Créer un utilisateur selon l'authentification
    unique_ptr<Utilisateur> utilisateur;

    if (Administrateur::authentifier(motDePasse)) {
        utilisateur = make_unique<Administrateur>();
        cout << "Authentification reussie - Mode Administrateur\n";
    } else {
        utilisateur = make_unique<Client>();
        if (!motDePasse.empty()) {
            cout << "Mot de passe incorrect - Mode Client\n";
        } else {
            cout << "Mode Client active\n";
        }
    }

    // Vérifier si le fichier existe, sinon le créer
    ifstream test(fichier);
    if (!test) {
        ofstream createFile(fichier);
        if (createFile) {
            createFile << "# Fichier mediatheque" << endl;
            cout << "Fichier " << fichier << " cree avec succes." << endl;
        } else {
            cerr << "Erreur lors de la creation du fichier " << fichier << endl;
            return 1;
        }
    } else {
        cout << "Fichier " << fichier << " deja existant." << endl;
        mediatheque.load(fichier); // charger le contenu existant dans l'objet
    }

    // Lancer la session appropriée selon le type d'utilisateur
    if (utilisateur->estAdministrateur()) {
        gererSessionAdmin(mediatheque, fichier);
    } else {
        gererSessionClient(mediatheque, fichier);
    }

    return 0;
}