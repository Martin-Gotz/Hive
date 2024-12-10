#pragma once
#include "MainPiece.h"
#include "Coup.h"
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
        Joueur(string nom) : nom(nom) {} // Constructeur temporaire
        Joueur(string nom, TypeJoueur type, Couleur couleur);
        string getNom() const { return nom; }
        // Méthodes principales
        void jouerCoup(Coup& coup);
        void placerPiece(Piece& piece, Coordonnee c, Plateau& plateau);
        void prendrePiece(Piece& piece);

        Couleur getCouleur() const { return couleur; }
        const MainPiece& getMain() const { return main; }
        TypeJoueur getType() const { return type; }
        // Ajouter une pièce à la main
        void ajouterPieceMain(Piece piece);

        void afficher(ostream& f) const;
        ResumeJoueur resumer() const;
    };
    ostream& operator<<(ostream& f, const Joueur& j);


} // namespace JeuHive
