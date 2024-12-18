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
	public:
		Coup(const Piece* piece, const Coordonnee& cooDestination) : piece(piece), cooDestination(cooDestination) {}

		virtual Coup* clone() const = 0;

		virtual bool estPlacement() const { return false; }
		virtual bool estDeplacement() const { return false; }

		const Piece* getPiece() const { return piece; }

		Coordonnee getCooDestination() const { return cooDestination; }
	};


	class CoupPlacement : public Coup {
	public:
		CoupPlacement(const Piece* piece, const Coordonnee& cooDestination) : Coup(piece, cooDestination) {}

		Coup* clone() const override {
			return new CoupPlacement(*this);
		}

		bool estPlacement() const override { return true; }

	};


	class CoupDeplacement : public Coup {
	private:
		Coordonnee cooOrigine;
	public:
		bool estDeplacement() const override { return true; }

		Coup* clone() const override {
			return new CoupDeplacement(*this);
		}

		CoupDeplacement(const Piece* piece, const Coordonnee& cooOrigine, const Coordonnee& cooDestination)
			: Coup(piece, cooDestination), cooOrigine(cooOrigine) {}

		Coordonnee getCooOrigine() const { return cooOrigine; }
	};
}
