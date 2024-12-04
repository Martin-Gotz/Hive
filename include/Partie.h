#pragma once
#include "Enums.h"
#include "Joueur.h"
#include <iostream>
#include "Plateau.h"
#include "Regle.h"
#include "HistoriqueCoup.h"
#include "Coup.h"
#include "Event.h"

namespace JeuHive {
	class Partie
	{
	private:
		int id;
		Joueur joueur1;
		Joueur joueur2;
		Plateau plateau;
		Regle regles;
		HistoriqueCoup historique;
		EtatPartie etatPartie;
		Joueur joueurActuel;
		vector<Observer*> observers;

	public:
		Partie(int id, Joueur& j1, Joueur& j2);
		~Partie() = default;

		// Accesseurs
		int getId() const { return id; }

		const Joueur& getJoueur1() const { return joueur1; }
		Joueur& getJoueur1() { return joueur1; }

		const Joueur& getJoueur2() const { return joueur2; }
		Joueur& getJoueur2() { return joueur2; }

		const Plateau& getPlateau() const { return plateau; }
		Plateau& getPlateau() { return plateau; } // Version non const pour modifier le plateau si besoin

		const HistoriqueCoup& getHistorique() const { return historique; }
		HistoriqueCoup& getHistorique() { return historique; } // Version non const pour modifier l'historique si besoin
		
		const EtatPartie& getEtatPartie() const { return etatPartie; }

		const Joueur& getJoueurActuel() const { return joueurActuel; }
		Joueur& getJoueurActuel() { return joueurActuel;}


		// Mutateurs
		void setEtatPartie(EtatPartie nouvelEtat) {
			etatPartie = nouvelEtat;
		}

		// Methodes principales
		void demarrer();
		void terminer();
		void jouerCoup(const Coup& coup); // L'ajouter aussi a l'historique
		void changerJoueurActuel();
		void tourSuivant();
		void annulerDernierCoup();


		// Gestion des observateurs
		void ajouterObserver(Observer* observer);
		void retirerObserver(Observer* observer);
		void notifierObservers(const Evenement& evenement);


		// Methode utilitaire pour afficher l'etat de la partie
		void afficher(ostream& os) const;
	};

	class PartieFactory {
	public:
		static Partie* creerPartie(int id, Joueur& joueur1, Joueur& joueur2) {
			return new Partie(id, joueur1, joueur2);
		}
	};
}