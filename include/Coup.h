#pragma once
#include "Enums.h"
#include "Piece.h"
#include "Coordonnee.h"
#include <string>

using namespace std;

namespace JeuHive {

	class Coup {
	private:
		Coordonnee cooDestination;
	public:
		Coup(Coordonnee& cooDestination) : cooDestination(cooDestination) {}

		virtual bool estPlacement() const { return false; }
		virtual bool estDeplacement() const { return false; }

		Coordonnee getCooDestination() const { return cooDestination; }
	};


	class CoupPlacement : public Coup {
	private:
		Piece* piece;
	public:
		CoupPlacement(Piece* piece, Coordonnee& cooDestination) : piece(piece), Coup(cooDestination) {}

		bool estPlacement() const override { return true; }

		Piece* getPiece() const { return piece; }
	};


	class CoupDeplacement : public Coup {
	private:
		Coordonnee cooOrigine;
	public:
		bool estDeplacement() const override { return true; }

		CoupDeplacement(Coordonnee& cooOrigine, Coordonnee& cooDestination) 
			: Coup(cooDestination), cooOrigine(cooOrigine) {}

		Coordonnee getCooOrigine() const { return cooOrigine; }
	};
}
