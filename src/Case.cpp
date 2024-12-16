#include "../include/Case.h"
#include "../include/Exceptions.h"

using namespace JeuHive;
using namespace std;

string Case::getString() const
{
	string str_case = "";
	for (const Piece* piece : pieces) {
		if (piece != nullptr) {
			try {
				ResumePiece resumePiece = piece->resumer();
				str_case.append(resumePiece.symbole);
				//str_case.append(resumePiece.couleur);
				//str_case.append(piece->getSymbole());
				//str_case.append(piece->getCouleur() == BLANC ? "b" : "n");
			}
			catch (const HiveException& e) {
				std::cerr << "Erreur dans getSymbole(): " << e.getInfo() << std::endl;
			}
		}
		else {
			std::cerr << "Pointeur nullptr dans pieces" << std::endl;
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
