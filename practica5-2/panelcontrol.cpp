#include "panelcontrol.h"

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

#include <QVBoxLayout>

PanelControl::PanelControl(
    QWidget *parent)
    : QWidget(parent)
{
    labelAngulo =
        new QLabel(
            "Angulo");

    labelVelocidad =
        new QLabel(
            "Velocidad");

    editAngulo =
        new QLineEdit;

    editVelocidad =
        new QLineEdit;

    botonDisparar =
        new QPushButton(
            "Disparar");
    QVBoxLayout* layout =
        new QVBoxLayout;

    layout->addWidget(
        labelAngulo);

    layout->addWidget(
        editAngulo);

    layout->addWidget(
        labelVelocidad);

    layout->addWidget(
        editVelocidad);

    layout->addWidget(
        botonDisparar);

    setLayout(layout);

    connect(
        botonDisparar,
        &QPushButton::clicked,
        this,
        &PanelControl::
        dispararSolicitado);
}

double PanelControl::obtenerAngulo()
{
    return editAngulo
        ->text()
        .toDouble();
}

double PanelControl::obtenerVelocidad()
{
    return editVelocidad
        ->text()
        .toDouble();
}

