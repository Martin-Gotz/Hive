#pragma once
#include "Coordonnee.h"

namespace Hive {
	class Piece
	{
	private:
		Coordonnee& c;
		string name;
	public:
		string getName() const { return name; }
		Coordonnee getCoord() const { return c; }
	};
}

