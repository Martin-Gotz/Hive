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
		virtual vector<Case*> mouvementPossibles(Plateau& plateau) const = 0;
		virtual bool deplacementpossible(Plateau& plateau) const =0;
	};

	class Reine : Piece
	{
	private :
		bool Surrounded;
	public:
		Reine() : Piece("Reine"), Surrounded(0) {}
		bool IsSurrounded() const { return Surrounded; }
		vector<Case*> mouvementPossibles(Plateau& plateau) const override;
		bool deplacementpossible(Plateau& plateau) const override;
	};

	class Scarabee : Piece {
		Scarabee() : Piece("Scarabee") {}
		bool deplacementpossible(Plateau& plateau) const override;
		vector<Case*> mouvementPossibles(Plateau& plateau) const override;
	};

	class Araignee : Piece {
		Araignee() : Piece("Araignee") {}
		bool deplacementpossible(Plateau& plateau) const override;
		vector<Case*> mouvementPossibles(Plateau& plateau) const override;
	};

	class Sauterelle : Piece {
		Sauterelle() : Piece("Sauterelle") {}
		bool deplacementpossible(Plateau& plateau) const override;
		vector<Case*> mouvementPossibles(Plateau& plateau) const override;
	};

	class Fourmi : Piece {
		Fourmi() : Piece("Fourmi") {}
		bool deplacementpossible(Plateau& plateau) const override;
		vector<Case*> mouvementPossibles(Plateau& plateau) const override;
	};

	class Moustique : Piece {
		Moustique() : Piece("Moustique") {}
		bool deplacementpossible(Plateau& plateau) const override;
		vector<Case*> mouvementPossibles(Plateau& plateau) const override;
	};


	class Coccinelle : Piece {
		Coccinelle() : Piece("Coccinelle") {}
		bool deplacementpossible(Plateau& plateau) const override;
		vector<Case*> mouvementPossibles(Plateau& plateau) const override;
	};
}

