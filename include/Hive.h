#pragma once

#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <ostream>
#include "Partie.h"
#include "Evenement.h"
#include "ResumeClasse.h"

using namespace std;

namespace JeuHive {
	class Hive : public Observable
	{
	private:
		vector<Partie*> parties;
		Partie* partieEnCours;

		// Constructeur privé
		Hive() : partieEnCours(nullptr) {}

		// Suppression du constructeur par copie et de l'opérateur d'affectation
		Hive(const Hive&) = delete;
		Hive& operator=(const Hive&) = delete;

	public:
		// Méthode statique pour accéder à l'instance unique
		static Hive& getInstance() {
			static Hive instance;
			return instance;
		}

		~Hive();


		// Methodes pour gerer les parties
		void ajouterPartie(Joueur& joueur1, Joueur& joueur2);
		void ajouterPartie(const string& nomJoueur1, TypeJoueur typeJoueur1, const string& nomJoueur2, TypeJoueur typeJoueur2);
		void supprimerPartie(int idPartie);

		Partie* getPartie(int idPartie);
		const Partie* getPartie(int idPartie) const;
		int nombreParties() const;


		// Gestion de la partie en cours
		void demarrerPartie(int idPartie);
		void terminerPartie();
		void mettrePartieEnPause();

		Partie* getPartieEnCours() { return partieEnCours; }
		const Partie* getPartieEnCours() const { return partieEnCours; }


		// Methode utilitaires
		void afficherParties() const;
		EtatHive getEtatHive() const;
	};
}
