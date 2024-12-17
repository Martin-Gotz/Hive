#include "./include/Hive.h"
#include "./include/InterfaceUtilisateur.h"
#include <QApplication>
#include "./qt/include/MainWindow.h"

using namespace std;
using namespace JeuHive;

int main(int argc, char* argv[]) {

    Hive& hive = Hive::getInstance();
    InterfaceUtilisateur ui(hive);
    ui.gererChoixUtilisateur();


    QApplication app(argc, argv);

    MainWindow w;
    w.show();

    return app.exec();
}