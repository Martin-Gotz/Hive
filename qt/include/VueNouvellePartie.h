#pragma once

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QCheckBox>
#include "Enums.h"

class VueNouvellePartie : public QDialog {
    Q_OBJECT

public:
    explicit VueNouvellePartie(QWidget* parent = nullptr);

    QString getNomJoueur1() const;
    QString getNomJoueur2() const;
    JeuHive::TypeJoueur getTypeJoueur1();
    JeuHive::TypeJoueur getTypeJoueur2();

private:
    QLineEdit* nomJoueur1Edit;
    QLineEdit* nomJoueur2Edit;
    QCheckBox* iaCheckBox;
    QPushButton* boutonOk;
    QPushButton* boutonAnnuler;
    QPushButton* boutonSupprimer;
    void initialiser();

private slots: 
    void supprimerPartie();
};
