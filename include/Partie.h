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
#include "JoueurIa.h"

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
		int nombreRetours;
		unsigned int compteurRegles; // permet de vérifier que le seuil de nombre de retours maximum n'est pas dépassé
		//int difficulte;
		static int prochain_id;
		JoueurIa* j;

	public:
		Partie(Joueur& j1, Joueur& j2, JoueurIa *Ia, int nombreRetours);
		~Partie() = default;

		// Accesseurs
		int getId() const { return id; }
		//const int getDifficulte() const { return difficulte; }
		//int getDifficulte() { return difficulte; }
		const static int getProchainId() { return prochain_id; }

		const Joueur& getJoueur1() const { return joueur1; }
		Joueur& getJoueur1() { return joueur1; }

		const Joueur& getJoueur2() const { return joueur2; }
		Joueur& getJoueur2() { return joueur2; }

		const Plateau& getPlateau() const { return plateau; }
		Plateau& getPlateau() { return plateau; }

		const HistoriqueCoup& getHistorique() const { return historique; }
		
		const EtatPartie& getEtatPartie() const { return etatPartie; }

		const Joueur* getJoueurActuel() const { return joueurActuel; }

		const int getCompteurTour() const { return compteurTour; }

		const int getCompteurRegles() const { return compteurRegles; }


		bool estPremierJoueurActuel() {
			return joueur1 == joueurActuel;
		}

		void initialiserCompteurRegles() { compteurRegles = 0; }
		void incrementerCompteurRegles() { if (compteurRegles < regles.getNombreRetours()) ++compteurRegles; else compteurRegles = regles.getNombreRetours(); }
		void decrementerCompteurRegles() { if (compteurRegles > 0) --compteurRegles; else compteurRegles = 0; }

		const Regle getRegles() const { return regles; }

		bool verifierEtatPartie();

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
		void jouerCoupIA();
		void joueurSuivant();
		void annulerDernierCoup();
		void annulerCoupAction(Coup* coup, Joueur* joueur);

		bool verifierAnnulation(); 


		// Autres méthodes
		ResumePartie resumer() const;
	};



	class FabriquePartie {
	public:
		static Partie* creerPartie(Joueur& joueur1, Joueur& joueur2, JoueurIa* Ia, int nombreRetours) {
			return new Partie(joueur1, joueur2, Ia, nombreRetours);
		}
	};
}