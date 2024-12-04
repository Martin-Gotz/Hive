#include "../include/InterfaceUtilisateur.h"
using namespace JeuHive;
InterfaceUtilisateur::InterfaceUtilisateur(Hive& h) : hive(h) {
    hive.ajouterObserver(this);
}

// Afficher le menu
void InterfaceUtilisateur::afficherMenu() const {
    cout << "\n=== Menu ===" << endl;
    cout << "1. Ajouter une nouvelle partie" << endl;
    cout << "2. Démarrer une partie" << endl;
    cout << "3. Terminer la partie en cours" << endl;
    cout << "4. Supprimer une partie" << endl;
    cout << "5. Afficher les parties" << endl;
    cout << "6. Quitter" << endl;
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
            terminerPartie();
            break;
        case 4:
            supprimerPartie();
            break;
        case 5:
            afficherParties();
            break;
        case 6:
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
    int idPartie;
    if (hive.nombreParties() != 0) {
        afficherParties();
        cout << "Entrez l'ID de la partie à démarrer : ";
        cin >> idPartie;
    }
    else {
        idPartie = 0;
    }

    try {
        hive.demarrerPartie(idPartie);
    }
    catch (const HiveException& e) {
        cout << "Erreur : " << e.getInfo() << endl;
    }
}

// Terminer la partie en cours
void InterfaceUtilisateur::terminerPartie() {
    try {
        hive.terminerPartie();
    }
    catch (const HiveException& e) {
        cout << "Erreur : " << e.getInfo() << endl;
    }
}

// Partie à supprimer
void InterfaceUtilisateur::supprimerPartie() {
    int idPartie;
    if (hive.nombreParties() != 0) {
        afficherParties();
        cout << "Entrez l'ID de la partie à supprimer : ";
        cin >> idPartie;
    }
    else {
        idPartie = 0;
    }
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