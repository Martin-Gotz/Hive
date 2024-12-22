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

		vector<Partie*> getAllParties() const { return parties; }
		// Methodes pour gerer les parties
		void ajouterPartie(const string& nomJoueur1, TypeJoueur typeJoueur1, const string& nomJoueur2, TypeJoueur typeJoueur2, int nombreRetours);
		void supprimerPartie(int idPartie);

		Partie* getPartie(int idPartie);
		const Partie* getPartie(int idPartie) const;
		int nombreParties() const;


		// Gestion de la partie en cours
		void demarrerPartie(int idPartie);
		void terminerPartie();
		//void terminerPartie(int idPartie); // on en aurait pas besoin en réalité
		void mettrePartieEnPause();

		Partie* getPartieEnCours() { return partieEnCours; }
		const Partie* getPartieEnCours() const { return partieEnCours; }


		// Methode utilitaires
		EtatHive resumer() const;
	};
}
