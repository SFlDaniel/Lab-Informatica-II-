#ifndef PANELCONTROL_H
#define PANELCONTROL_H

#include <QWidget>

class QLabel;
class QLineEdit;
class QPushButton;

class PanelControl : public QWidget
{
    Q_OBJECT

private:

    QLabel* labelAngulo;

    QLabel* labelVelocidad;

    QLineEdit* editAngulo;

    QLineEdit* editVelocidad;

    QPushButton* botonDisparar;

public:

    explicit PanelControl(
        QWidget *parent = nullptr);

    double obtenerAngulo();

    double obtenerVelocidad();

signals:

    void dispararSolicitado();
};

#endif