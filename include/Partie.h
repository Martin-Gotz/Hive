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
		Joueur joueurActuel;

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

		const HistoriqueCoup& getHistorique() const { return historique; }
		
		const EtatPartie& getEtatPartie() const { return etatPartie; }

		const Joueur& getJoueurActuel() const { return joueurActuel; }
		Joueur& getJoueurActuel() { return joueurActuel;}


		// Methodes principales
		void demarrer();
		void initialiser();
		void reprendre();
		void mettreEnPause();
		void terminer();

		void jouerCoup(const Coup& coup); // L'ajouter aussi a l'historique
		void changerJoueurActuel();
		void tourSuivant();
		void annulerDernierCoup();


		// Methode utilitaire pour afficher l'etat de la partie
		void afficher(ostream& os) const;
		friend ostream& operator<<(ostream& os, const Partie& partie);
	};

	class PartieFactory {
	public:
		static Partie* creerPartie(int id, Joueur& joueur1, Joueur& joueur2) {
			return new Partie(id, joueur1, joueur2);
		}
	};
}