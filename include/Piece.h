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
		string nom;
		string symbole;

	public:
		// on garde l'opérateur == par défault, qui apparemment ne peut pas être défini avec un =default
		// il compare l'adresse mémoire des pieces (pas de comparaison d'attributs)

		Piece(Couleur c, string n, string s) : couleur(c), nom(n), symbole(s) {}

		Couleur getCouleur() const { return couleur; }

		string getNom() const { return nom; };
		string getSymbole() const { return symbole; };	// une lettre pour afficher dans la console

		virtual bool estAbeille() const { return false; }
		// redéfinie uniquement dans la classe Abeille

		virtual set<Coordonnee> ensembleDeplacementPossibles(const Plateau& plateau, const Coordonnee& coo) const = 0;

		// faire la concaténation entre symbole et couleur
		// Methode utilitaire pour afficher l'etat de la partie
		void afficher(ostream& os) const;
		ResumePiece resumer() const;
	};		
	ostream& operator<<(ostream& os, const Piece& piece);


	class Abeille : public Piece
	{
	public:
		Abeille(Couleur c) : Piece(c, "Abeille", "r") {}

		virtual ~Abeille() = default;

		bool estAbeille() const override { return true; }
		set<Coordonnee> ensembleDeplacementPossibles(const Plateau& plateau, const Coordonnee& coo) const override;
		// destructeur virtuel pour permettre le polymorphisme
	};

	class Scarabee : public Piece {
	public:
		Scarabee(Couleur c) : Piece(c, "Scarabee", "s") {}
		virtual ~Scarabee() = default;

		set<Coordonnee> ensembleDeplacementPossibles(const Plateau& plateau, const Coordonnee& coo) const override;
	};

	class Araignee : public Piece {
	public:
		Araignee(Couleur c) : Piece(c, "Araignee", "a") {}
		virtual ~Araignee() = default;
		
		set<Coordonnee> ensembleDeplacementPossibles(const Plateau& plateau, const Coordonnee& coo) const override;
	};

	class Sauterelle : public Piece {
	public:
		Sauterelle(Couleur c) : Piece(c, "Sauterelle", "c") {}
		virtual ~Sauterelle() = default;

		set<Coordonnee> ensembleDeplacementPossibles(const Plateau& plateau, const Coordonnee& coo) const override;
	};

	class Fourmi : public Piece {
	public:
		Fourmi(Couleur c) : Piece(c, "Fourmi", "f") {}
		virtual ~Fourmi() = default;
		
		set<Coordonnee> ensembleDeplacementPossibles(const Plateau& plateau, const Coordonnee& coo) const override;
	};

	class Moustique : public Piece {
	public:
		Moustique(Couleur c) : Piece(c, "Moustique", "m") {}
		virtual ~Moustique() = default;
		
		set<Coordonnee> ensembleDeplacementPossibles(const Plateau& plateau, const Coordonnee& coo) const override;
	};

	class Coccinelle : public Piece {
	public:
		Coccinelle(Couleur c) : Piece(c, "Coccinelle", "b") {}
		virtual ~Coccinelle() = default;
		
		set<Coordonnee> ensembleDeplacementPossibles(const Plateau& plateau, const Coordonnee& coo) const override;
	};
}

