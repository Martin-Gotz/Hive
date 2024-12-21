#include "../include/FabriquePiece.h"



namespace JeuHive {
	FabriquePiece initialiserFabriquePiece()
	{
		FabriquePiece fabrique;
		fabrique.enregistrerPiece("Abeille", [](Couleur couleur) { return new Abeille(couleur); }, 1);
		fabrique.enregistrerPiece("Fourmi", [](Couleur couleur) { return new Fourmi(couleur); }, 3);
		fabrique.enregistrerPiece("Araignee", [](Couleur couleur) { return new Araignee(couleur); }, 2);
		fabrique.enregistrerPiece("Sauterelle", [](Couleur couleur) { return new Sauterelle(couleur); }, 3);
		fabrique.enregistrerPiece("Scarabee", [](Couleur couleur) { return new Scarabee(couleur); }, 2);
		return fabrique;
	}
}