#pragma once
#include "Coordonnee.h"
#include "Piece.h"
#include <vector>
#include <iostream>

using namespace std;
namespace Hive {
	class Case
	{
	private:
		Coordonnee &c;
		vector<Piece>& pieces;
		bool occuppee;
	public:
		void ajouterPiece(Piece& piece);
		void retirerPiece(Piece& piece);
		bool getOccuppee() const { return occuppee; }
	};
}
