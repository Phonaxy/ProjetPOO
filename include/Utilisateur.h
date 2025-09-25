#ifndef PROJETPOO_UTILISATEUR_H
#define PROJETPOO_UTILISATEUR_H

#include <string>
#include <vector>

// Énumération des types d'utilisateurs
enum class TypeUtilisateur {
    CLIENT,
    ADMINISTRATEUR
};

// Énumération des droits d'accès
enum class Droit {
    LIRE,           // Lister, rechercher, afficher
    AJOUTER,        // Ajouter des ressources
    MODIFIER,       // Modifier des ressources
    SUPPRIMER,      // Supprimer des ressources
    GERER_FICHIERS, // Load, Save, Clear, Reinitialiser
    RELOAD          // Recharger les données
};

// Classe abstraite Utilisateur
class Utilisateur {
protected:
    std::string nom;
    TypeUtilisateur type;
    std::vector<Droit> droits;

public:
    Utilisateur(const std::string& nom, TypeUtilisateur type);
    virtual ~Utilisateur() = default;

    // Méthodes virtuelles pures
    virtual bool peutExecuter(Droit droit) const = 0;
    virtual bool estAdministrateur() const = 0;
    virtual void afficherDroits() const = 0;

    // Getters
    const std::string& getNom() const;
    TypeUtilisateur getType() const;
    const std::vector<Droit>& getDroits() const;

protected:
    void ajouterDroit(Droit droit);
    std::string droitToString(Droit droit) const;
};

// Classe Client
class Client : public Utilisateur {
public:
    Client(const std::string& nom = "Client");

    bool peutExecuter(Droit droit) const override;
    bool estAdministrateur() const override;
    void afficherDroits() const override;
};

// Classe Administrateur
class Administrateur : public Utilisateur {
private:
    static const std::string MOT_DE_PASSE_ADMIN;

public:
    Administrateur(const std::string& nom = "Administrateur");

    bool peutExecuter(Droit droit) const override;
    bool estAdministrateur() const override;
    void afficherDroits() const override;

    // Méthode statique d'authentification
    static bool authentifier(const std::string& motDePasse);
    static void changerMotDePasse(const std::string& ancienMdp, const std::string& nouveauMdp);
};

#endif