#include "../include/Case.h"
#include "../include/Exceptions.h"

using namespace JeuHive;
using namespace std;

string Case::toString() const
{
	string str_case;

	for (const Piece* piece : pieces) {
		if (!piece) {
			cerr << "Erreur : pièce null dans la case." << endl;
			continue;
		}

		try {
			str_case.append(piece->toString());
		}
		catch (const HiveException& e) {
			cerr << "Erreur lors de la génération de la représentation textuelle : " << e.getInfo() << endl;
		}
	}

	return str_case;


	/*
	// la couleur ajoute 9 caractères invisibles
	string couleur;
	cout << "\033[31mCeci est un texte rouge\033[0m\n";
	string str_case = "";
	for (const Piece* piece : pieces) {
		if (piece == getDessus()) {
			if (piece->getCouleur() == BLANC) {
				couleur = "[36m";	// cyan
			}
			else {
				couleur = "[35m";	// magenta
			}
		}
		else{
			if (piece->getCouleur() == BLANC) {
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

ResumeCase Case::resumer() const {
	ResumeCase resume;
	resume.q = coo.get_q();
	resume.r = coo.get_r();

	for (const auto& piece : pieces) {
		if (piece) {
			resume.pieces.push_back(piece->resumer());
		}
	}

	return resume;
}


ostream& JeuHive::operator<<(ostream& os, const Case& c)
{
	os << c.toString();
	return os;
}