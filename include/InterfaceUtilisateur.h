#pragma once
#include "Hive.h"

using namespace std;

namespace JeuHive {
    class InterfaceUtilisateur : public Observer {
    private:
        Hive& hive;  // R�f�rence � l'objet Hive pour manipuler les parties

    public:
        InterfaceUtilisateur(Hive& h);

        // Gestion des choix de l'utilisateur
        void gererChoixUtilisateur();

    private:
        // Afficher le menu
        void afficherMenu() const;

        // Demander � l'utilisateur les informations n�cessaires pour ajouter une partie
        void ajouterPartie();

        void supprimerPartie();

        void demarrerPartie();

        // Terminer la partie en cours
        void terminerPartie();

        void afficherParties();

        void reagir(const Evenement& evenement) {
            cout << evenement.getDescription() << endl;
        }
    };
}