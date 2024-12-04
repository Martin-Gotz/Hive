#include "../include/Plateau.h"

using namespace JeuHive;
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
		throw HiveException("Aucune pi�ce ne se trouve � ces coordonn�es");
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
	// renvoie nullptr si rien n'est trouv�
	// d'o� le choix de renvoi d'un pointeur
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
			f << "Case num�ro : " << i++ << " Coordonn�es : (" << itr->first.get_q() << itr->first.get_r() << ")\n";
		}
		return f;
	}

*/

size_t Plateau::getNombrePieces() const
{
	size_t resultat = 0;
	Case* case0;
	for (pair<Coordonnee, Case*> paire : Cases) {
		case0 = paire.second;
		resultat += case0->getNombrePieces();
	}
	return resultat;
}

set<Coordonnee> Plateau::ensemblePlacementsPossibles(const Piece& piece, int tour) const
{
	// les placements possibles devront respecter ces conditions: 
	// 1)  �tre seront en contact avec une pi�ce de m�me couleur mais pas avec la couleur oppos�e
	// 2) Si on en est au quatri�me tour et que la reine abeille n'est pas plac�e, il faut imp�rativement la placer
	// 3) les cases d�j� occup�es ne sont pas �ligibles
	//
	// Exceptions pour le premier tour:
	// Le premier joueur pose sa premi�re pi�ce en (0, 0)
	// le deuxi�me joueur du premier tour peut poser une pi�ce � cot� de (0, 0) m�me si leur couleur est incompatible


	// explication de l'algorithme:
	// On cr�e un ensemble de case voisinsBonneCouleur qui repr�sente l'ensembles des voisins de chaque pi�ces 
	// de la m�me couleur que piece.
	// pareil avec voisinsMauvaiseCouleur mais avec la couleur oppos�e
	// Les cases sur lesquelles on peut placer la pi�ce sont les cases voisines d'une pi�ce de la m�me couleur, mais pas
	// voisines d'une pi�ce de la couleur oppos�e. Ce r�sultat s'obtient en prenant la diff�rence des deux ensembles
	// avec set_difference

	if (piece.GetestPlacee()) {
		throw HiveException("La piece est deja placee");
	}

	set<Coordonnee> resultat;

	if (tour == 1) {
		if (estVide()) {
			resultat.insert(Coordonnee(0, 0));
		}
		else {
			for (Coordonnee voisin : Coordonnee(0, 0).getVoisins()) {
				resultat.insert(voisin);
			}
		}

		return resultat;
	}

	if (tour == 4 && !estAbeillePlacee(piece.GetCouleur())) {
		// commentaire au cas o� l'autre m�thode ne marche pas
		//const Abeille* ab = dynamic_cast<const Abeille*>(&piece);  // bricolage
		//bool estAbeille = (ab != nullptr);
		if (!piece.estAbeille()) {
			return resultat;	// ne contient aucun �l�ment
		}
	}


	set<Coordonnee> voisinsBonneCouleur;		// voisins des pi�ces de la m�me couleur que piece
	set<Coordonnee> voisinsMauvaiseCouleur;	// voisins des pi�ces de la couleur oppos�e piece
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

	set_difference(
		voisinsBonneCouleur.begin(), voisinsBonneCouleur.end(), voisinsMauvaiseCouleur.begin(), voisinsMauvaiseCouleur.end(),
		inserter(resultat, resultat.begin()));

	return resultat;
}

bool Plateau::deplacementPossible(const Piece& piece, const Coordonnee& coo) const
{
	// id�e de l'algo:
	// si la pi�ce n'est pas plac�e, on renvoie une exception
	// si la pi�ce n'est pas au dessus de sa case, elle ne peut pas bouger
	// si la pi�ce est au dessus de sa case et qu'il y a des pi�ces en dessous, elle peut bouger
	// si la case de la pi�ce n'a pas de voisin (�a ne devrait pas arriver mais on sait jamais), elle peut se d�placer.
	// sinon:
	// On prend une(seule) case voisine et on applique un algorithme de recherche en largeur en excluant la case actuelle
	// (pour simuler son absence). Parfois, la position initiale et la position finale possible sont toutes deux valides
	// pour que la ruche soit connect�e, mais elle doit l'�tre aussi pendant le glissement(sur un plateau physique)
	// Ceci est �quivalent au fait que la ruche reste connect�e apr�s la suppression de la pi�ce.
	// Si l'ensemble des cases obtenues a pour taille le nombre de cases -1, alors la ruche est totalement conn�ct�e
	// car on peut acc�der � n'importe quelle case du plateau en passant par le premier voisin choisi

	// Le param�tre coo n'est pas strictement n�cessaire car on peut techniquement chercher une pi�ce sur toutes
	// les coordonnees du plateau mais ce serait inutilement co�teux

	if (!piece.GetestPlacee()) {
		throw HiveException("la piece n'est pas encore placee");
	}

	Case* case_de_piece = getCaseDeCoo(coo);

	if (&piece != case_de_piece->getDessus()) {
		return false;
	}

	if (case_de_piece->getNombrePieces()>=2) {
		return true;
	}

	vector<Case*> premiers_voisins = getVoisinsDeCoo(case_de_piece->getCoo());

	if (premiers_voisins.size() == 0) {
		return true;
	}

	// obtention de toutes les cases accessibles � partir de premier_voisin dans visitees

	Case* premier_voisin = premiers_voisins.at(0);
	set<Case*> visitees;		// contient les cases d�j� visit�es
	vector<Case*> file_attente = { premier_voisin };	// contient les voisins(pas encore visit�s) des cases visit�es. 
	// Il faudra les visiter par la suite

	Case* case_actuelle;
	while (file_attente.size() > 0) {
		case_actuelle = file_attente.front();

		// ajout des cases voisines non d�j� visit�es dans la file d'attente pour les visiter plus tard
		// sauf si c'est la case de la pi�ce qu'on veut tester
		for (Case* case_voisine : getVoisinsDeCoo(case_actuelle->getCoo())) {	
			if ((visitees.find(case_voisine) != visitees.end())  && case_voisine!=case_de_piece) {
				file_attente.push_back(case_voisine);
			}
		}

		visitees.insert(case_actuelle);
		file_attente.erase(file_attente.begin());
	}

	return visitees.size() == getNombreCases() - 1;





}

set<Coordonnee> Plateau::getCooVoisinesGlissement(const Coordonnee& coo, const Coordonnee* ignorer_coo) const
{
	// ignorer_coo est la coordonn�e telle que la pi�ce visible de cette coordonn�e si elle existe doit
	// �tre ignor�e, comme si elle avait �t� supprim� du plateau. Utile pour qu'une pi�ce ne se consid�re
	// pas comme voisine � elle m�me dans les fonctions de d�placement
	//
	// id�e : pour chaque coo voisine de case0
	//		si une case est d�j� pr�sente(en prenant en compte l'ignorer_coo), on oublie
	//		si elle a deux coos communes avec les voisins de case0, on oublie (�a bloquerai le glissement)

	int nbr_intersections;
	set<Coordonnee> resultat;
	vector<Case*> voisins = getVoisinsDeCoo(coo);

	// suppression de la case s'il faut l'ignorer
	for (Case* case0 : voisins) {
		if (&(case0->getCoo()) == ignorer_coo && case0->getNombrePieces() == 1) {
			voisins.erase(remove(voisins.begin(), voisins.end(), case0), voisins.end());
		}
	}

	bool case_occupee;
	for (Coordonnee coo_voisine : coo.getVoisins()) {

		case_occupee = false;
		for (Case* case0 : voisins) {
			if (case0->getCoo() == coo_voisine) {	// si une case est pr�sente sur la coo_voisine
				case_occupee = true;
				break;
			}
		}
		if (case_occupee) {
			continue;
		}

		nbr_intersections = 0;
		for (Case* case_voisine_voisine : getVoisinsDeCoo(coo_voisine)) {
			if (find(voisins.begin(), voisins.end(), case_voisine_voisine) != voisins.end()) {
				// si un voisin du voisin est un voisin
				nbr_intersections++;
			}
		}
		// 2 -> impossible de glisser (bloqu�)
		// 0 -> sort de la ruche (au moins pendant le glissement physique sur le plateau)
		if (nbr_intersections == 1) {
			resultat.insert(coo_voisine);
		}
	}
	return resultat;
}


vector<Case*> Plateau::getVoisinsDeCoo(const Coordonnee& coo) const
// on ne peut pas �crire case car c'est un mot cl�
{
	vector<Case*> voisins;
	vector<Coordonnee> coo_voisines = coo.getVoisins();
	Case* case_voisine;

	for (auto coo_voisine : coo_voisines) {
		case_voisine = getCaseDeCoo(coo_voisine);// Si une case se trouve sur la coordonnee voisine
		if (case_voisine != nullptr) {
			voisins.push_back(case_voisine);
		}	

	}
	return voisins;

}

bool Plateau::estAbeillePlacee(Couleur couleur) const
{
	// on test juste chaque pi�ce de chaque case
	Case* case0;
	for (pair<Coordonnee, Case*> paire : Cases) {
		case0 = paire.second;
		for (const Piece* piece : case0->getPieces()) {

			if (piece->estAbeille() && piece->GetCouleur()==couleur) {
				return true;
			}

		}

	}
	return false;
}

ostream& JeuHive::operator<<(ostream& f, const Plateau& p)
{
	// r�sultat de l'affichage:
	// Pour chaque hexagone, la pile de pi�ce est affich�e: un pi�ce est repr�sent�e par un entier(0 pour BLANC, 1 pour
	// NOIR) et d'un caract�re pour le type d'insecte:
	// A:abeille, a:araign�e, S:scarab�e, s:sauterelle, f:fourmi, m: moustique, c:coccinelle


	// pour afficher dans la console le plateau, peut convertir les coos hexagonales en une hauteur y(1 pour chaque ligne)
	// et une position x(un certain nombre de caract�res)
	// Pour s'assurer qu'il y ait assez de place, la convertion sera lin�aire et se fera de cette mani�re:
	// y=2q+r, x=r
	// les lignes ne s'afficheront bien que si le jeu n'est pas trop �tendu sur l'axe gauche-droite, et on ne peut rien y
	// faire

	if (p.estVide()) {
		return f;
	}

	int taille_str = 4;	// la taille que prendra chaque hexagone � afficher

	//on commence par calculer les x et y min et max pour gacher le moins de place possible
	int min_y = 10000;  // on suppose qu'aucune case ne sera � de telles coordonn�es
	int max_y = -10000;
	int min_x = 10000; 
	int max_x = -10000; 

	Coordonnee coo_case;
	int x_case;
	int y_case;

	for (auto paire : p.getCases()) {
		coo_case = paire.first;
		x_case = coo_case.get_q();
		y_case = coo_case.get_q() + 2*coo_case.get_r();
		min_y = min(min_y, y_case);
		max_y = max(max_y, y_case);
		min_x = min(min_x, x_case);
		max_x = max(max_x, x_case);
		taille_str = max(taille_str, paire.second->getNombrePieces() * 2);

	}
	int taille_x = max_x - min_x + 1;
	int taille_y = max_y - min_y + 1;
	const string str_espaces = string(taille_str, ' ');

	cout << "taille_x" << taille_x << "   taille_y" <<taille_y<<"\n";

	// tableau bidimensionnel rempli de str_espaces
	vector<vector<string>> tab = vector<vector<string>>(taille_y, vector<string>(taille_x, str_espaces)); 
	
	/*
	cout << "tableau vide " << "\n";
	for (int i = tab.size() - 1; i >= 0; i--) {		// boucle invers�e car on print de haut en bas
		for (int j = 0; j < tab[0].size(); j++) {
			f << "i:" << i << "j:" << j << " voila ";
			f << tab.at(i).at(j) << "\n";
		}
		f << "\n";
	}
	*/

	
	Case* case0;
	string str_case;
	for (auto paire : p.getCases()) {
		coo_case = paire.first;
		case0 = paire.second;

		x_case = coo_case.get_q();
		y_case = coo_case.get_q() + 2 * coo_case.get_r();
		str_case = case0->getString(taille_str);
		/*
		cout << "str_case" << coo_case << " coo_cases xy " << x_case-min_y << "  " << y_case-min_x 
			<< " coo_cases xy " << x_case << "  " << y_case
			<< " " << str_case << "\n";
		*/
		tab.at(y_case-min_y).at(x_case-min_x) = str_case;

	}
	// tableau maintenant rempli
	
	// f << "sizey" << tab.size() << "\n";
	// f << "sizex" << tab.at(0).size() << "\n";

	/*
	cout << "tableau rempli " << "\n";
	for (int i = tab.size() - 1; i >= 0; i--) {		// boucle invers�e car on print de haut en bas
		for (int j = 0; j < tab[0].size(); j++) {
			f << "i:" << i << "j:" << j << " voila ";
			f << tab.at(i).at(j) << "\n";
		}
		f << "\n";
	}
	*/


	for (int i = taille_y - 1; i >= 0; i--) {		// boucle invers�e car on print de haut en bas
		for (int j = 0; j < taille_x; j++) {
			f << tab.at(i).at(j);
		}
		f << "\n";
	}

	return f;

}
