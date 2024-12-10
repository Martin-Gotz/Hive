#pragma once
#include "Enums.h"
//#include "Piece.h"
//#include "Coordonnee.h"
//#include "Joueur.h"
#include <string>

using namespace std;

namespace JeuHive {

	class Coup
	{
	private:
		string test;
		//Piece* piece;
		//Coordonnee cooDestination;
		//Joueur joueur;
	public:
		Coup(string coup) : test(coup) {} // Constructeur temporaire
		/*
		Coup(Piece* piece, Coordonnee& cooDestination, Joueur& joueur) : piece(piece),
			cooDestination(cooDestination), joueur(joueur) {}

		virtual bool estPlacement() const { return false; }
		virtual bool estDeplacement() const { return false; }

		Piece* getPiece() const { return piece; }
		Coordonnee getCooDestination() const { return cooDestination; }
		const Joueur& getJoueur() const { return joueur; }
		*/

		// classe idéalement abstraite mais aucune méthode à abstraire :(
	};

	/*
	class CoupPlacement : public Coup {
	public:
		bool estPlacement() const override { return true; }

		CoupPlacement(Piece* piece, Coordonnee& cooDestination,
			Joueur& joueur) : Coup(piece, cooDestination, joueur) {}
	};


	class CoupDeplacement : public Coup {
	private:
		Coordonnee cooOrigine;
	public:
		bool estDeplacement() const override { return true; }

		CoupDeplacement(Piece* piece, Coordonnee& cooOrigine, Coordonnee& cooDestination, 
			Joueur& joueur) : Coup(piece, cooDestination, joueur), cooOrigine(cooOrigine) {}

		Coordonnee getCooOrigine() const { return cooOrigine; }
	};
	*/
}
