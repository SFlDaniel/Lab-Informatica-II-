#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QTimer>
#include "fisica.h"
#include "exportador.h"

class GameWindow : public QWidget
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr);
    ~GameWindow();

protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void actualizarFrame();

private:
    Fisica      fisica;
    Exportador  exportador;
    QTimer*     timer;
    double      tiempo;

    static const int ANCHO = 1000;
    static const int ALTO  = 700;

    void inicializarEscena();
};

#endif