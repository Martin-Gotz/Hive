#pragma once

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

class VueNouvellePartie : public QDialog {
    Q_OBJECT

public:
    explicit VueNouvellePartie(QWidget* parent = nullptr);

    QString getNomJoueur1() const;
    QString getNomJoueur2() const;

private:
    QLineEdit* nomJoueur1Edit;
    QLineEdit* nomJoueur2Edit;
    QPushButton* okButton;
    QPushButton* cancelButton;
    QPushButton* deleteButton;
    void setupUI();

private slots: 
    void supprimerPartie();
};