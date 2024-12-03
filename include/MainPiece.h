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
		void AjouterPiece(Piece& piece);
		void RetirerPiece(Piece& piece);
		bool getEstVide() const { return estVide; }
		vector<Piece*> getPieces() const { return Pieces; }
	};
}
