#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>

#include <QGraphicsScene>
#include <QGraphicsView>

#include <QGraphicsEllipseItem>
#include <QGraphicsRectItem>

#include <QTimer>

#include <vector>

#include "juego.h"

class GameWindow : public QWidget
{
    Q_OBJECT

private:

    Juego juego;

    QGraphicsScene* scene;

    QGraphicsView* view;

    QTimer* timer;

    std::vector<QGraphicsEllipseItem*>
        proyectilesGraficos;

    std::vector<QGraphicsRectItem*>
        infraestructurasGraficas;

    void crearEscena();

    void actualizarGUI();

    PanelControl* panel;

public:

    GameWindow(QWidget *parent = nullptr);

};

#endif