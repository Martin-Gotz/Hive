#pragma once
#include "Coordonnee.h"
#include "Joueur.h"
#include "Plateau.h"
#include <vector>

namespace Hive {
	class Piece
	{
	private:
		Coordonnee& c;
		string name;
		bool estPlacee;
	public:
		string getName() const { return name; }
		Coordonnee getCoord() const { return c; }
	};

	class Reine : Piece
	{
	private :
		bool Surrounded;
	public:
		bool deplacementpossible(Plateau& plateau);
		vector<Case*> mouvementPossibles(Plateau& plateau);
		bool IsSurrounded() const { return Surrounded; }
	};

	class Scarabee : Piece {
		bool deplacementPossible(Plateau& plateau);
		Case& mouvementPossibles(Plateau& plateau);
	};

	class Araignee : Piece {
		bool deplacementPossible(Plateau& plateau);
		Case& mouvementPossibles(Plateau& plateau);
	};

	class Sauterelle : Piece {
		bool deplacementPossible(Plateau& plateau);
		Case& mouvementPossibles(Plateau& plateau);
	};

	class Fourmi : Piece {
		bool deplacementPossible(Plateau& plateau);
		Case& mouvementPossibles(Plateau& plateau);
	};

	class Moustique : Piece {
		bool deplacementPossible(Plateau& plateau);
		Case& mouvementPossibles(Plateau& plateau);
	};

	class Coccinelle : Piece {
		bool deplacementPossible(Plateau& plateau);
		Case& mouvementPossibles(Plateau& plateau);
	};
}

