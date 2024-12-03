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

        hive.afficherParties();

        // Ajout de parties
        hive.ajouterPartie(joueur1, joueur2);
        hive.ajouterPartie(joueur3, joueur4);
        hive.ajouterPartie(joueur1, joueur4);

        hive.afficherParties();



        // Démarrer une partie
        hive.demarrerPartie(1);

        // Terminer la partie en cours
        hive.terminerPartie();

        // Supprimer une partie
        hive.supprimerPartie(0);

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