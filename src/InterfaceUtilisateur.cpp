#include "../include/InterfaceUtilisateur.h"
using namespace JeuHive;

// Constructeurs et destructeurs
InterfaceUtilisateur::InterfaceUtilisateur(Hive& h) : hive(h) {
    hive.ajouterObserver(this);
}

InterfaceUtilisateur::~InterfaceUtilisateur() {
    if (partieObservee) {
        partieObservee->retirerObserver(this);
    }
    hive.retirerObserver(this);
}



// ===== METHODES D'AFFICHAGE =====

// Afficher le menu
void InterfaceUtilisateur::afficherMenu() const {
    cout << "\n======== MENU ========\n";
    cout << "1. Ajouter une nouvelle partie\n";
    cout << "2. Démarrer une partie\n";
    cout << "3. Supprimer une partie\n";
    cout << "4. Afficher les parties\n";
    cout << "5. Quitter\n";
}

// Afficher le menu de la partie en cours
void InterfaceUtilisateur::afficherMenuPartie() const {
    cout << "\n===== PARTIE ===== " << endl;
    cout << "1. Jouer un coup" << endl;
    cout << "2. Terminer la partie" << endl;
    cout << "3. Retour au menu principal" << endl;
}





// ===== GESTION DES MENUS =====
// 
// Logique de validation des entrées
int InterfaceUtilisateur::obtenirEntreeUtilisateur(const string& message, bool menu = false) {
    int valeur;
    cout << message;
    cin >> valeur;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (!menu) {
            cout << endl << "Erreur : Veuillez entrer un nombre valide." << endl;
        }
        return -1;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return valeur;
}

// MENU PRINCIPAL
void InterfaceUtilisateur::gererChoixUtilisateur() {
    while (true) {
        afficherMenu();
        int choix = obtenirEntreeUtilisateur("Entrez votre choix : ", true);
        cout << "---------------------\n";

        switch (choix) {
        case 1: ajouterPartie(); break;
        case 2: demarrerPartie(); break;
        case 3: supprimerPartie(); break;
        case 4: afficherParties(); break;
        case 5: cout << "Au revoir !\n"; return;
        default: cout << "Option invalide, veuillez réessayer.\n";
        }
        cout << endl << endl;
    }
}

// PARTIE EN COURS
void InterfaceUtilisateur::gererChoixUtilisateurMenuPartie() {
    int choix = -1;

    while (true) {
        afficherMenuPartie();
        int choix = obtenirEntreeUtilisateur("Entrez votre choix : ");
        cout << "---------------------" << endl;

        switch (choix) {
        case 1: jouerCoup(); break;
        case 2: terminerPartieEnCours(); return;
        case 3: retournerMenu(); return; // Retour au menu principal après la terminaison de la partie
        default: cout << "Option invalide, veuillez réessayer." << endl;
        }

        cout << endl << endl;
    }
}







// ===== METHODES RELATIVES A HIVE =====

// Demander à l'utilisateur les informations nécessaires pour ajouter une partie
void InterfaceUtilisateur::ajouterPartie() {
    string nomJoueur1, nomJoueur2;
    cout << "Entrez le nom du joueur 1 : ";
    cin >> nomJoueur1;
    cout << "Entrez le nom du joueur 2 : ";
    cin >> nomJoueur2;
    cout << endl;

    Joueur joueur1(nomJoueur1);
    Joueur joueur2(nomJoueur2);

    hive.ajouterPartie(joueur1, joueur2);
}

// Partie à démarrer
void InterfaceUtilisateur::demarrerPartie() {
    if (hive.nombreParties() == 0) {
        cout << "Aucune partie à démarrer." << endl;
        return;
    }

    if (hive.getPartieEnCours() != nullptr) {
        cout << "Une partie est déjà en cours." << endl;
        return;
    }

    afficherParties();
    cout << endl;
    int idPartie = obtenirEntreeUtilisateur("Entrez l'ID de la partie à démarrer : ");
    cout << endl;

    // Vérification de la valeur en cas d'entrée invalide
    if (idPartie == -1) {
        return;
    }

    try {
        partieObservee = hive.getPartie(idPartie);

        if (partieObservee) {
            partieObservee->ajouterObserver(this);
        }

        hive.demarrerPartie(idPartie);
        cout << endl << endl;
        cout << "-------------------- Partie " << partieObservee->getId() << " --------------------" << endl;
        gererChoixUtilisateurMenuPartie();
    }
    catch (const HiveException& e) {
        cout << "Erreur : " << e.getInfo() << endl;
    }
}


// Partie à supprimer
void InterfaceUtilisateur::supprimerPartie() {
    if (hive.nombreParties() == 0) {
        cout << "Aucune partie à supprimer." << endl;
        return;
    }

    afficherParties();
    cout << endl;
    int idPartie = obtenirEntreeUtilisateur("Entrez l'ID de la partie à supprimer : ");
    cout << endl;
    
    // Vérification de la valeur en cas d'entrée invalide
    if (idPartie == -1) {
        return;
    }

    try {
        hive.supprimerPartie(idPartie);
    }
    catch (const HiveException& e) {
        cout << "Erreur : " << e.getInfo() << endl;
    }
}





// ===== METHODES RELATIVES A PARTIE =====

// Jouer un coup dans la partie en cours
void InterfaceUtilisateur::jouerCoup() {
    cout << "Entrez le coup à jouer : ";
    string coup;
    cin >> coup;
    partieObservee->jouerCoup(Coup(coup));
}

// Terminer la partie en cours
void InterfaceUtilisateur::terminerPartieEnCours() {
    hive.terminerPartie();
    partieObservee = nullptr;
}

// Changer le joueur actuel
void InterfaceUtilisateur::retournerMenu() {
    hive.mettrePartieEnPause();
    partieObservee = nullptr;
}





// ===== AUTRES METHODES =====

// Afficher toutes les parties
void InterfaceUtilisateur::afficherParties() {
    EtatHive etat = hive.getEtatHive(); // Récupère l'état des parties

    if (etat.parties.empty()) {
        cout << "Aucune partie n'est enregistree." << endl << endl;
        return;
    }

    cout << "Liste des parties :" << endl;
    for (const auto& resume : etat.parties) {
        cout << resume.id
            << " : " << resume.joueur1 << " vs " << resume.joueur2
            << " - " << resume.etatPartie << endl;
    }
}


void InterfaceUtilisateur::afficherEvenement(const Evenement& e) const {
    // Afficher le message de l'observable si il existe
    if (!e.getDescription().empty()) {
        cout << e.getDescription() << endl;
    }

    // Affichages supplémentaires
    if (e.getType() == TypeEvenement::DEBUT_PARTIE) {
        cout << "La partie a commencé !" << endl;
    }
    else if (e.getType() == TypeEvenement::FIN_PARTIE) {
        cout << "La partie est terminée." << endl;
    }
    else if (e.getType() == TypeEvenement::PAUSE_PARTIE) {
        cout << "La partie est en pause." << endl;
    }
    else if (e.getType() == TypeEvenement::TOUR_SUIVANT) {
        cout << "C'est au tour du joueur suivant." << endl;
    }
    else if (e.getType() == TypeEvenement::CHANGEMENT_JOUEUR) {
        cout << "Changement de joueur." << endl;
    }
}

// Action de l'observateur
void InterfaceUtilisateur::reagir(const Evenement& e) {
    afficherEvenement(e);
}