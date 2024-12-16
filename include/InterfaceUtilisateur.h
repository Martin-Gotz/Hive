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
        Hive& getHive() { return hive; }

    private:
        // Menu g�n�ral
        void afficherMenu() const;

        int obtenirEntreeUtilisateur(const string& message, bool menu);

        void ajouterPartie();
        TypeJoueur demanderTypeJoueur(const string& nomJoueur);
        void supprimerPartie();
        void demarrerPartie();
        void afficherParties() const;


        // Menu � l'int�rieur d'une partie
        void afficherMenuPartie() const;
        void gererChoixUtilisateurMenuPartie();

        void placerPiece();
        void deplacerPiece();
        void AnnulerPiece();
        void terminerPartieEnCours();
        void retournerMenu();


        void afficherInformationsPartie() const;
        void afficherInformationsJoueurs() const;
        void afficherJoueur(const string& titre, const ResumeJoueur& joueur, bool estJoueurActuel) const;
        void afficherMain(const ResumeMain& main) const;
        void afficherPlateau() const;



        // Reaction aux observable
        void afficherEvenement(const Evenement& evenement) const;
        void reagir(const Evenement& evenement);
    };
}