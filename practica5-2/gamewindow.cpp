#include "gamewindow.h"

#include <QVBoxLayout>

GameWindow::GameWindow(QWidget *parent)
    : QWidget(parent)
{
    scene =
        new QGraphicsScene(this);

    view =
        new QGraphicsView(scene);

    timer =
        new QTimer(this);

    panel =
        new PanelControl;

    scene->setSceneRect(
        0,
        0,
        1000,
        700);

    crearEscena();

    QVBoxLayout* layout =
        new QVBoxLayout;

    layout->addWidget(view);
    layout->addWidget(panel);

    setLayout(layout);

    connect(
        timer,
        &QTimer::timeout,
        this,
        &GameWindow::actualizarGUI);
    connect(
        panel,
        &PanelControl::
        dispararSolicitado,
        this,
        &GameWindow::
        lanzarProyectil);

    timer->start(16);
}

void GameWindow::crearEscena()
{
    auto infra =
        new Infraestructura(
            400,
            400,
            120,
            40,
            100,
            0.7);

    juego.getFisica()
        .agregarInfraestructura(
            infra);

    QGraphicsRectItem* rect =
        scene->addRect(
            infra->getX(),
            infra->getY(),
            infra->getAncho(),
            infra->getAlto());

    infraestructurasGraficas
        .push_back(rect);
}

