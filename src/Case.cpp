#include "../include/Case.h"

using namespace JeuHive;
using namespace std;

string JeuHive::Case::getString() const
{
	string str_case = "";
	for (const Piece* piece : pieces) {
		if (piece->GetCouleur() == BLANC) {
			str_case.append("b");
		}
		else {
			str_case.append("n");
		}
		str_case.append(piece->getSymbole());
	}
	return str_case;

	/*
	// la couleur ajoute 9 caractères invisibles
	string couleur;
	cout << "\033[31mCeci est un texte rouge\033[0m\n";
	string str_case = "";
	for (const Piece* piece : pieces) {
		if (piece == getDessus()) {
			if (piece->GetCouleur() == BLANC) {
				couleur = "[36m";	// cyan
			}
			else {
				couleur = "[35m";	// magenta
			}
		}
		else{
			if (piece->GetCouleur() == BLANC) {
				couleur = "[34m";	// bleu
			}
			else {
				couleur = "[31m";	// rouge
			}
		}

		str_case.append("\033");
		str_case.append(couleur);
		str_case.append(piece->getSymbole());
		str_case.append("\033[0m");
	}
	return str_case;
	*/
}
