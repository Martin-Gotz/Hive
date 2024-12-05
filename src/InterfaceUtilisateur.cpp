#include "../include/InterfaceUtilisateur.h"
using namespace JeuHive;
InterfaceUtilisateur::InterfaceUtilisateur(Hive& h) : hive(h) {
    hive.ajouterObserver(this);
}

InterfaceUtilisateur::~InterfaceUtilisateur() {
    if (partieObservee) {
        partieObservee->retirerObserver(this);
    }
    hive.retirerObserver(this);
}

// Afficher le menu
void InterfaceUtilisateur::afficherMenu() const {
    cout << "\n=== Menu ===" << endl;
    cout << "1. Ajouter une nouvelle partie" << endl;
    cout << "2. Démarrer une partie" << endl;
    cout << "3. Supprimer une partie" << endl;
    cout << "4. Afficher les parties" << endl;
    cout << "5. Quitter" << endl;
    cout << "Entrez votre choix : ";
}

// Gestion des choix de l'utilisateur
void InterfaceUtilisateur::gererChoixUtilisateur() {
    int choix;
    while (true) {
        afficherMenu();
        cin >> choix;
        cout << "---------------------" << endl;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Veuillez entrer un nombre valide !" << endl;
            continue;
        }

        switch (choix) {
        case 1:
            ajouterPartie();
            break;
        case 2:
            demarrerPartie();
            break;
        case 3:
            supprimerPartie();
            break;
        case 4:
            afficherParties();
            break;
        case 5:
            cout << "Au revoir !" << endl;
            return;
        default:
            cout << "Option invalide, veuillez réessayer." << endl;
        }
    }
}


// Demander à l'utilisateur les informations nécessaires pour ajouter une partie
void InterfaceUtilisateur::ajouterPartie() {
    string nomJoueur1, nomJoueur2;
    cout << "Entrez le nom du joueur 1 : ";
    cin >> nomJoueur1;
    cout << "Entrez le nom du joueur 2 : ";
    cin >> nomJoueur2;

    Joueur joueur1(nomJoueur1);
    Joueur joueur2(nomJoueur2);

    hive.ajouterPartie(joueur1, joueur2);
}

// Partie à démarrer
void InterfaceUtilisateur::demarrerPartie() {
    if (hive.getPartieEnCours() != nullptr) {
        cout << "Une partie est déjà en cours." << endl;
        return;
    }

    int idPartie;
    afficherParties();
    cout << "Entrez l'ID de la partie à démarrer : ";
    cin >> idPartie;

    try {
        hive.demarrerPartie(idPartie);
        partieObservee = hive.getPartieEnCours();
        partieObservee->ajouterObserver(this);
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

    int idPartie;
    afficherParties();
    cout << "Entrez l'ID de la partie à supprimer : ";
    cin >> idPartie;

    try {
        hive.supprimerPartie(idPartie);
    }
    catch (const HiveException& e) {
        cout << "Erreur : " << e.getInfo() << endl;
    }
}

// Afficher toutes les parties
void InterfaceUtilisateur::afficherParties() {
    hive.afficherParties();
}





// PARTIE EN COURS
// Afficher le menu de la partie en cours
void InterfaceUtilisateur::afficherMenuPartie() const {
    cout << "\n=== Menu de la Partie ===" << endl;
    cout << "1. Jouer un coup" << endl;
    cout << "2. Terminer la partie" << endl;
    cout << "3. Retour au menu principal" << endl;
    cout << "Entrez votre choix : ";
}

// Gestion des choix du menu de la partie en cours
void InterfaceUtilisateur::gererChoixUtilisateurMenuPartie() {
    int choix;
    while (true) {
        afficherMenuPartie();
        cin >> choix;
        cout << "---------------------" << endl;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Veuillez entrer un nombre valide !" << endl;
            continue;
        }

        switch (choix) {
        case 1:
            jouerCoup();
            break;
        case 2:
            changerJoueurActuel();
            break;
        case 3:
            terminerPartieEnCours();
            return; // Retour au menu principal après la terminaison de la partie
        case 4:
            return; // Retour au menu principal sans terminer la partie
        default:
            cout << "Option invalide, veuillez réessayer." << endl;
        }
    }
}

// Jouer un coup dans la partie en cours
void InterfaceUtilisateur::jouerCoup() {
    cout << "Entrez le coup à jouer : ";
    string coup;
    cin >> coup;
    // Jouer le coup dans la partie en cours
    partieObservee->jouerCoup(Coup(coup));
}

// Changer le joueur actuel
void InterfaceUtilisateur::changerJoueurActuel() {
    partieObservee->changerJoueurActuel();
}

// Terminer la partie en cours
void InterfaceUtilisateur::terminerPartieEnCours() {
    partieObservee->terminer();
    partieObservee = nullptr;
}





void InterfaceUtilisateur::afficherEvenement(const Evenement& evenement) const {
    cout << "[Evenement] " << evenement.getDescription() << endl;
}

// Action de l'observateur
void InterfaceUtilisateur::reagir(const Evenement& evenement) {
    afficherEvenement(evenement);
}