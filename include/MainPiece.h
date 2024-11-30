#pragma once
#include <vector>
#include "Piece.h"
#include <stdio.h>
#include <stdlib.h>
#include <ostream>

using namespace std;
namespace Hive {
	class MainPiece
	{
	private:
		vector<Piece> Pieces;
		bool estVide;
	public:
		void AjouterPiece(Piece& piece);
		void RetirerPiece(Piece& piece);
		bool getEstVide() const { return estVide; }
		vector<Piece> getPieces() const { return Pieces; }
	};
}
