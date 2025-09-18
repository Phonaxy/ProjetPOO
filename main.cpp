#include <iostream>

using namespace std;

int main() {
    int choix;

    do {
        cout << "\n===== MENU PRINCIPAL =====\n";
        cout << "1. ADD type\n";
        cout << "2. Load filename\n";
        cout << "3. Save filename\n";
        cout << "4. SEARCH chaine\n";
        cout << "5. CLEAR\n";
        cout <<"6. LIST\n";
        cout <<"7. SHOW id\n";
        cout <<"8. DELETE id\n";
        cout <<"9. RESET\n";
        cout <<"10. BYE\n";
        cout << "Votre choix : ";
        cin >> choix;

        switch (choix) {
            case 1:
                cout << "ADD type\n";
                cout << "ADD type permet de lancer une procédure permettant de creer une nouvelle ressource en fonction du type specifie en parametre.\n";
                break;
            case 2:
                cout << "Load filename\n";
                cout << "cette commande doit permettre à l'utilisateur de charger un fichier contenant les ressources disponibles dans la médiathèque\n";
                break;
            case 3:
                cout << "Save filename\n";
                cout << ": cette commande permet à l'utilisateur de sauvegarder les données actuellement dans l'outil dans le fichier dont le nom est spécifié en paramètre\n";
                break;
            case 4:
                cout << "SEARCH chaine\n";
                cout << "cette fonction permet de rechercher dans la base de données les documents contenant la chaîne de caractères spécifiée en paramètre\n";
                break;
            case 5:
                cout << "CLEAR\n";
                cout << "cette commande permet de réinitialiser la base de données courante après une recherche\n";
                break;
            case 6:
                cout << "LIST\n";
                cout << "cette fonction permet d'afficher de manière compacte les données contenues dans la base de données\n";
                break;
            case 7:
                cout << "SHOW id\n";
                cout << "cette fonction doit permettre d'afficher les informations détaillées sur une ressource précise contenue dans la médiathèque\n";
                break;
            case 8:
                cout << "DELETE id\n";
                cout << "cette méthode permet de supprimer une ressource particulière appartenant à la médiathèque\n";
                break;
            case 9:
                cout << "RESET\n";
                cout << "cette dernière méthode permet de supprimer toutes les ressources contenues dans la bibliothèque.\n";
                break;
            case 10:
                cout << "BYE\n";
                cout << "lorsque l'utilisateur lance cette commande, il demande simplement à quitter votre application\n";
                break;
            default:
                cout << "Choix invalide, veuillez réessayer.\n";
        }

    } while (choix != 10);

    return 0;
}
    