#pragma once
#include <iostream>
#include <vector>
#include "Coordonnee.h"
#include "Piece.h"
#include <stack>


using namespace std;


namespace Hive {
	class Case
	{
	private:
		Coordonnee coo;
		stack<const Piece*> pieces;
	public:
		const Coordonnee& getCoo() const { return coo; }
		void ajouterPiece(const Piece& piece) { pieces.push(&piece); }
		void retirerPiece() { pieces.pop(); }
		const Piece* getDessus() const { return pieces.top(); }
	};
}

// Case* getCaseByCoord(Coordonnee& c, const Plateau& p)  déplacé dans la classe plateau
// vector<Case*> getVoisins(Plateau& plateau) const;      pareil
// car on ne peut pas include plateau.h dans case.h, ça ferait une inclusion en boucle