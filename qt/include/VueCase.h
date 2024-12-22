#pragma once

#include "Case.h"
#include "Enums.h"
#include <QPushButton>
#include <QPainter>
#include <QPolygonF>
#include <QPen>
#include <QBrush>
#include <cmath>

namespace JeuHive {
    class VueCase : public QPushButton {
        Q_OBJECT

    public:
        explicit VueCase(Coordonnee coord, QWidget* parent = nullptr) : coord(coord), QPushButton(parent), piece(nullptr), couleur(BLANC) {
            pen = QPen(Qt::black);
            brush = QBrush(Qt::white);
            setCheckable(true);

            // Rendre le fond transparent
            setStyleSheet("background-color: transparent; border: none;");
            setFlat(true);

            connect(this, &QPushButton::clicked, this, &VueCase::clickedEvent);

            updateHexagon();
        }

        // Dessiner l'hexagone
        void paintEvent(QPaintEvent* event) override {
            QPainter painter(this);
            // Définir la couleur de fond en fonction de la couleur de la case
            if (couleur == BLANC) {
                brush.setColor(Qt::white);
            }
            else {
                brush.setColor(Qt::black);
            }

            // Dessiner l'hexagone
            painter.setRenderHint(QPainter::Antialiasing);
            painter.setPen(pen);
            painter.setBrush(brush);
            painter.drawPolygon(hexagon);

            // Si une pièce est présente, dessiner son symbole
            if (piece) {
                painter.setPen(couleur == BLANC ? Qt::black : Qt::white);
                QFont font = painter.font();
                font.setPointSize(12);
                painter.setFont(font);
                painter.drawText(rect(), Qt::AlignCenter, QString::fromStdString(piece->getSymbole()));
            }
        }

        // Vérifie si le clic est dans l'hexagone
        bool hitButton(const QPoint& pos) const override {
            return hexagon.containsPoint(pos, Qt::OddEvenFill);
        }

        void updateHexagon() {
            int w = width();
            int h = height();

            QPointF center(w / 2.0, h / 2.0);
            int size = std::min(w, h) / 2.0;

            hexagon.clear();
            for (int i = 0; i < 6; ++i) {
                double angle = M_PI / 3.0 * i;
                hexagon << QPointF(center.x() + size * std::cos(angle), center.y() + size * std::sin(angle));
            }
        }

        void resizeEvent(QResizeEvent* event) override {
            updateHexagon();
            QPushButton::resizeEvent(event);
        }

        void setPiece(const JeuHive::Piece& p) {
            piece = &p;
            setCouleur(p.getCouleur());
            update();
        }

        void setNoPiece() {
            setCouleur(BLANC);
            piece = nullptr;
            update();
        }


        void setCouleur(Couleur c) {
            couleur = c;
            update();
        }

        const Coordonnee& getCoord() const {
            return coord;
        }

        const JeuHive::Piece& getPiece() const { return *piece; }
        bool piecePresente() const { return piece != nullptr; }

    private:
        const Piece* piece;
        Coordonnee coord;
        QPen pen;
        QBrush brush;
        QPolygonF hexagon;
        Couleur couleur;

    signals:
        void caseClicked(VueCase*);

    private slots:
        void clickedEvent() { emit caseClicked(this); }
    };
}