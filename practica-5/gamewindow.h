#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QTimer>
#include <QPainter>
#include <fstream>
#include "fisica.h"

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
    QTimer*     timer;
    std::ofstream archivo;
    double      tiempo;

    void inicializarParticulas();
    void inicializarObstaculos();
    void guardarEstado();
};

#endif // GAMEWINDOW_H
