#include "../include/Partie.h"
using namespace Hive;

void Partie::lancerpartie()
{
	cout << "Lancement de la partie ...\n";
}

void Partie::finPartie()
{
	const auto& pieces = joueur1.getMain().getPieces();
	for (const auto& piece : pieces) {
		if (piece.getName() == "Reine") {
			const Reine* reine = dynamic_cast<const Reine*>(&piece);
			if (reine && reine->IsSurrounded()) {
				cout << "La Reine est entourée. Fin de la partie.\n";
				etatPartie = Terminee;
				return;
			}
		}
	}
}

Coup& Partie::JouerCoup()
{
	// à compléter
	cout << "veuillez choisir un emplacement : \n";
	plateau.EnsemblePlacementPossibles();

}

void Partie::TourSuivant()
{
	switch (joueur_actuel) {
	case player1:
		cout << "Au tour de : " << joueur1.getNom() << "\n";
		JouerCoup();
		joueur_actuel = player2;
		break;
	case player2:
		cout << "Au tour de : " << joueur1.getNom() << "\n";
		JouerCoup();
		joueur_actuel = player1;
		break;
	default:
		cout << "joueur inconnu ...\n";
	}
}