using namespace std;
#include "./include/Hive.h"
#include "./include/InterfaceUtilisateur.h"

using namespace std;
using namespace JeuHive;

int main() {
    /*
    Plateau pla;
    Abeille A_b(BLANC);
    Abeille A_n(NOIR);
    Araignee a_b(BLANC);
    Sauterelle s_n(NOIR);
    Scarabee S_b(BLANC);
    Fourmi F_n(NOIR);
    Fourmi F_b(BLANC);


    pla.ajouterPieceSurCoo(A_b, Coordonnee(0, 0));
    pla.ajouterPieceSurCoo(A_n, Coordonnee(0, 1));
    pla.ajouterPieceSurCoo(a_b, Coordonnee(1, 0));
    pla.ajouterPieceSurCoo(s_n, Coordonnee(-1, 1));
    pla.ajouterPieceSurCoo(S_b, Coordonnee(1, -1));
    pla.ajouterPieceSurCoo(F_n, Coordonnee(-1, 0));
    //pla.ajouterPieceSurCoo(F_b, Coordonnee(0, 2));
    cout << pla;

    cout << pla.getNombreCases() << "\n";
    cout << pla.getNombrePieces() << "\n";
    cout << pla.estVide() << "\n";
    pla.retirerPieceDeCoo(Coordonnee(1, -1));

    vector<Coordonnee> surligner({ { -1, 1 }, {1, 1}, {2, 1}, {-1, 2}, {0, 0} });
    // cout << pla;
    pla.afficher(cout, surligner, {});

    pla.ajouterPieceSurCoo(S_b, Coordonnee(0, 0));

    cout << pla;

    Case* origine = pla.getCaseDeCoo(Coordonnee(0, 0));
    cout << " case origine: " << origine->getString() << "\n";
    vector<Case*> cases_voisines = pla.getVoisinsDeCoo(origine->getCoo());
    for (Case* case_voisine : cases_voisines) {
        cout << case_voisine->getString() << "\n";
    }


    cout << " ----------------------------------------- " << "\n";

    cout << pla;

    cout << " abeille placee " << pla.estAbeillePlacee(BLANC) << "\n";
    cout << " ----------------------------------------- " << "\n";

    set<Coordonnee> ensemble = pla.ensemblePlacementsPossibles(F_b, 2);
    for (Coordonnee cocacola : ensemble) {
        cout << cocacola << "\n";
    }

    pla.ajouterPieceSurCoo(F_b, Coordonnee(0, 2));

    cout << pla;

    cout << " ----------------------------------------- " << "\n";


    cout << "--------------------------------------------------------";
    cout << "deplacement possible \n";
    for (pair<Coordonnee, Case*> paire : pla.getCases()) {
        cout << paire.second->getString() << pla.deplacementPossible(*(paire.second->getDessus()), paire.first) << "\n";
    }

    cout << "--------------------------------------------------------";
    cout << "deplacements glissements \n";

    for (pair<Coordonnee, Case*> paire : pla.getCases()) {
        cout << "coos sont " << paire.first << paire.second->getString() << "\n";
        for (Coordonnee coo_voisine : pla.getCooVoisinesGlissement(paire.first)) {
            cout << coo_voisine << "\n";
        }
    }

    cout << pla;

    cout << "--------------------------------------------------------";
    cout << "deplacements  \n";
    vector<Coordonnee> cases_surlignees;
    set<Coordonnee> coos_possibles;
    for (pair<Coordonnee, Case*> paire : pla.getCases()) {
        cout << "-------------------------------\n";
        cout << "coos possoble " << paire.first << paire.second->getString() << "\n";
        coos_possibles = paire.second->getDessus()->ensembleDeplacementPossibles(pla, paire.first);
        for (Coordonnee coo_possible : coos_possibles) {
            cout << coo_possible << "\n";
        }
        cases_surlignees = vector<Coordonnee>(coos_possibles.begin(), coos_possibles.end());
        pla.afficher(cout, cases_surlignees, { paire.first });
    }
    */
    

    Hive& hive = Hive::getInstance();
    InterfaceUtilisateur ui(hive);
    ui.gererChoixUtilisateur();



    return 0;
}