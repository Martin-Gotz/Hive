#pragma once

namespace JeuHive {
	class Regle
	{
	private:
		int nombre_retours;
	public:
		Regle(int nombre = 1) :  nombre_retours(nombre) {}
		int GetNombreRetours() const { return nombre_retours; }
	};
}
