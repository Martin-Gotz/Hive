#pragma once
#include "Coordonnee.h"
#include "Plateau.h"
#include "Case.h"
namespace Hive {


	// la pièce doit appartenir à un joueur
	class Joueur;

	enum Couleur {Blanc, Noir };

	class Piece
	{
	private:
		Coordonnee coord;
		Couleur couleur;
		bool estPlace;
		Joueur joueur;
	public:
		Coordonnee getCoord() const { return coord; }
		bool getEstPlace() const { return estPlace; }
		Couleur getCouleur() const {return couleur;}
		Piece& operator=(const Piece insecte);
	};

	class Reine : Piece
	{
	private:
		bool Surrounded;
	public:
		bool deplacementPossible(Plateau& plateau);
		Case* mouvementsValides(Plateau& plateau);
		bool IsSurrounded() const;
	};

	class Scarabee : Piece {
	public:
		bool deplacementPossible(Plateau& plateau);
		Case* mouvementsValides(Plateau& plateau);
	};

	class Araignee : Piece {
	public:		
		bool deplacementPossible(Plateau& plateau);
		Case* mouvementsValides(Plateau& plateau);
	};

	class Sauterelle : Piece {
	public:
		bool deplacementPossible(Plateau& plateau);
		Case* mouvementsValides(Plateau& plateau);
	};

	class Fourmi : Piece {
	public:
		bool deplacementPossible(Plateau& plateau);
		Case* mouvementsValides(Plateau& plateau);
	};

	class Moustique : Piece {
	public:		
		bool deplacementPossible(Plateau& plateau);
		Case* mouvementsValides(Plateau& plateau);
	};

	class Coccinnelle : Piece {
	public:
		bool deplacementPossible(Plateau& plateau);
		Case* mouvementsValides(Plateau& plateau);
	};
}



