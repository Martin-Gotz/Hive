#pragma once

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>

class VueNouvellePartie : public QDialog {
    Q_OBJECT

public:
    explicit VueNouvellePartie(QWidget* parent = nullptr);

    QString getNomJoueur1() const;
    QString getNomJoueur2() const;

private:
    QLineEdit* nomJoueur1Edit;
    QLineEdit* nomJoueur2Edit;
    QPushButton* boutonOk;
    QPushButton* boutonAnnuler;
    QPushButton* boutonSupprimer;
    void initialiser();

private slots: 
    void supprimerPartie();
};