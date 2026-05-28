#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QTimer>
#include <fstream>
#include <vector>
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
    Fisica  fisica;
    QTimer* timer;
    std::ofstream archivo;
    double  tiempo;

    static const int ANCHO = 800;
    static const int ALTO  = 600;

    void inicializarEscena();
    void guardarEstado();
};

#endif // GAMEWINDOW_H