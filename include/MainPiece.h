#pragma once
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <ostream>
#include "Piece.h"



using namespace std;
namespace JeuHive {
    class MainPiece
    {
    private:
        vector<Piece*> Pieces;
        bool estVide;

    public:
        // Constructeur
        MainPiece() : estVide(true) {}

        void ajouterPiece(Piece* piece);
        void retirerPiece(Piece* piece);
        bool getEstVide() const { return estVide; }
        vector<Piece*> getPieces() const { return Pieces; }

        // Itérateur
        vector<Piece*>::iterator begin() { return Pieces.begin(); }
        vector<Piece*>::iterator end() { return Pieces.end(); }

        vector<Piece*>::const_iterator begin() const { return Pieces.begin(); }
        vector<Piece*>::const_iterator end() const { return Pieces.end(); }

        // Affichage
        void afficher(ostream& os) const;
        ResumeMain resumer() const;
        friend ostream& operator<<(ostream& os, const MainPiece& partie);
    };
}
