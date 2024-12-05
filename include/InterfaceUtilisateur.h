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
        // Menu g�n�ral
        void afficherMenu() const;

        void ajouterPartie();
        void supprimerPartie();
        void demarrerPartie();
        void afficherParties();


        // Menu � l'int�rieur d'une partie
        void afficherMenuPartie() const;
        void gererChoixUtilisateurMenuPartie();

        void jouerCoup();
        void changerJoueurActuel();
        void terminerPartieEnCours();

        void afficherEvenement(const Evenement& evenement) const;
        void reagir(const Evenement& evenement);
    };
}