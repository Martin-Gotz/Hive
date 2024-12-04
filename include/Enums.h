#pragma once
#include <string>

namespace JeuHive {
	enum TypeJoueur {
		HUMAIN,
		IA
	};

	enum Couleur {
		BLANC,
		NOIR
	};

	enum Action {
		PLACEMENT,
		DEPLACEMENT
	};

	enum EtatPartie {
		EN_PAUSE,
		EN_COURS,
		TERMINEE
	};


	enum TypeEvenement {
		DEBUT_PARTIE,
		FIN_PARTIE,
		CHANGEMENT_JOUEUR,
		TOUR_SUIVANT,
		ANNULER_COUP,
		SAUVEGARDE_PARTIE,
		PIECE_PLACEE,
		ERREUR_PARTIE
	};
}
