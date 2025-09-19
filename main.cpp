#include <iostream>
#include <fstream>
#include <string>
#include "include/ajout.h"

using namespace std;

int main() {
    // Création du fichier mediatheque.txt s'il n'existe pas
    string fichier = "mediatheque.txt";
    ifstream test(fichier);

    if (!test) {
        ofstream createFile(fichier);
        if (createFile) {
            createFile << "# Fichier mediatheque" << endl;
            cout << "Fichier " << fichier << " créé avec succès." << endl;
        } else {
            cerr << "Erreur lors de la création du fichier " << fichier << endl;
            return 1;
        }
        createFile.flush();
    } else {
        cout << "Fichier " << fichier << " déjà existant." << endl;
    }

    int choix;

    do {
        cout << "\n===== MENU PRINCIPAL =====\n";
        cout << "1. Ajouter une ressource\n";
        cout << "2. Load filename\n";
        cout << "3. Save filename\n";
        cout << "4. SEARCH chaine\n";
        cout << "5. CLEAR\n";
        cout << "6. LIST\n";
        cout << "7. SHOW id\n";
        cout << "8. DELETE id\n";
        cout << "9. RESET\n";
        cout << "10. Quitter\n";
        cout << "Votre choix : ";
        cin >> choix;

        switch (choix) {
            case 1:
                ajouterRessource("mediatheque.txt");
                break;
            case 2:
                cout << "Cette commande doit permettre à l'utilisateur de charger un fichier contenant les ressources disponibles dans la médiathèque\n";
                break;
            case 3:
                cout << "Cette commande permet à l'utilisateur de sauvegarder les données actuellement dans l'outil dans le fichier dont le nom est spécifié en paramètre\n";
                break;
            case 4:
                cout << "Cette fonction permet de rechercher dans la base de données les documents contenant la chaîne de caractères spécifiée en paramètre\n";
                break;
            case 5:
                cout << "Cette commande permet de réinitialiser la base de données courante après une recherche\n";
                break;
            case 6:
                cout << "Cette fonction permet d'afficher de manière compacte les données contenues dans la base de données\n";
                break;
            case 7:
                cout << "SHOW id\n";
                cout << "cette fonction doit permettre d'afficher les informations détaillées sur une ressource précise contenue dans la médiathèque\n";
                break;
            case 8:
                cout << "Cette fonction permet de supprimer une ressource particulière appartenant à la médiathèque\n";
                break;
            case 9:
                cout << "Cette fonction permet de supprimer toutes les ressources contenues dans la bibliothèque.\n";
                break;
            case 10:
                cout << "BYE\n";
                return 0;
            default:
                cout << "Choix invalide, veuillez réessayer.\n";
        }

    } while (choix != 10);

    return 0;
}