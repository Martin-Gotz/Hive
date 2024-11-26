#pragma once
#include "Piece.h"
#include "Case.h"
#include "Joueur.h"

namespace Hive {

	enum action {placement, deplacement};

	class Coup
	{
	private:
		action actions;
		Piece& piece;
		Case& caseOrigine;
		Case& caseDestination;
		Joueur& joueur;
	public:

	};
}
