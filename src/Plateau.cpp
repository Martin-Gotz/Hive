#include "../include/Plateau.h"

using namespace Hive;
#include <algorithm>	// pour le set_difference de EnsemblePlacementPossibles
#include <array>


void Plateau::ajouterPieceSurCoo(const Piece& piece, const Coordonnee& coo) {

	Case* case_sur_coo = getCaseDeCoo(coo);
	
	if (case_sur_coo == nullptr) {
		Case* nouv_case = new Case(coo);
		Cases.insert(make_pair(coo, nouv_case));
		nouv_case->ajouterPiece(piece);
	}
	else {
		case_sur_coo->ajouterPiece(piece);
	}
}

void Plateau::retirerPieceDeCoo(const Coordonnee& coo) {
	Case* case_sur_coo = getCaseDeCoo(coo);

	if (case_sur_coo == nullptr) {
		throw HiveException("Aucune pièce ne se trouve à ces coordonnées");
	}
	else {
		case_sur_coo->retirerPiece();

		if (case_sur_coo->estVide()) {
			Cases.erase(coo);
			delete case_sur_coo;
		}
	}
}

Case* Plateau::getCaseDeCoo(const Coordonnee& coo) const {
	// renvoie nullptr si rien n'est trouvé
	unordered_map<Coordonnee, Case*>::const_iterator case0 = Cases.find(coo);

	if (case0 != Cases.end()) {
		return case0->second;
	}
	else {
		return nullptr;
	}

}


/*
ostream& operator<<(ostream& f, const Plateau& p)
	{
		f << "Nombre de cellules : " << p.getNombreCases() << "\n";
		int i = 0;
		unordered_map<Coordonnee, Case*>::const_iterator itr;
		for (itr = p.getCases().begin();
			itr != p.getCases().end(); itr++)
		{
			f << "Case numéro : " << i++ << " Coordonnées : (" << itr->first.get_q() << itr->first.get_r() << ")\n";
		}
		return f;
	}

*/

set<Coordonnee> Plateau::EnsemblePlacementPossibles(const Piece& piece) const
{
	// les placements possibles seront : 
	// ceux qui seront en contact avec une autre case
	// En fait non: ne tient pas en compte l'abeille (ce sera géré plus haut)
	// précédemment : "au 5 ème tour, on doit s'assurer que la reine a été placée"
	// les cases déjà occupées ne sont pas éligibles

	// explication de l'algorithme:
	// On crée un ensemble de case voisinsBonneCouleur qui représente l'ensembles des voisins de chaque pièces 
	// de la même couleur que piece.
	// pareil avec voisinsMauvaiseCouleur mais avec la couleur opposée
	// Les cases sur lesquelles on peut placer la pièce sont les cases voisines d'une pièce de la même couleur, mais pas
	// voisines d'une pièce de la couleur opposée. Ce résultat s'obtient en prenant la différence des deux ensembles
	// avec set_difference

	set<Coordonnee> voisinsBonneCouleur;		// voisins des pièces de la même couleur que piece
	set<Coordonnee> voisinsMauvaiseCouleur;	// voisins des pièces de la couleur opposée piece
	const Case* case_ptr;	
	const Piece* piece_dessus;
	vector<Coordonnee> coo_voisines;
	Coordonnee coo_case;
	unordered_map<Coordonnee, Case*>::const_iterator itr;

	for (itr = Cases.begin();
		itr != Cases.end(); itr++)
	{
		coo_case = itr->first;
		case_ptr = itr->second;

		coo_voisines = coo_case.getVoisins();
		piece_dessus = case_ptr->getDessus();

		for (auto coo_voisine : coo_voisines) {
			if (piece_dessus->GetCouleur() == piece.GetCouleur()) {
				voisinsBonneCouleur.insert(coo_voisine);
			}
			else {
				voisinsMauvaiseCouleur.insert(coo_voisine);
			}
		}
	}

	set<Coordonnee> difference;

	set_difference(
		voisinsBonneCouleur.begin(), voisinsBonneCouleur.end(), voisinsMauvaiseCouleur.begin(), voisinsMauvaiseCouleur.end(),
		inserter(difference, difference.begin()));

	return difference;
}


vector<Case*> Plateau::getVoisinsDeCase(const Case& case0) const
// on ne peut pas écrire case car c'est un mot clé
{
	vector<Case*> voisins;
	vector<Coordonnee> coo_voisines = case0.getCoo().getVoisins();
	Case* case_voisine;

	for (auto coo_voisine : coo_voisines) {
		case_voisine = getCaseDeCoo(coo_voisine);// Si une case se trouve sur la coordonnee voisine
		if (case_voisine != nullptr) {
			voisins.push_back(case_voisine);
		}	

	}
	return voisins;

}

ostream& operator<<(ostream& f, const Plateau& p)
{
	// résultat de l'affichage:
	// Pour chaque hexagone, la pile de pièce est affichée: un pièce est représentée par un entier(0 pour BLANC, 1 pour
	// NOIR) et d'un caractère pour le type d'insecte:
	// A:abeille, a:araignée, S:scarabée, s:sauterelle, f:fourmi, m: moustique, c:coccinelle


	// pour afficher dans la console le plateau, peut convertir les coos hexagonales en une hauteur y(1 pour chaque ligne)
	// et une position x(un certain nombre de caractères)
	// Pour s'assurer qu'il y ait assez de place, la convertion sera linéaire et se fera de cette manière:
	// y=2q+r, x=r
	// les lignes ne s'afficheront bien que si le jeu n'est pas trop étendu sur l'axe gauche-droite, et on ne peut rien y
	// faire

	if (p.estVide()) {
		return f;
	}

	const int taille_str = 8;	// la taille que prendra chaque hexagone à afficher
	const string str_espaces = string(taille_str, ' ');

	//on commence par calculer les x et y min et max pour gacher le moins de place possible
	int min_y = 10000;  // on suppose qu'aucune case ne sera à de telles coordonnées
	int max_y = -10000;
	int min_x = 10000; 
	int max_x = -10000; 

	Coordonnee coo_case;
	int x_case;
	int y_case;

	for (auto paire : p.getCases()) {
		coo_case = paire.first;
		x_case = coo_case.get_r();
		y_case = coo_case.get_r() + 2*coo_case.get_q();
		min_y = min(min_y, y_case);
		max_y = max(max_y, y_case);
		min_x = min(min_x, x_case);
		max_x = max(max_x, x_case);

	}
	int taille_x = max_x - min_x + 1;
	int taille_y = max_y - min_y + 1;

	// tableau bidimensionnel rempli de str_espaces
	vector<vector<string>> tab = vector<vector<string>>(taille_y, vector<string>(taille_x, str_espaces)); 
	Case* case0;
	string str_case;
	for (auto paire : p.getCases()) {
		coo_case = paire.first;
		case0 = paire.second;

		x_case = coo_case.get_r();
		y_case = coo_case.get_r() + 2 * coo_case.get_q();

		str_case = "";
		for (const Piece* piece : case0->getPieces()) {
			if (piece->GetCouleur() == BLANC) {
				str_case.append("0");
			}
			else {
				str_case.append("1");
			}
			str_case.append(piece->getSymbole());
		}
		str_case.append(string(taille_str - str_case.size(), ' '));
		/*
		while (str_case.size() < taille_str) {
			str_case.append(" ");
		}
		*/
		tab.at(y_case).assign(x_case, str_case);
	}

	for (int i = taille_y - 1; i >= 0; i--) {		// boucle inversée car on print de haut en bas
		for (int j = 0; j < taille_x; j++) {
			f << tab.at(i).at(j);
		}
		f << "\n";
	}

	return f;

}
