#pragma once

#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <ostream>
#include "Partie.h"
#include "Event.h"

using namespace std;

namespace JeuHive {
	class Hive : public Observable
	{
	private:
		vector<Partie*> parties;
		Partie* partieEnCours;
		int prochainIdPartie;

		// Constructeur privé
		Hive() : partieEnCours(nullptr), prochainIdPartie(1) {}

		// Suppression du constructeur par copie et de l'opérateur d'affectation
		Hive(const Hive&) = delete;
		Hive& operator=(const Hive&) = delete;

	public:
		// Méthode statique pour accéder à l'instance unique
		static Hive& getInstance() {
			static Hive instance;
			return instance;
		}

		// Destructeur
		~Hive();

		// Methodes pour gerer les parties

		void ajouterPartie(Joueur& joueur1, Joueur& joueur2); // Asignation des couleurs et autres paramètres à voir
		void supprimerPartie(int idPartie);

		Partie* getPartie(int idPartie);
		const Partie* getPartie(int idPartie) const;
		int nombreParties() const;

		// Gestion de la partie en cours
		void demarrerPartie(int idPartie);
		void demarrerPartie(Partie* partie);
		void terminerPartie();

		Partie* getPartieEnCours() { return partieEnCours; }
		const Partie* getPartieEnCours() const { return partieEnCours; }


		// Methode utilitaires
		void afficherParties() const;
	};

	// classe d'exception mise dans un fichier .h séparé pour pour l'utiliser sans créer des boucles d'inclusions.
}
