using namespace std;
#include "./include/Hive.h"

using namespace std;
using namespace JeuHive;

int main() {
    try {
        Joueur joueur1("Alice");
        Joueur joueur2("Bob");
        Joueur joueur3("Michel");
        Joueur joueur4("Francis");

        Hive hive;

        cout << "\n== Liste des parties avant ajout ==" << endl;
        hive.afficherParties();

        // Ajout de parties
        hive.ajouterPartie(Partie(1, &joueur1, &joueur2));
        hive.ajouterPartie(Partie(2, &joueur3, &joueur4));
        hive.ajouterPartie(Partie(3, &joueur1, &joueur4));

        cout << "\n== Liste des parties après ajout ==" << endl;
        hive.afficherParties();



        // Démarrer une partie
        cout << "\n== Démarrer la partie 2 ==" << endl;
        hive.demarrerPartie(1);

        // Terminer la partie en cours
        cout << "\n== Terminer la partie en cours ==" << endl;
        hive.terminerPartie();

        // Supprimer une partie
        cout << "\n== Supprimer la partie 1 ==" << endl;
        hive.supprimerPartie(0);

        cout << "\n== Liste des parties après suppression ==" << endl;
        hive.afficherParties();

    }
    catch (const HiveException& e) {
        cerr << "Erreur : " << e.getInfo() << endl;
    }
    catch (const exception& e) {
        cerr << "Exception inattendue : " << e.what() << endl;
    }

    return 0;
}