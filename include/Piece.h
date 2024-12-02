#pragma once
#include <vector>
#include "Enums.h"
#include <string>

using namespace std;

namespace Hive {

	class Piece
	{
	private:
		bool estPlacee;
		Couleur couleur;

	public:
		Piece(Couleur c) : estPlacee(false), couleur(c) {}

		bool GetestPlacee() const { return estPlacee; }
		Couleur GetCouleur() const { return couleur; }

		virtual string getSymbole() const = 0;	// une lettre pour afficher dans la console

		//virtual vector<Coordonnee*> mouvementsPossibles(Plateau& plateau, Coordonnee& coo) const = 0;
		//bool deplacementpossible(Plateau& plateau, Coordonnee& coo) const;
	};

	class Abeille : public Piece
	{
	public:
		Abeille(Couleur c) : Piece(c) {}

		string getSymbole() const override { return "A"; }
		virtual ~Abeille() = default;
		//vector<Coordonnee*> mouvementsPossibles(Plateau& plateau, Coordonnee& coo) const override;
		//vector<Coordonnee*> mouvementsPossibles(Plateau& plateau, Coordonnee& coo) const override;
		//bool isSurrounded(Plateau& plateau, Coordonnee& coo) const;

		// destructeur virtuel pour permettre le polymorphisme
	};

	class Scarabee : public Piece {
	public:
		Scarabee(Couleur c) : Piece(c) {}
		virtual ~Scarabee() = default;
		string getSymbole() const override { return "S"; }

		//vector<Coordonnee*> mouvementsPossibles(Plateau& plateau, Coordonnee& coo) const override;
	};

	class Araignee : public Piece {
	public:
		Araignee(Couleur c) : Piece(c) {}
		virtual ~Araignee() = default;
		string getSymbole() const override { return "a"; }
		//vector<Coordonnee*> mouvementsPossibles(Plateau& plateau, Coordonnee& coo) const override;
	};

	class Sauterelle : public Piece {
	public:
		Sauterelle(Couleur c) : Piece(c) {}
		virtual ~Sauterelle() = default;
		string getSymbole() const override { return "s"; }
		//vector<Coordonnee*> mouvementsPossibles(Plateau& plateau, Coordonnee& coo) const override;
	};

	class Fourmi : public Piece {
	public:
		Fourmi(Couleur c) : Piece(c) {}
		virtual ~Fourmi() = default;
		string getSymbole() const override { return "F"; }
		//vector<Coordonnee*> mouvementsPossibles(Plateau& plateau, Coordonnee& coo) const override;
	};

	class Moustique : public Piece {
	public:
		Moustique(Couleur c) : Piece(c) {}
		virtual ~Moustique() = default;
		string getSymbole() const override { return "M"; }
		//vector<Coordonnee*> mouvementsPossibles(Plateau& plateau, Coordonnee& coo) const override;
	};


	class Coccinelle : public Piece {
	public:
		Coccinelle(Couleur c) : Piece(c) {}
		virtual ~Coccinelle() = default;
		string getSymbole() const override { return "C"; }
		//vector<Coordonnee*> mouvementsPossibles(Plateau& plateau, Coordonnee& coo) const override;
	};
}

