#pragma once

namespace JeuHive {
	class Regle
	{
	private:
		int nombreRetours;
	public:
		Regle(int nombre = 1) :  nombreRetours(nombre) {}
		int getNombreRetours() const { return nombreRetours; }
		void setNombreRetours(const int a) { nombreRetours = a; }
	};
}
