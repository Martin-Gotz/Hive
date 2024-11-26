#pragma once
#include <iostream>
#include <vector>
#include "Coordonnee.h"

using namespace std;
namespace Hive {

	class Plateau
	{
	private:
		int ID;
		int nombre_cases;
		vector<Case> Cases;
	public:
		vector<Coordonnee> getCases() const;
		Plateau() : nombre_cases(0), ID(0) {};
		friend ostream& operator<<(ostream& f, Plateau& p);
		int getId() const { return ID; }
		int getNombreCases() const { return nombre_cases; }
	};
	ostream& operator<<(ostream& f, const Plateau& p);

	class Ensemble_Plateaux
	{
	private:
		vector<Plateau> plateau;
		int nombre;
	public:
		Ensemble_Plateaux();
		~Ensemble_Plateaux();
		Plateau getPlateau(int ID);
		int getNombrePlateau() const;
	};
}

