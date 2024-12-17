#include "../include/MainWindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Exemple : ajouter un texte sur un QLabel dans le MainWindow
    setWindowTitle("Test MainWindow");
}

MainWindow::~MainWindow()
{
    delete ui;
}
