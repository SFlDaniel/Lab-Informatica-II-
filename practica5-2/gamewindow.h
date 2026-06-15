#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsEllipseItem>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QTimer>
#include <QLabel>
#include <QFont>
#include <QColor>
#include <vector>

#include "juego.h"
#include "panelcontrol.h"

class GameWindow : public QWidget
{
    Q_OBJECT

private:
    Juego             juego;
    QGraphicsScene*   scene;
    QGraphicsView*    view;
    PanelControl*     panel;
    QLabel*           turnoLabel;
    QLabel*           vidaLabel;
    QTimer*           timer;

    QGraphicsEllipseItem* jugador1Item;
    QGraphicsEllipseItem* jugador2Item;

    std::vector<QGraphicsEllipseItem*> proyectilesGraficos;

    void crearEscena();

private slots:
    void actualizarGUI();
    void lanzarProyectil();

public:
    explicit GameWindow(QWidget *parent = nullptr);
};

#endif // GAMEWINDOW_H