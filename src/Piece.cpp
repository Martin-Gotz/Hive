#include "../include/Piece.h"
#include "../include/Plateau.h"

namespace JeuHive{
	set<Coordonnee> Abeille::ensembleDeplacementPossibles(const Plateau& plateau, const Coordonnee& coo) const
	{
		if (!plateau.deplacementPossible(*this, coo)) {
			return set<Coordonnee>();
		}
		return plateau.getCooVoisinesGlissement(coo);
	}

	set<Coordonnee> Scarabee::ensembleDeplacementPossibles(const Plateau& plateau, const Coordonnee& coo) const
	{
		if (!plateau.deplacementPossible(*this, coo)) {
			return set<Coordonnee>();
		}

		// s'il est sur une autre pi�ce alors il peut aller partout autour
		Case* case0 = plateau.getCaseDeCoo(coo);
		if (case0->getNombrePieces() > 1) {
			vector<Coordonnee> coo_voisines = coo.getVoisins();
			return set<Coordonnee>(coo_voisines.begin(), coo_voisines.end());
		}

		// union des glissements et des chevauchements
		set<Coordonnee> resultat = plateau.getCooVoisinesGlissement(coo);
		
		for (Case* case_voisine : plateau.getVoisinsDeCoo(coo)) {
			resultat.insert(case_voisine->getCoo());
		}
		return resultat;
	}

	set<Coordonnee> Araignee::ensembleDeplacementPossibles(const Plateau& plateau, const Coordonnee& coo) const
	{
		// l'entier repr�sente le nombre de mouvements d'une case effectu�s. Agit comme une file
		vector<pair<int,Coordonnee>> coos_intermediaires = { pair<int, Coordonnee>(0, coo)};
		set<Coordonnee> resultat;

		int generation;
		Coordonnee coo_intermediaire;
		set<Coordonnee> nouv_coos;
		while (coos_intermediaires.size()>0){
			generation = coos_intermediaires.front().first;
			coo_intermediaire = coos_intermediaires.front().second;

			nouv_coos = plateau.getCooVoisinesGlissement(coo_intermediaire);

			if (generation == 3-1) {
				for (Coordonnee nouv_coo : nouv_coos) {
					resultat.insert(nouv_coo);
				}
			}
			else {
				for (Coordonnee nouv_coo : nouv_coos) {
					coos_intermediaires.push_back(pair<int, Coordonnee>(generation+1, nouv_coo));
				}
			}

			coos_intermediaires.erase(coos_intermediaires.begin());
		}
		return resultat;
	}

	set<Coordonnee> Sauterelle::ensembleDeplacementPossibles(const Plateau& plateau, const Coordonnee& coo) const
	{
		set<Coordonnee> resultat;
		vector<Coordonnee> directions = getDirections();


		Coordonnee coo_ligne;	// coordonn�es le long de la ligne trac�e par la sauterelle
		for (const Coordonnee dir : directions) {
			coo_ligne = coo + dir;

			// si l'alv�ole voisine est inoccup�e, impossible d'aller dans cette direction
			if (plateau.getCaseDeCoo(coo_ligne) == nullptr) {
				continue;
			}

			coo_ligne = coo_ligne + dir;

			while (plateau.getCaseDeCoo(coo_ligne) != nullptr) {
				coo_ligne = coo_ligne + dir;
			}

			resultat.insert(coo_ligne);
		}
		
		return resultat;
	}

	set<Coordonnee> Fourmi::ensembleDeplacementPossibles(const Plateau& plateau, const Coordonnee& coo) const
	{
		vector<Coordonnee> coos_intermediaires = { coo };
		set<Coordonnee> resultat;

		Coordonnee coo_intermediaire;
		set<Coordonnee> nouv_coos;
		while (coos_intermediaires.size() > 0) {
			coo_intermediaire = coos_intermediaires.front();
			
			// si la coo est d�j� dans r�sultat alors on a d�j� vu cette coordonn�e passer par 
			// coo_intermediaire
			if (resultat.find(coo_intermediaire) != resultat.end()) {
				continue;
			}

			nouv_coos = plateau.getCooVoisinesGlissement(coo_intermediaire);

			
			for (Coordonnee nouv_coo : nouv_coos) {
				// si la nouvelle coo n'est pas d�j� dans resultat, on l'ajoute aux coos_intermediaires
				// On pourrait v�rifier que c'est pas non plus dans coos_intermediaires mais c'est pas
				// n�cessaire et c'est co�teux car trouver un �l�ment dans un vector ne se fait pas aussi
				// rapidement que dans un set.
				if (resultat.find(nouv_coo) != resultat.end()) {
					coos_intermediaires.push_back(nouv_coo);
				}
				
			}


			coos_intermediaires.erase(coos_intermediaires.begin());
		}
		return resultat;

		
	}

}