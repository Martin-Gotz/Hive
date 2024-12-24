#pragma once
#include "MainPiece.h"
#include "Piece.h"
#include "Coordonnee.h"
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

        // Accesseurs
        string getNom() const { return nom; }
        Couleur getCouleur() const { return couleur; }
        const MainPiece& getMain() const { return main; }
        TypeJoueur getType() const { return type; }

        // Mutateurs
        void setCouleur(Couleur nouvelleCouleur) { couleur = nouvelleCouleur; }

        // Méthodes principales
        void remplirMain(const FabriquePiece& fabrique);
        void retirerPiece(Piece* piece);

        // Ajouter une pièce à la main
        void ajouterPieceMain(Piece* piece);

        bool operator==(Joueur* other) const {
            return (nom == other->nom && couleur == other->couleur);
        }

        ResumeJoueur resumer() const;
    };  

    class JoueurIA : public Joueur {
    public:
        JoueurIA(string nom) : Joueur(nom, IA) {
            std::srand(std::time(nullptr)); // Initialize random seed
        }
    };


} // namespace JeuHive
