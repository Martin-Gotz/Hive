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
    afficherInformationsPartie();
    cout << "Que shouhaitez vous faire ?\n";
    cout << "1. Poser une piece" << endl;
    cout << "2. Deplacer une piece" << endl;
    cout << "3. Retour au menu principal" << endl;
    cout << "4. Abandonner la partie" << endl;
}





// ===== GESTION DES MENUS =====

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

        try {
            switch (choix) {
                case 1: placerPiece(); break;
                case 2: deplacerPiece(); break;
                case 3: retournerMenu(); return;
                case 4: terminerPartieEnCours(); return;
                default: cout << "Option invalide, veuillez réessayer." << endl;
            }
        }
        catch (const HiveException& e) {
            cout << "Erreur : " << e.getInfo() << '\n';
        }

        cout << endl << endl;
    }
}







// ===== METHODES RELATIVES A HIVE =====

// Demander à l'utilisateur les informations nécessaires pour ajouter une partie
void InterfaceUtilisateur::ajouterPartie() {

    //TypeJoueur typeJoueur1 = demanderTypeJoueur("joueur 1");
    //cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string nomJoueur1, nomJoueur2;
    do {
        cout << "Entrez le nom du joueur 1 : ";
        getline(cin, nomJoueur1);
        if (nomJoueur1.empty()) {
            cout << "Le nom du joueur 1 ne peut pas être vide. Essayez encore." << endl;
        }
    } while (nomJoueur1.empty());

    //TypeJoueur typeJoueur2 = demanderTypeJoueur("joueur 2");
    //cin.ignore(numeric_limits<streamsize>::max(), '\n');

    do {
        cout << "Entrez le nom du joueur 2 : ";
        getline(cin, nomJoueur2);
        if (nomJoueur2.empty()) {
            cout << "Le nom du joueur 2 ne peut pas etre vide. Essayez encore." << endl;
        }
    } while (nomJoueur2.empty());

    cout << endl;

    //hive.ajouterPartie(nomJoueur1, typeJoueur1, nomJoueur2, typeJoueur2);
    hive.ajouterPartie(nomJoueur1, TypeJoueur::HUMAIN, nomJoueur2, TypeJoueur::IA);
}


// Permet de gérer l'entrée utilisateur correspondant aux types des joueurs
TypeJoueur InterfaceUtilisateur::demanderTypeJoueur(const string& nomJoueur) {
    string entree;
    int choix;

    do {
        cout << "Quel est le type de " << nomJoueur << " ? (0 pour HUMAIN, 1 pour IA) : ";
        cin >> entree;

        // Vérifie si l'entrée est un entier valide
        try {
            choix = stoi(entree);
        }
        catch (const invalid_argument&) {
            choix = -1; // Valeur hors intervalle pour forcer la boucle à continuer
        }
        catch (const out_of_range&) {
            choix = -1;
        }

        if (choix != 0 && choix != 1) {
            cout << "Entrée invalide. Veuillez entrer 0 pour HUMAIN ou 1 pour IA." << endl;
        }
    } while (choix != 0 && choix != 1);

    return static_cast<TypeJoueur>(choix);
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
            // Démarre la partie
            hive.demarrerPartie(idPartie);

            // Si la partie est trouvée, on ajoute l'observateur
            partieObservee->ajouterObserver(this);

            cout << endl << endl;
            cout << "-------------------- Partie " << to_string(partieObservee->getId()) << " --------------------" << endl;

            gererChoixUtilisateurMenuPartie();
        }
        else {
            // Si la partie n'a pas été trouvée
            throw HiveException("Aucune partie trouvée avec cet ID.");
        }
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

void JeuHive::InterfaceUtilisateur::placerPiece() {
    int idTypePiece;
    int x, y;

    cout << "Entrez l'id dans la main de la pièce a placer : ";
    cin >> idTypePiece;

    if (!hive.getPartieEnCours()->getPlateau().estVide()) {
        cout << "Entrez les coordonnées de la case (x y) : ";
        cin >> x >> y;
    }
    else {
        x = 0;
        y = 0;
    }


    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Entrée invalide. Veuillez réessayer.\n";
        return;
    }

    hive.getPartieEnCours()->placerPiece(idTypePiece, { x, y });
    cout << "Pièce " << idTypePiece << " placée en (" << x << ", " << y << ").\n";
}

void JeuHive::InterfaceUtilisateur::deplacerPiece() {
    int x1, y1, x2, y2;


    if (hive.getPartieEnCours()->getPlateau().estVide()) {
        cout << "Erreur : le plateau est vide\n";
        return;
    }

    cout << "Entrez les coordonnées de la pièce a déplacer (x1 y1) : ";
    cin >> x1 >> y1;

    cout << "Entrez les coordonnées de destination (x2 y2) : ";
    cin >> x2 >> y2;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Entrée invalide. Veuillez réessayer.\n";
        return;
    }

    hive.getPartieEnCours()->deplacerPiece({ x1, y1 }, { x2, y2 });
    cout << "Piece déplacée de (" << x1 << ", " << y1 << ") a (" << x2 << ", " << y2 << ").\n";
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







// ===== METHODES D'AFFICHAGE =====

// Afficher toutes les parties
void InterfaceUtilisateur::afficherParties() const {
    EtatHive etat = hive.getEtatHive(); // Récupère l'état des parties

    if (etat.parties.empty()) {
        cout << "Aucune partie n'est enregistree." << endl << endl;
        return;
    }

    cout << "Liste des parties :" << endl;
    for (const auto& resume : etat.parties) {
        cout << resume.id
            << " : " << resume.joueur1.nom << " vs " << resume.joueur2.nom
            << " - " << resume.etatPartie << endl;
    }
}


// Afficher l'état de la partie au tour en question
void JeuHive::InterfaceUtilisateur::afficherInformationsPartie() const
{
    if (!hive.getPartieEnCours()) {
        return;
    }

    cout << "\n============ Tour n°" << hive.getPartieEnCours()->getCompteurTour() << " ============\n" << endl;

    cout << "-> C'est a " << hive.getPartieEnCours()->getJoueurActuel()->getNom() << " de jouer" << endl;

    afficherInformationsJoueurs();
    afficherPlateau();
}



// Méthodes pour afficher les joueurs et leurs mains (dans une partie en cours)

void JeuHive::InterfaceUtilisateur::afficherInformationsJoueurs() const
{
    const auto partieEnCours = hive.getPartieEnCours();
    const auto joueurActuel = partieEnCours->getJoueurActuel();

    cout << "\n----------- Joueurs -----------\n" << endl;

    bool estJoueurActuel = (joueurActuel == &(partieEnCours->getJoueur1()));

    // Mettre en évidence le joueur actuel
    afficherJoueur("Joueur 1", partieEnCours->getJoueur1().resumer(), estJoueurActuel);
    afficherJoueur("Joueur 2", partieEnCours->getJoueur2().resumer(), !estJoueurActuel);
}

void JeuHive::InterfaceUtilisateur::afficherJoueur(const string& titre, const ResumeJoueur& joueur, bool estJoueurActuel) const
{
    cout << "[ " << titre << " : " << joueur.nom << " (" << joueur.type << ")" << " ]" << (estJoueurActuel ? " *JOUEUR ACTUEL*" : "") << endl;
    cout << "Couleur : " << joueur.couleur << "\n";
    afficherMain(joueur.main);
    cout << endl;
}


void JeuHive::InterfaceUtilisateur::afficherMain(const ResumeMain& main) const
{
    cout << "Main : " << main.nombre_pieces_restantes << " pièce(s) restante(s)\n";
    if (main.pieces.empty()) {
        cout << "   Aucune pièce dans la main.\n";
    }
    else {
        cout << "   Pièces : ";
        int numero = 1;
        for (const auto& piece : main.pieces) {
            cout << numero << ". " << piece.nom << " ";
            ++numero;
        }
        cout << '\n';
    }
}




// Affichage du plateau
void JeuHive::InterfaceUtilisateur::afficherPlateau() const
{
    cout << "\n----------- Plateau -----------\n" << endl;

    if (hive.getPartieEnCours()->getPlateau().estVide()) {
        cout << "Plateau vide.\n" << endl;
    }
    else {
        cout << hive.getPartieEnCours()->getPlateau() << endl;
    }
}




// Reaction aux observable
void InterfaceUtilisateur::afficherEvenement(const Evenement& e) const {
    // Afficher le message de l'observable si il existe
    if (!e.getDescription().empty()) {
        cout << e.getDescription() << endl;
    }

    /*
    // Vérifier si l'événement est un EvenementPartie
    if (const EvenementPartie* evtPartie = dynamic_cast<const EvenementPartie*>(&e)) {
        
    }
    */

    // Affichages supplémentaires
    if (e.getType() == TypeEvenement::DEBUT_PARTIE) {
        cout << "La partie a commencé !" << endl;
    }
    else if (e.getType() == TypeEvenement::REPRISE_PARTIE) {
        cout << "La partie a repris." << endl;
    }
    else if (e.getType() == TypeEvenement::FIN_PARTIE) {
        cout << "La partie est terminée." << endl;
    }
    else if (e.getType() == TypeEvenement::PAUSE_PARTIE) {
        cout << "La partie est en pause." << endl;
    }
    else if (e.getType() == TypeEvenement::TOUR_SUIVANT) {
        cout << "Tour suivant" << endl;
    }
    else if (e.getType() == TypeEvenement::CHANGEMENT_JOUEUR) {
        cout << "Changement de joueur" << endl;
    }
}

// Action de l'observateur
void InterfaceUtilisateur::reagir(const Evenement& e) {
    afficherEvenement(e);
}