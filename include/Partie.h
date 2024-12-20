#pragma once
#include "Enums.h"
#include "Joueur.h"
#include <iostream>
#include "Plateau.h"
#include "Regle.h"
#include "HistoriqueCoup.h"
#include "Coup.h"
#include "Evenement.h"
#include "ResumeClasse.h"

namespace JeuHive {
	class Partie : public Observable
	{
	private:
		int id;
		Joueur joueur1;
		Joueur joueur2;
		Plateau plateau;
		Regle regles;
		HistoriqueCoup historique;
		EtatPartie etatPartie;
		Joueur* joueurActuel;
		Joueur* Victorieux;
		int compteurTour;

		int CompteurRegles; // permet de vérifier que le seuil de nombre de retours maximum n'est pas dépassé

		static int prochain_id;

	public:
		Partie(Joueur& j1, Joueur& j2);
		~Partie() = default;

		// Accesseurs
		int getId() const { return id; }

		const Joueur& getJoueur1() const { return joueur1; }
		Joueur& getJoueur1() { return joueur1; }

		const Joueur& getJoueur2() const { return joueur2; }
		Joueur& getJoueur2() { return joueur2; }

		const Plateau& getPlateau() const { return plateau; }

		const HistoriqueCoup& getHistorique() const { return historique; }
		
		const EtatPartie& getEtatPartie() const { return etatPartie; }

		const Joueur* getJoueurActuel() const { return joueurActuel; }

		const int getCompteurTour() const { return compteurTour; }

		bool verifier_partie();

		// Methodes principales
		void demarrer();
		void initialiser();
		void reprendre();
		void mettreEnPause();
		void terminer();



		// Pour ces fonctions, il faudra s'assurer que la partie est en cours
		void placerPiece(int idPiece, const Coordonnee& cooDestination);
		void deplacerPiece(const Coordonnee& cooOrigine, const Coordonnee& cooDestination);
		void jouerCoup(Coup* coup);
		void joueurSuivant();
		bool annulerDernierCoup();

		void verifierAnnulation(); 


		// Autres méthodes
		ResumePartie resumer() const;
		string tostringresumer() const;
	};



	class PartieFactory {
	public:
		static Partie* creerPartie(Joueur& joueur1, Joueur& joueur2) {
			return new Partie(joueur1, joueur2);
		}
	};
}