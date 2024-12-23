#include "../include/Partie.h"
#include <random>
using namespace JeuHive;
using namespace std;


// Initialisation du compteur statique
int Partie::prochain_id = 1;


//Constructeurs
Partie::Partie(Joueur& j1, Joueur& j2, JoueurIa* Ia, int nombreRetours, int dif) :
    id(prochain_id),
    joueur1(j1),
    joueur2(j2),
    plateau(),
    regles(),
    historique(),
    compteurRegles(0),
    etatPartie(EtatPartie::NON_COMMENCEE),
    joueurActuel(nullptr),
    compteurTour(0),
    nombreRetours(nombreRetours),
    difficulte(dif),
    Victorieux(nullptr),
    j(Ia)
{
    prochain_id++; // Incrémentation du compteur statique pour suivre le nombre de parties créé
    regles.setNombreRetours(nombreRetours);
    /*
    if (joueur2.getType() == IA) {
        switch (difficulte) {
        case 1:
            j = new JoueurIaFacile(&joueur2, compteurTour, &plateau);
            break;
        case 2:
            j = new JoueurIaMoyen(&joueur2, compteurTour, &plateau);
            break;
        case 3:
            j = new JoueurIaDifficile(&joueur2, compteurTour, &plateau);
            break;
        default:
            j = new JoueurIaFacile(&joueur2, compteurTour, &plateau);
            break;
        }
    }*/
}


// Methodes principales
void Partie::demarrer() {
    if (etatPartie == EtatPartie::EN_COURS) {
        throw HiveException("La partie est déjà en cours !");
    }

    if (etatPartie == EtatPartie::TERMINEE) {
        throw HiveException("La partie est terminée !");
    }


    // Si la partie n'a jamais commencé, il faut la mettre en place. Sinon, on la reprend.
    if (etatPartie == EtatPartie::NON_COMMENCEE) {
        initialiser();
    }
    else {
        reprendre();
    }

    etatPartie = EtatPartie::EN_COURS;

    if (compteurTour == 1 && joueurActuel->getType() == IA)
    {
        jouerCoupIA();
    }

}


// Mise en place des éléments la première fois que la partie est lancée
void Partie::initialiser() {
    // 1 : Initialisation des joueurs (et pièces)

    // Génération aléatoire de la couleur
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(0, 1);

    if (distrib(gen) == 0) {
        joueur1.setCouleur(Couleur::BLANC);
        joueur2.setCouleur(Couleur::NOIR);
        joueurActuel = &joueur1; // Le joueur blanc commence
    }
    else {
        joueur1.setCouleur(Couleur::NOIR);
        joueur2.setCouleur(Couleur::BLANC);
        joueurActuel = &joueur2; // Le joueur blanc commence
    }

    FabriquePiece fabrique = initialiserFabriquePiece();
    joueur1.remplirMain(fabrique);
    joueur2.remplirMain(fabrique);

    // 3 : Règles spécifiques de début de partie
    compteurTour = 1;

    EvenementPartie evt(id, TypeEvenement::DEBUT_PARTIE);
    notifierObservers(evt);

}

void Partie::reprendre() {
    EvenementPartie evt(id, TypeEvenement::REPRISE_PARTIE);
    notifierObservers(evt);
}

void Partie::mettreEnPause() {
    if (etatPartie != EtatPartie::EN_COURS) {
        throw HiveException("La partie n'est pas en cours");
    }

    etatPartie = EtatPartie::EN_PAUSE;
    EvenementPartie evt(id, TypeEvenement::PAUSE_PARTIE);
    notifierObservers(evt);
}

void Partie::terminer() {
    if (etatPartie != EtatPartie::EN_COURS) {
        throw HiveException("Impossible de terminer une partie qui n'est pas en cours !");
    }

    etatPartie = EtatPartie::TERMINEE;
    EvenementPartie evt(id, TypeEvenement::FIN_PARTIE);
    notifierObservers(evt);
}






void Partie::placerPiece(int idPiece, const Coordonnee& cooDestination) {
    if (joueurActuel->getMain().estVide()) {
        throw HiveException("Plus de pièce dans la main !");
    }

    if (idPiece <= 0 || idPiece > joueurActuel->getMain().getPieces().size()) {
        throw HiveException("ID de pièce invalide !");
    }

    Piece* piece = joueurActuel->getMain().getPieces()[idPiece - 1];

    // Construire un coup de placement
    Coup* coup = new CoupPlacement(piece, cooDestination, compteurTour);
    
    // Jouer le coup
    jouerCoup(coup);

    

    // Retirer la pièce de la main du joueur
    joueurActuel->retirerPiece(piece);

    joueurSuivant();
}

void Partie::deplacerPiece(const Coordonnee& cooOrigine, const Coordonnee& cooDestination) {

    const Case* case0 = plateau.getCaseDeCoo(cooOrigine);

    if (case0 == nullptr) {
        throw HiveException("Aucune pièce n'est située à ces coordonnées");
        return;
    }

    const Piece* piece = case0->getDessus();

    if (piece->getCouleur() != joueurActuel->getCouleur()) {
        throw HiveException("Vous ne pouvez déplacer que vos propres pièces !");
        return;
    }

    // Construire un coup de déplacement
    Coup* coup = new CoupDeplacement(piece, cooOrigine, cooDestination, compteurTour);

    // Jouer le coup
    jouerCoup(coup);

    joueurSuivant();
}



void Partie::jouerCoup(Coup* coup) {
    // Appliquer le coup sur le plateau
    plateau.jouerCoup(*coup);

    // Ajouter le coup à l'historique
    historique.ajouterCoup(*coup);

    // Créer et notifier un événement selon le type de coup
    TypeEvenement typeEvt = (dynamic_cast<CoupPlacement*>(coup) != nullptr)
        ? TypeEvenement::PIECE_PLACEE
        : TypeEvenement::PIECE_DEPLACEE;
    EvenementPartie evt(id, typeEvt);
    notifierObservers(evt);

    //CompteurRegles--;
    delete coup;
}



void Partie::jouerCoupIA()
{
    if (joueurActuel->getType() != IA)
    {
        throw HiveException("Erreur, le joueur n'est pas une IA !");
        return;
    }
    j->actualiser(joueurActuel, &plateau, compteurTour);
    Coup* coupChoisi = j->choisirCoup();

    if (CoupPlacement* coupPlacement = dynamic_cast<CoupPlacement*>(coupChoisi))
    {
        // Trouver l'index de la pièce dans la main du joueur
        const auto& pieces = joueurActuel->getMain().getPieces();
        auto it = find(pieces.begin(), pieces.end(), coupPlacement->getPiece());
        if (it != pieces.end())
        {
            int indexPiece = distance(pieces.begin(), it) + 1; // +1 car l'index est basé sur 1
            placerPiece(indexPiece, coupPlacement->getCooDestination());
            cout << "IA a placé la pièce " << coupPlacement->getPiece()->getNom() << " en " << coupPlacement->getCooDestination().get_q() << ", " << coupPlacement->getCooDestination().get_r() << endl;
        }
    }
    else if (CoupDeplacement* coupDeplacement = dynamic_cast<CoupDeplacement*>(coupChoisi))
    {
        deplacerPiece(coupDeplacement->getCooOrigine(), coupDeplacement->getCooDestination());
        cout << "IA a déplacé la pièce " << coupDeplacement->getPiece()->getNom() << " de " << coupDeplacement->getCooOrigine().get_q() << ", " << coupDeplacement->getCooOrigine().get_r() << " à " << coupDeplacement->getCooDestination().get_q() << ", " << coupDeplacement->getCooDestination().get_r() << endl;
    }

    joueurActuel = (joueurActuel->getNom() == joueur1.getNom()) ? &joueur2 : &joueur1;
    cout << "\nL'IA a joué son coup !\n";
    joueurSuivant();
}

void Partie::joueurSuivant() {
    if (etatPartie != EtatPartie::EN_COURS) {
        throw HiveException("Impossible de passer le tour d'une partie qui n'est pas en cours !");
    }
    if(verifierEtatPartie())
    { 
        if (joueurActuel->getCouleur() == Couleur::NOIR) {
            compteurTour++;
            EvenementPartie evt(id, TypeEvenement::TOUR_SUIVANT);
            notifierObservers(evt);
        }

        joueurActuel = (joueurActuel->getNom() == joueur1.getNom()) ? &joueur2 : &joueur1; // Le getNom est temporaire en attendant l'opérateur de comparaison
        
        if (joueurActuel->getType() == IA && joueurActuel != nullptr)
        {
            jouerCoupIA();
        }
        
        EvenementPartie evt(id, TypeEvenement::CHANGEMENT_JOUEUR);
        notifierObservers(evt);        
    }
    else
    {
        throw HiveException("Le vainqueur a déjà été déterminé !");
    }
}



// Formatage des données pour l'abstraction de l'affichage
ResumePartie Partie::resumer() const {

    ResumePartie resume;

    resume.id = id;
    resume.joueur1.nom = joueur1.getNom();
    resume.joueur2.nom = joueur2.getNom();
    resume.joueur1.couleur = joueur1.getCouleur();
    resume.joueur2.couleur = joueur2.getCouleur();
    resume.joueur1.main = joueur1.getMain().resumer();
    resume.joueur2.main = joueur2.getMain().resumer();
    if (joueur1.getType() == HUMAIN) resume.joueur1.type = "HUMAIN";
    else resume.joueur1.type = "IA";
    if (joueur2.getType() == HUMAIN) resume.joueur2.type = "HUMAIN";
    else resume.joueur2.type = "IA";

    switch (etatPartie) {
        case EtatPartie::NON_COMMENCEE:
            resume.etatPartie = "Non commencee";
            break;
        case EtatPartie::EN_COURS:
            resume.etatPartie = "En cours";
            break;
        case EtatPartie::EN_PAUSE:
            resume.etatPartie = "En pause";
            break;
        case EtatPartie::TERMINEE:
            resume.etatPartie = "Terminée";
            break;
    }
    return resume;
}





bool Partie::verifierEtatPartie() {
    if (plateau.estPartieFinie())
    {
        switch (plateau.Gagnant())
        {
        case BLANC:
            if (joueur1.getCouleur() == BLANC)
            {
                Victorieux = &joueur1;
            }
            else 
            {
                Victorieux = &joueur2;
            }
        case NOIR:
            if (joueur1.getCouleur() == NOIR)
            {
                Victorieux = &joueur1;
            }
            else
            {
                Victorieux = &joueur2;
            }
        }
        cout << Victorieux->getNom() << " a gagné ! \n";
        terminer();
        return false;
    }
    else return true;
}

void JeuHive::Partie::annulerDernierCoup()
{
    if (historique.getlisteCoups().empty()) {
        throw HiveException("Il n'y a aucun coup à annuler.");
    }

    Coup* dernierCoup = historique.getlisteCoups().back();
    historique.annulerDernierCoup();
    joueurActuel = (joueurActuel->getNom() == joueur1.getNom()) ? &joueur2 : &joueur1;

    if (dernierCoup) {
        CoupDeplacement* deplacement = dynamic_cast<CoupDeplacement*>(dernierCoup);
        if (deplacement) {
            // Remettre la pièce à sa position d'origine
            plateau.inverserDeplacement(deplacement);
        }

        CoupPlacement* placement = dynamic_cast<CoupPlacement*>(dernierCoup);
        if (placement) {
            // Retirer la pièce du plateau et la remettre dans la main du joueur
            plateau.inverserPlacement(placement);
            joueurActuel->ajouterPieceMain(const_cast<Piece*>(placement->getPiece()));
        }

        // Décrémenter le compteur de tours si nécessaire
        if (joueurActuel->getCouleur() == Couleur::NOIR) {
            compteurTour--;
        }
    }

    incrementerCompteurRegles();

    EvenementPartie evt(id, TypeEvenement::ANNULER_COUP);
    notifierObservers(evt);

    dernierCoup = nullptr;
}


void JeuHive::Partie::verifierAnnulation()
{
    if (compteurRegles > regles.getNombreRetours())
    {
        throw HiveException("Le nombre de retours en arrière est trop important");
    }
    else
    {
       annulerDernierCoup();
       compteurRegles++;
    }
}

// annuler X nombre de coups reviendrait à faire une boucle for allant de 0 à X de annulerDernierCoup ?
