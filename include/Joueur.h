#pragma once
#include "MainPiece.h"
#include "Piece.h"
#include "Coordonnee.h"
#include "Plateau.h"
#include <string>
#include <vector>

namespace JeuHive {

    class Joueur {
    private:
        string nom;
        TypeJoueur type;
        Couleur couleur;
        MainPiece main;

    public:
        Joueur(string nom, TypeJoueur type);
        Joueur(string nom, TypeJoueur type, Couleur couleur);

        // Accesseurs
        string getNom() const { return nom; }
        Couleur getCouleur() const { return couleur; }
        const MainPiece& getMain() const { return main; }
        TypeJoueur getType() const { return type; }

        // Mutateurs
        void setCouleur(Couleur nouvelleCouleur) { couleur = nouvelleCouleur; }

        // Méthodes principales
        void remplirMain();
        void retirerPiece(Piece* piece);

        // Ajouter une pièce à la main
        void ajouterPieceMain(Piece* piece);

        ResumeJoueur resumer() const;
    };

    class IntelligenceA : public Joueur {
    public:
        IntelligenceA() : Joueur("IA", TypeJoueur::IA) {}
        /*
        void jouerCoupIA(Plateau& plateau, int tour) {
            // Obtenir tous les coups possibles pour le joueur
            //vector<Coup*> coupsPossibles = plateau.(*this);
            //plateau.

            // Vérifier s'il y a des coups possibles
            if (coupsPossibles.empty()) {
                throw HiveException("Aucun coup possible pour le joueur.");
            }

            // Initialiser le générateur de nombres aléatoires
            std::srand(static_cast<unsigned int>(std::time(nullptr)));

            // Choisir un coup aléatoirement
            int indexCoupChoisi = std::rand() % coupsPossibles.size();
            Coup* coupChoisi = coupsPossibles[indexCoupChoisi];

            // Jouer le coup choisi
            plateau.jouerCoup(*coupChoisi);

            // Nettoyer la mémoire des coups possibles
            for (Coup* coup : coupsPossibles) {
                delete coup;
            }

            // Notifier les observateurs
            EvenementHive evt("Coup joué par l'IA pour le joueur " + getNom() + "\n");
            notifierObservers(evt);
        }
        */
    };


} // namespace JeuHive
