#pragma once

#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <ostream>
#include "Partie.h"

using namespace std;

namespace Hive {
	class Hive
	{
	private:
		vector<Partie> Parties;
		Partie& PartieEnCours;
	public:
		void CreerNouvellePartie();
		void ChangerPartie();
	};
}
