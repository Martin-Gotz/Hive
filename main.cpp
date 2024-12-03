using namespace std;
#include "./include/Hive.h"
#include "./include/InterfaceUtilisateur.h"

using namespace std;
using namespace JeuHive;

int main() {
    Hive hive;
    InterfaceUtilisateur ui(hive);
    ui.gererChoixUtilisateur();

    return 0;
}