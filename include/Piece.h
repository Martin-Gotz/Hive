#pragma once
#include "Coordonnee.h"
#include "Joueur.h"
#include "Plateau.h"
#include <vector>

namespace Hive {
	class Piece
	{
	private:
		Coordonnee c;
		string name;
		bool estPlacee;
	public:
		Piece(string nom) : name(nom), estPlacee(0), c(0,0) {}
		string getName() const { return name; }
		Coordonnee getCoord() const { return c; }
	};

	class Reine : Piece
	{
	private :
		bool Surrounded;
	public:
		Reine() : Piece("Reine"), Surrounded(0) {}
		bool deplacementpossible(Plateau& plateau);
		vector<Case*> mouvementPossibles(Plateau& plateau);
		bool IsSurrounded() const { return Surrounded; }
	};

	class Scarabee : Piece {
		Scarabee() : Piece("Scarabee") {}
		bool deplacementPossible(Plateau& plateau);
		Case& mouvementPossibles(Plateau& plateau);
	};

	class Araignee : Piece {
		Araignee() : Piece("Araignee") {}
		bool deplacementPossible(Plateau& plateau);
		Case& mouvementPossibles(Plateau& plateau);
	};

	class Sauterelle : Piece {
		Sauterelle() : Piece("Sauterelle") {}
		bool deplacementPossible(Plateau& plateau);
		Case& mouvementPossibles(Plateau& plateau);
	};

	class Fourmi : Piece {
		Fourmi() : Piece("Fourmi") {}
		bool deplacementPossible(Plateau& plateau);
		Case& mouvementPossibles(Plateau& plateau);
	};

	class Moustique : Piece {
		Moustique() : Piece("Moustique") {}
		bool deplacementPossible(Plateau& plateau);
		Case& mouvementPossibles(Plateau& plateau);
	};


	class Coccinelle : Piece {
		Coccinelle() : Piece("Coccinelle") {}
		bool deplacementPossible(Plateau& plateau);
		Case& mouvementPossibles(Plateau& plateau);
	};
}

