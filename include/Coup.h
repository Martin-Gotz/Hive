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
		const Piece* piece;
		int tour;
	public:
		Coup(const Piece* piece, const Coordonnee& cooDestination, int tour) 
			: piece(piece), cooDestination(cooDestination), tour(tour) {}

		virtual Coup* clone() const = 0;

		const Piece* getPiece() const { return piece; }
		int getTour() const { return tour; }
		Coordonnee getCooDestination() const { return cooDestination; }
	};


	class CoupPlacement : public Coup {
	public:
		CoupPlacement(const Piece* piece, const Coordonnee& cooDestination, int tour) : Coup(piece, cooDestination, tour) {}

		Coup* clone() const override {
			return new CoupPlacement(*this);
		}

	};


	class CoupDeplacement : public Coup {
	private:
		Coordonnee cooOrigine;
	public:
		CoupDeplacement(const Piece* piece, const Coordonnee& cooOrigine, const Coordonnee& cooDestination, int tour)
			: Coup(piece, cooDestination, tour), cooOrigine(cooOrigine) {}

		Coup* clone() const override {
			return new CoupDeplacement(*this);
		}

		Coordonnee getCooOrigine() const { return cooOrigine; }
	};
}
