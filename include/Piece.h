#pragma once
#include <vector>
#include "Enums.h"
#include <string>

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

		virtual string getSymbole() const = 0;	// une lettre pour afficher dans la console

		//virtual vector<Coordonnee*> mouvementsPossibles(Plateau& plateau, Coordonnee& coo) const = 0;
		//bool deplacementpossible(Plateau& plateau, Coordonnee& coo) const;
	};

	class Abeille : public Piece
	{
	public:
		Abeille(Couleur c) : Piece(c) {}

		string getSymbole() const { return "A"; }

		//vector<Coordonnee*> mouvementsPossibles(Plateau& plateau, Coordonnee& coo) const override;
		//bool isSurrounded(Plateau& plateau, Coordonnee& coo) const;
	};

	class Scarabee : public Piece {
		Scarabee(Couleur c) : Piece(c) {}

		string getSymbole() const { return "S"; }

		//vector<Coordonnee*> mouvementsPossibles(Plateau& plateau, Coordonnee& coo) const override;
	};

	class Araignee : public Piece {
		Araignee(Couleur c) : Piece(c) {}

		string getSymbole() const { return "a"; }
		//vector<Coordonnee*> mouvementsPossibles(Plateau& plateau, Coordonnee& coo) const override;
	};

	class Sauterelle : public Piece {
		Sauterelle(Couleur c) : Piece(c) {}

		string getSymbole() const { return "s"; }
		//vector<Coordonnee*> mouvementsPossibles(Plateau& plateau, Coordonnee& coo) const override;
	};

	class Fourmi : public Piece {
		Fourmi(Couleur c) : Piece(c) {}

		string getSymbole() const { return "F"; }
		//vector<Coordonnee*> mouvementsPossibles(Plateau& plateau, Coordonnee& coo) const override;
	};

	class Moustique : public Piece {
		Moustique(Couleur c) : Piece(c) {}

		string getSymbole() const { return "M"; }
		//vector<Coordonnee*> mouvementsPossibles(Plateau& plateau, Coordonnee& coo) const override;
	};


	class Coccinelle : public Piece {
		Coccinelle(Couleur c) : Piece(c) {}

		string getSymbole() const { return "c"; }
		//vector<Coordonnee*> mouvementsPossibles(Plateau& plateau, Coordonnee& coo) const override;
	};
}


