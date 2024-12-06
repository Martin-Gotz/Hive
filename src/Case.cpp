#include "../include/Case.h"

using namespace JeuHive;
using namespace std;

string JeuHive::Case::getString(int taille_str) const
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
	str_case.append(string(taille_str - str_case.size(), ' '));
	return str_case;
}
