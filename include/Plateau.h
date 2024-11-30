#pragma once
#include <iostream>
#include <vector>
#include "Case.h"

using namespace std;
namespace Hive {

	class Plateau
	{
	private:
		int ID;
		int nombre_cases;
		vector<Case> Cases;
	public:
		vector<Case> getCases() const;
		Plateau() : nombre_cases(0), ID(0) {};
		friend ostream& operator<<(ostream& f, Plateau& p);
		int getId() const { return ID; }
		int getNombreCases() const { return nombre_cases; }
		vector<Case> EnsemblePlacementPossibles(); 
	};
	ostream& operator<<(ostream& f, const Plateau& p);

}

