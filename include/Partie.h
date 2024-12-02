#pragma once
#include "Enums.h"
#include "Joueur.h"
#include <iostream>
#include "Plateau.h"
#include "Regle.h"
#include "HistoriqueCoup.h"
#include "Coup.h"

namespace Hive {


	class Partie
	{
	private:
		Joueur& joueur1;
		Joueur& joueur2;
		Plateau plateau;
		Regle regles;
		HistoriqueCoup historique;
		Joueur_actuel joueur_actuel;
		EtatPartie etatPartie;
		float temps;
	public:
		void lancerpartie();
		void finPartie();
		void TourSuivant();
		Coup& JouerCoup();
		void AnnulerDernierCoup();
		Partie(Joueur& joueur_x, Joueur& joueur_y, Regle r, Joueur_actuel j) : joueur1(joueur_x), joueur2(joueur_y), plateau(), temps(0), etatPartie(EN_COURS), joueur_actuel(j) {}
	};
}

