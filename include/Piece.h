#pragma once
#include <vector>
#include <set>
#include "Enums.h"
#include <string>
#include "Coordonnee.h"

using namespace std;

namespace JeuHive {

	class Plateau;
	class Case;

	class Piece
	{
	protected:
		Couleur couleur;

	public:
		// on garde l'opérateur == par défault, qui apparemment ne peut pas être défini avec un =default
		// il compare l'adresse mémoire des pieces (pas de comparaison d'attributs)

		Piece(Couleur c) : couleur(c) {}

		Couleur GetCouleur() const { return couleur; }

		virtual string getSymbole() const = 0;	// une lettre pour afficher dans la console

		virtual bool estAbeille() const { return false; }
		// redéfinie uniquement dans la classe Abeille



		virtual set<Coordonnee> ensembleDeplacementPossibles(const Plateau& plateau, const Coordonnee& coo) const = 0;
	};

	class Abeille : public Piece
	{
	public:
		Abeille(Couleur c) : Piece(c) {}

		string getSymbole() const override { return "A"; }
		virtual ~Abeille() = default;

		bool estAbeille() const override { return true; }
		set<Coordonnee> ensembleDeplacementPossibles(const Plateau& plateau, const Coordonnee& coo) const override;
		//bool isSurrounded(Plateau& plateau, Coordonnee& coo) const;

		// destructeur virtuel pour permettre le polymorphisme
	};

	class Scarabee : public Piece {
	public:
		Scarabee(Couleur c) : Piece(c) {}
		virtual ~Scarabee() = default;
		string getSymbole() const override { return "S"; }

		set<Coordonnee> ensembleDeplacementPossibles(const Plateau& plateau, const Coordonnee& coo) const override;
	};

	class Araignee : public Piece {
	public:
		Araignee(Couleur c) : Piece(c) {}
		virtual ~Araignee() = default;
		string getSymbole() const override { return "a"; }
		
		set<Coordonnee> ensembleDeplacementPossibles(const Plateau& plateau, const Coordonnee& coo) const override;
	};

	class Sauterelle : public Piece {
	public:
		Sauterelle(Couleur c) : Piece(c) {}
		virtual ~Sauterelle() = default;
		string getSymbole() const override { return "s"; }

		set<Coordonnee> ensembleDeplacementPossibles(const Plateau& plateau, const Coordonnee& coo) const override;
	};

	class Fourmi : public Piece {
	public:
		Fourmi(Couleur c) : Piece(c) {}
		virtual ~Fourmi() = default;
		string getSymbole() const override { return "F"; }
		
		set<Coordonnee> ensembleDeplacementPossibles(const Plateau& plateau, const Coordonnee& coo) const override;
	};

	class Moustique : public Piece {
	public:
		Moustique(Couleur c) : Piece(c) {}
		virtual ~Moustique() = default;
		string getSymbole() const override { return "M"; }
		
		set<Coordonnee> ensembleDeplacementPossibles(const Plateau& plateau, const Coordonnee& coo) const override;
	};


	class Coccinelle : public Piece {
	public:
		Coccinelle(Couleur c) : Piece(c) {}
		virtual ~Coccinelle() = default;
		string getSymbole() const override { return "C"; }
		
		set<Coordonnee> ensembleDeplacementPossibles(const Plateau& plateau, const Coordonnee& coo) const override;
	};
}

