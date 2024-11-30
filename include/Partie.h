#pragma once
#include "Joueur.h"
#include <iostream>
#include "Plateau.h"
#include "Regle.h"
#include "HistoriqueCoup.h"
#include "Coup.h"

namespace Hive {


	enum Etat {En_cours, Terminee, Annulee};
	enum Joueur_actuel {player1, player2};

	class Partie
	{
	private:
		Joueur& joueur1;
		Joueur& joueur2;
		Plateau plateau;
		Regle regles;
		HistoriqueCoup historique;
		Joueur_actuel joueur_actuel;
		Etat etatPartie;
		float temps;
	public:
		void lancerpartie();
		void finPartie();
		void TourSuivant();
		Coup& JouerCoup();
		void AnnulerDernierCoup();
		Partie(Joueur& joueur_x, Joueur& joueur_y, Regle r, Joueur_actuel j) : joueur1(joueur_x), joueur2(joueur_y), plateau(), temps(0), etatPartie(En_cours), joueur_actuel(j) {}
	};
}

