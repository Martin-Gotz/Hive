#pragma once

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
		EN_COURS,
		TERMINEE,
		ANNULEE
	};

	enum Joueur_actuel { player1, player2 };
}
