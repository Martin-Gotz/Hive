#pragma once
#include "Joueur.h"
#include <iostream>
#include "Plateau.h"
#include "Regle.h"
#include "HistoriqueCoup.h"
#include "Coup.h"

namespace Hive {


	enum Etat {En_cours, Terminee, Annulee};
	class Partie
	{
	private:
		Joueur& joueur1;
		Joueur& joueur2;
		Plateau& plateau;
		Regle& regles;
		HistoriqueCoup& historique;
		Joueur& joueur_actuel;
		Etat &etatPartie;
		float temps;
	public:
		void lancerpartie();
		void finPartie();
		void TourSuivant();
		Coup& JouerCoup();
		void AnnulerDernierCoup();
	};
}

