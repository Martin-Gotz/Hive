#pragma once
#include <vector>
#include "Enums.h"

namespace Hive {
	class Piece
	{
	private:
		bool estPlacee;
		Couleur couleur;

	public:
		Piece(Couleur c) : estPlacee(false), couleur(c) {}
		bool GetestPlacee() const { return estPlacee; }
		bool GetCouleur() const { return couleur; }
		//virtual vector<Coordonnee*> mouvementsPossibles(Plateau& plateau, Coordonnee& coo) const = 0;
		//bool deplacementpossible(Plateau& plateau, Coordonnee& coo) const;
	};

	class Abeille : public Piece
	{
	public:
		Abeille(Couleur c) : Piece(c) {}
		//vector<Coordonnee*> mouvementsPossibles(Plateau& plateau, Coordonnee& coo) const override;
		//bool isSurrounded(Plateau& plateau, Coordonnee& coo) const;
	};

	class Scarabee : public Piece {
		Scarabee(Couleur c) : Piece(c) {}
		//vector<Coordonnee*> mouvementsPossibles(Plateau& plateau, Coordonnee& coo) const override;
	};

	class Araignee : public Piece {
		Araignee(Couleur c) : Piece(c) {}
		//vector<Coordonnee*> mouvementsPossibles(Plateau& plateau, Coordonnee& coo) const override;
	};

	class Sauterelle : public Piece {
		Sauterelle(Couleur c) : Piece(c) {}
		//vector<Coordonnee*> mouvementsPossibles(Plateau& plateau, Coordonnee& coo) const override;
	};

	class Fourmi : public Piece {
		Fourmi(Couleur c) : Piece(c) {}
		//vector<Coordonnee*> mouvementsPossibles(Plateau& plateau, Coordonnee& coo) const override;
	};

	class Moustique : public Piece {
		Moustique(Couleur c) : Piece(c) {}
		//vector<Coordonnee*> mouvementsPossibles(Plateau& plateau, Coordonnee& coo) const override;
	};


	class Coccinelle : public Piece {
		Coccinelle(Couleur c) : Piece(c) {}
		//vector<Coordonnee*> mouvementsPossibles(Plateau& plateau, Coordonnee& coo) const override;
	};
}

