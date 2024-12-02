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
		Couleur GetCouleur() const { return couleur; }

		virtual std::string getSymbole() const = 0;	// une lettre pour afficher dans la console

		//virtual vector<Coordonnee*> mouvementsPossibles(Plateau& plateau, Coordonnee& coo) const = 0;
		//bool deplacementpossible(Plateau& plateau, Coordonnee& coo) const;
	};

	class Abeille : public Piece
	{
	public:
		Abeille(Couleur c) : Piece(c) {}

		std::string getSymbole() const override { return "A"; }
		virtual ~Abeille() = default;
		//vector<Coordonnee*> mouvementsPossibles(Plateau& plateau, Coordonnee& coo) const override;
		//bool isSurrounded(Plateau& plateau, Coordonnee& coo) const;

		// destructeur virtuel pour permettre le polymorphisme
	};

	class Scarabee : public Piece {
	public:
		Scarabee(Couleur c) : Piece(c) {}
		virtual ~Scarabee() = default;
		std::string getSymbole() const override { return "S"; }

		//vector<Coordonnee*> mouvementsPossibles(Plateau& plateau, Coordonnee& coo) const override;
	};

	class Araignee : public Piece {
	public:
		Araignee(Couleur c) : Piece(c) {}
		virtual ~Araignee() = default;
		std::string getSymbole() const override { return "a"; }
		//vector<Coordonnee*> mouvementsPossibles(Plateau& plateau, Coordonnee& coo) const override;
	};

	class Sauterelle : public Piece {
	public:
		Sauterelle(Couleur c) : Piece(c) {}
		virtual ~Sauterelle() = default;
		std::string getSymbole() const override { return "s"; }
		//vector<Coordonnee*> mouvementsPossibles(Plateau& plateau, Coordonnee& coo) const override;
	};

	class Fourmi : public Piece {
	public:
		Fourmi(Couleur c) : Piece(c) {}
		virtual ~Fourmi() = default;
		std::string getSymbole() const override { return "F"; }
		//vector<Coordonnee*> mouvementsPossibles(Plateau& plateau, Coordonnee& coo) const override;
	};

	class Moustique : public Piece {
	public:
		Moustique(Couleur c) : Piece(c) {}
		virtual ~Moustique() = default;
		std::string getSymbole() const override { return "M"; }
		//vector<Coordonnee*> mouvementsPossibles(Plateau& plateau, Coordonnee& coo) const override;
	};


	class Coccinelle : public Piece {
	public:
		Coccinelle(Couleur c) : Piece(c) {}
		virtual ~Coccinelle() = default;
		std::string getSymbole() const override { return "c"; }
		//vector<Coordonnee*> mouvementsPossibles(Plateau& plateau, Coordonnee& coo) const override;
	};
}


