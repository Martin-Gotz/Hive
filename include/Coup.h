#pragma once
#include "Enums.h"
#include <string>

using namespace std;

namespace JeuHive {

	class Coup
	{
	private:
		string nomCoup;
		/*
		Action actions;
		Piece& piece;
		Case& caseOrigine;
		Case& caseDestination;
		Joueur& joueur;
		*/
	public:
		Coup(string s) : nomCoup(s) {};
	};
}
