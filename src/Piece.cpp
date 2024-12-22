#include "../include/Piece.h"
#include "../include/Plateau.h"
#include <tuple>


namespace JeuHive {
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

		// s'il est sur une autre pièce alors il peut aller partout autour
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
		if (!plateau.deplacementPossible(*this, coo)) {
			return set<Coordonnee>();
		}

		int nbr_mouvements = 3;
		set<Coordonnee> resultat;

		// contient des tuplues de la forme:
		// - nombre de glissements effectués
		// - coordonnée précedente
		// - coordonnée actuelle
		vector<tuple<int, Coordonnee, Coordonnee>> coos_intermediaires = { {0, Coordonnee(10000, 10000), coo} };
		// nombre improbable(même impossible car la première pièce est placée en (0, 0)) car initialement,
		// il n'y a pas des coordonnée précédente et à cause de l'absence de NULL en C++

		int generation;
		Coordonnee coo_actuelle;
		Coordonnee coo_precedente;
		set<Coordonnee> nouv_coos_glissement;
		set<Coordonnee> nouv_coos;
		while (coos_intermediaires.size() > 0) {
			// on prend le premier élément qu'on supprimera par la suite
			generation = get<0>(coos_intermediaires.front());
			coo_precedente = get<1>(coos_intermediaires.front());
			coo_actuelle = get<2>(coos_intermediaires.front());

			nouv_coos_glissement = plateau.getCooVoisinesGlissement(coo_actuelle, &coo);
			nouv_coos = {};

			//cout << " coo actuelle: " << coo_actuelle << "  coo precedente " << coo_precedente << "\n";

			// suppression des retours arrière
			for (Coordonnee nouv_coo_glissement : nouv_coos_glissement) {
				// Si la coordonnée précedente est celle atteignable par un glissement, on n'y va pas
				// (l'araignée ne peut pas retourner sur ses pas)
				if (!(nouv_coo_glissement == coo_precedente)) {
					nouv_coos.insert(nouv_coo_glissement);
				}
			}

			/*
			cout << coo_actuelle << "coo_actuelle \n";
			for (Coordonnee debug : nouv_coos) {
				cout << "     nouv_coo " << debug << "\n";
			}
			*/


			if (generation == nbr_mouvements - 1) {
				for (Coordonnee nouv_coo : nouv_coos) {
					resultat.insert(nouv_coo);
				}
			}
			else {
				for (Coordonnee nouv_coo : nouv_coos) {
					coos_intermediaires.push_back({ generation + 1, coo_actuelle, nouv_coo });
				}
			}

			coos_intermediaires.erase(coos_intermediaires.begin());
		}
		return resultat;
	}

	set<Coordonnee> Sauterelle::ensembleDeplacementPossibles(const Plateau& plateau, const Coordonnee& coo) const
	{
		if (!plateau.deplacementPossible(*this, coo)) {
			return set<Coordonnee>();
		}

		set<Coordonnee> resultat;
		vector<Coordonnee> directions = getDirections();


		Coordonnee coo_ligne;	// coordonnées le long de la ligne tracée par la sauterelle
		for (const Coordonnee dir : directions) {
			coo_ligne = coo + dir;

			// si l'alvéole voisine est inoccupée, impossible d'aller dans cette direction
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
		if (!plateau.deplacementPossible(*this, coo)) {
			return set<Coordonnee>();
		}

		vector<Coordonnee> coos_intermediaires = { coo };
		set<Coordonnee> resultat;

		Coordonnee coo_actuelle;
		set<Coordonnee> nouv_coos;
		while (coos_intermediaires.size() > 0) {
			coo_actuelle = coos_intermediaires.front();

			// si la coo est déjà dans résultat alors on a déjà vu cette coordonnée passer par 
			// coo_actuelle
			if (resultat.find(coo_actuelle) != resultat.end()) {
				coos_intermediaires.erase(coos_intermediaires.begin());
				continue;
			}

			nouv_coos = plateau.getCooVoisinesGlissement(coo_actuelle, &coo);


			for (Coordonnee nouv_coo : nouv_coos) {
				// si la nouvelle coo n'est pas déjà dans resultat, on l'ajoute aux coos_intermediaires
				// On pourrait vérifier que c'est pas non plus dans coos_intermediaires mais c'est pas
				// nécessaire et c'est coûteux car trouver un élément dans un vector ne se fait pas aussi
				// rapidement que dans un set.
				if (resultat.find(nouv_coo) == resultat.end()) {
					coos_intermediaires.push_back(nouv_coo);
				}

			}

			resultat.insert(coo_actuelle);
			coos_intermediaires.erase(coos_intermediaires.begin());
		}
		resultat.erase(coo);
		return resultat;
	}

	string Piece::toString() const
	{
		ResumePiece resume = resumer();
		return resume.symbole + resume.symboleCouleur;
	}

	ResumePiece Piece::resumer() const
	{
		ResumePiece resume;
		resume.nom = getNom();
		resume.symbole = getSymbole();
		resume.couleur = (getCouleur() == Couleur::BLANC ? "Blanc" : "Noir");
		resume.symboleCouleur = (resume.couleur[0]);
		return resume;
	}
}