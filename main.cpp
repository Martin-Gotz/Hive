using namespace std;
#include "./include/Hive.h"
#include "./include/InterfaceUtilisateur.h"

using namespace std;
using namespace JeuHive;

int main() {

    Hive& hive = Hive::getInstance();
    InterfaceUtilisateur ui(hive);
    ui.gererChoixUtilisateur();

    /*
    Plateau pla;
    Abeille A_b(BLANC);
    Abeille A_n(NOIR);
    Araignee a_b(BLANC);

    pla.ajouterPieceSurCoo(A_b, Coordonnee(0, 0));
    */

    return 0;
}