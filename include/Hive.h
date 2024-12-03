#pragma once

#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <ostream>
#include "Partie.h"

using namespace std;

namespace JeuHive {
	class Hive
	{
	private:
		vector<Partie*> parties;
		Partie* partieEnCours;
	public:
		Hive();
		~Hive();

		// Methodes pour gerer les parties
		void ajouterPartie(const Partie& partie); // Peut être ne pas utiliser une référence constante (par valeur ou création d'une nouvelle partie dans la méthode ?)
		void supprimerPartie(int idPartie);
		Partie* getPartie(int idPartie);
		const Partie* getPartie(int idPartie) const;
		int nombreParties() const;

		// Gestion de la partie en cours
		void demarrerPartie(int idPartie);
		void terminerPartie();

		Partie* getPartieEnCours() { return partieEnCours; }

		const Partie* getPartieEnCours() const { return partieEnCours; }


		// Methode utilitaires
		void afficherParties() const;
	};

	// classe d'exception mise dans un fichier .h séparé pour pour l'utiliser sans créer des boucles d'inclusions.
}
