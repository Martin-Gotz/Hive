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
		// en fait il faut pouvoir acc�der aux pi�ces d'en dessous pour afficher le plateau, d'o� la suppression du stack
		vector<const Piece*> pieces;
	public:
		const Coordonnee& getCoo() const { return coo; }
		void ajouterPiece(const Piece& piece) { pieces.push_back(&piece); }
		void retirerPiece() { pieces.pop_back(); }
		const Piece* getDessus() const { return pieces.back(); }
		const vector<const Piece*>& getPieces() const { return pieces; }
		bool estVide() const { return pieces.empty(); }
		Case(const Coordonnee& coo) : coo(coo) {}
	};
}

// Case* getCaseByCoord(Coordonnee& c, const Plateau& p)  d�plac� dans la classe plateau
// vector<Case*> getVoisins(Plateau& plateau) const;      pareil
// car on ne peut pas include plateau.h dans case.h, �a ferait une inclusion en boucle