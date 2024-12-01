#pragma once

#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <ostream>
#include "Partie.h"

using namespace std;

namespace Hive {
	class Hive_Game
	{
	private:
		vector<Partie> Parties;
		Partie& PartieEnCours;
	public:
		void CreerNouvellePartie();
		void ChangerPartie();
		void SupprimerPartie();
	};

	// classe d'exception mise dans un fichier .h s�par� pour pour l'utiliser sans cr�er des boucles d'inclusions.
}
