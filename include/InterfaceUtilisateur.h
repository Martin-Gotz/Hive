#pragma once
#include "Hive.h"

using namespace std;

namespace JeuHive {
    class InterfaceUtilisateur : public Observer {
    private:
        Hive& hive;  // R�f�rence � l'objet Hive pour manipuler les parties
        Partie* partieObservee = nullptr;

    public:
        InterfaceUtilisateur(Hive& h);
        ~InterfaceUtilisateur();

        // Gestion des choix de l'utilisateur
        void gererChoixUtilisateur();

    private:
        // Afficher le menu
        void afficherMenu() const;

        bool traiterChoix(int choix);

        // Demander � l'utilisateur les informations n�cessaires pour ajouter une partie
        void ajouterPartie();

        void supprimerPartie();

        void demarrerPartie();

        // Terminer la partie en cours
        void terminerPartie();

        void afficherParties();

        void reagir(const Evenement& evenement);
    };
}