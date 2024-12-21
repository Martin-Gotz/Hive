#pragma once
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <ostream>
#include "FabriquePiece.h"



using namespace std;
namespace JeuHive {
    class MainPiece
    {
    private:
        vector<Piece*> pieces;

    public:
        // Constructeur

        void ajouterPiece(Piece* piece);
        void retirerPiece(Piece* piece);
        bool estVide() const { return pieces.empty(); }
        vector<Piece*> getPieces() const { return pieces; }

        // Itérateur
        vector<Piece*>::iterator begin() { return pieces.begin(); }
        vector<Piece*>::iterator end() { return pieces.end(); }

        vector<Piece*>::const_iterator begin() const { return pieces.begin(); }
        vector<Piece*>::const_iterator end() const { return pieces.end(); }

        // Autres méthodes
        ResumeMain resumer() const;
    };
}
