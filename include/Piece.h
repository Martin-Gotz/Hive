#pragma once
#include "Coordonnee.h"
#include "Joueur.h"
#include "Plateau.h"
#include <vector>

namespace Hive {
	class Piece
	{
	private:
		bool estPlacee;
	public:
		Piece() : estPlacee(false) {}
		virtual vector<Coordonnee*> mouvementsPossibles(Plateau& plateau, Coordonnee& coo) const = 0;
		bool deplacementpossible(Plateau& plateau, Coordonnee& coo) const;
	};

	class Abeille : public Piece
	{
	public:
		Abeille() {}
		vector<Coordonnee*> mouvementsPossibles(Plateau& plateau, Coordonnee& coo) const override;
		bool isSurrounded(Plateau& plateau, Coordonnee& coo) const;
	};

	class Scarabee : public Piece {
		Scarabee() {}
		vector<Coordonnee*> mouvementsPossibles(Plateau& plateau, Coordonnee& coo) const override;
	};

	class Araignee : public Piece {
		Araignee() {}
		vector<Coordonnee*> mouvementsPossibles(Plateau& plateau, Coordonnee& coo) const override;
	};

	class Sauterelle : public Piece {
		Sauterelle() {}
		vector<Coordonnee*> mouvementsPossibles(Plateau& plateau, Coordonnee& coo) const override;
	};

	class Fourmi : public Piece {
		Fourmi() {}
		vector<Coordonnee*> mouvementsPossibles(Plateau& plateau, Coordonnee& coo) const override;
	};

	class Moustique : public Piece {
		Moustique() {}
		vector<Coordonnee*> mouvementsPossibles(Plateau& plateau, Coordonnee& coo) const override;
	};


	class Coccinelle : public Piece {
		Coccinelle() {}
		vector<Coordonnee*> mouvementsPossibles(Plateau& plateau, Coordonnee& coo) const override;
	};
}

