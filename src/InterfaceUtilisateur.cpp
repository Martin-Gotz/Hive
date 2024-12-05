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
    cout << "\n======== Menu ========" << endl;
    cout << "1. Ajouter une nouvelle partie" << endl;
    cout << "2. D�marrer une partie" << endl;
    cout << "3. Supprimer une partie" << endl;
    cout << "4. Afficher les parties" << endl;
    cout << "5. Quitter" << endl;
    cout << "Entrez votre choix : ";
}


// Logique de validation des entr�es
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

// Gestion des choix de l'utilisateur
void InterfaceUtilisateur::gererChoixUtilisateur() {
    int choix = -1;

    while (true) {
        afficherMenu();
        int choix = obtenirEntreeUtilisateur("Veuillez entrer votre choix : ", true);
        cout << "---------------------" << endl;

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
            cout << "Option invalide, veuillez r�essayer." << endl;
        }

        cout << endl << endl;
    }
}


// Demander � l'utilisateur les informations n�cessaires pour ajouter une partie
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

// Partie � d�marrer
void InterfaceUtilisateur::demarrerPartie() {
    if (hive.nombreParties() == 0) {
        cout << "Aucune partie � d�marrer." << endl;
        return;
    }

    if (hive.getPartieEnCours() != nullptr) {
        cout << "Une partie est d�j� en cours." << endl;
        return;
    }

    afficherParties();
    cout << endl;
    int idPartie = obtenirEntreeUtilisateur("Entrez l'ID de la partie � d�marrer : ");
    cout << endl;

    // V�rification de la valeur en cas d'entr�e invalide
    if (idPartie == -1) {
        return;
    }

    try {
        partieObservee = hive.getPartie(idPartie);

        if (partieObservee) {
            partieObservee->ajouterObserver(this);
        }

        hive.demarrerPartie(idPartie);
        cout << endl << endl << endl;
        gererChoixUtilisateurMenuPartie();
    }
    catch (const HiveException& e) {
        cout << "Erreur : " << e.getInfo() << endl;
    }
}


// Partie � supprimer
void InterfaceUtilisateur::supprimerPartie() {
    if (hive.nombreParties() == 0) {
        cout << "Aucune partie � supprimer." << endl;
        return;
    }

    afficherParties();
    cout << endl;
    int idPartie = obtenirEntreeUtilisateur("Entrez l'ID de la partie � supprimer : ");
    cout << endl;
    
    // V�rification de la valeur en cas d'entr�e invalide
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

// Afficher toutes les parties
void InterfaceUtilisateur::afficherParties() {
    hive.afficherParties();
}







// PARTIE EN COURS
// Afficher le menu de la partie en cours
void InterfaceUtilisateur::afficherMenuPartie() const {
    cout << "\n===== PARTIE ===== " << endl;
    cout << "1. Jouer un coup" << endl;
    cout << "2. Terminer la partie" << endl;
    cout << "3. Retour au menu principal" << endl;
    cout << "Entrez votre choix : ";
}

// Gestion des choix du menu de la partie en cours
void InterfaceUtilisateur::gererChoixUtilisateurMenuPartie() {
    int choix = -1;

    while (true) {
        afficherMenuPartie();
        int choix = obtenirEntreeUtilisateur("Veuillez entrer votre choix : ");
        cout << "---------------------" << endl;

        switch (choix) {
        case 1:
            jouerCoup();
            break;
        case 2:
            terminerPartieEnCours();
            return;
        case 3:
            retournerMenu();
            return; // Retour au menu principal apr�s la terminaison de la partie
        default:
            cout << "Option invalide, veuillez r�essayer." << endl;
        }

        cout << endl << endl;
    }
}

// Jouer un coup dans la partie en cours
void InterfaceUtilisateur::jouerCoup() {
    cout << "Entrez le coup � jouer : ";
    string coup;
    cin >> coup;

    // Jouer le coup dans la partie en cours
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




void InterfaceUtilisateur::afficherEvenement(const Evenement& evenement) const {
    cout << evenement.getDescription() << endl;
}

// Action de l'observateur
void InterfaceUtilisateur::reagir(const Evenement& evenement) {
    afficherEvenement(evenement);
}