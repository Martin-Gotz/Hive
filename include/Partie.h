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

		unsigned int CompteurRegles; // permet de vérifier que le seuil de nombre de retours maximum n'est pas dépassé

		static int prochain_id;

	public:
		Partie(Joueur& j1, Joueur& j2, Regle r);
		~Partie() = default;

		void modifierRegles(const Regle& r);

		// Accesseurs
		int getId() const { return id; }

		const static int getProchainId() { return prochain_id; }

		const Joueur& getJoueur1() const { return joueur1; }
		Joueur& getJoueur1() { return joueur1; }

		const Joueur& getJoueur2() const { return joueur2; }
		Joueur& getJoueur2() { return joueur2; }

		const Plateau& getPlateau() const { return plateau; }

		const HistoriqueCoup& getHistorique() const { return historique; }
		
		const EtatPartie& getEtatPartie() const { return etatPartie; }

		const Joueur* getJoueurActuel() const { return joueurActuel; }

		const int getCompteurTour() const { return compteurTour; }

		const int getCompteurRegles() const { return CompteurRegles; }

		void initialiserCompteurRegles() { CompteurRegles = 0; }
		void incrementerCompteurRegles() { ++CompteurRegles; }
		void decrementerCompteurRegles() { if (CompteurRegles > 0) --CompteurRegles; else CompteurRegles = 0; }

		const Regle getRegles() const { return regles; }

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
		void jouerCoupIA();
		void joueurSuivant();
		void annulerDernierCoup();

		void verifierAnnulation(); 


		// Autres méthodes
		ResumePartie resumer() const;
	};



	class PartieFactory {
	public:
		static Partie* creerPartie(Joueur& joueur1, Joueur& joueur2, Regle r) {
			return new Partie(joueur1, joueur2, r);
		}
	};
}