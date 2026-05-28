#include "gamewindow.h"
#include <QPainter>
#include <QString>

static const double DT = 0.1;

static const QColor COLORES[] = {
    QColor(70,  130, 255),
    QColor(255,  80,  80),
    QColor( 80, 220, 100),
    QColor(255, 180,  30),
    QColor(200,  80, 255),
};
static const int N_COLORES = 5;

GameWindow::GameWindow(QWidget *parent)
    : QWidget(parent), exportador("trayectoria.txt"), tiempo(0.0)
{
    setFixedSize(ANCHO, ALTO);
    setWindowTitle("Simulacion Colisiones Multiples - Practica 5");
    inicializarEscena();
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &GameWindow::actualizarFrame);
    timer->start(16);
}

GameWindow::~GameWindow()
{
    exportador.cerrar();
}

void GameWindow::inicializarEscena()
{
    fisica.agregarParticula(new Particula(100, 100, 80,  45, 10));
    fisica.agregarParticula(new Particula(400, 200, 60, 135, 20));
    fisica.agregarParticula(new Particula(300, 500, 90,  70, 15));
    fisica.agregarParticula(new Particula(700, 300, 75, 210, 12));

    fisica.agregarObstaculo(new Obstaculo(350, 250, 120, 40, 0.7));
    fisica.agregarObstaculo(new Obstaculo(600, 450, 100, 50, 0.6));
}

void GameWindow::actualizarFrame()
{
    fisica.actualizarSistema(DT, ANCHO, ALTO);
    exportador.guardar(fisica, tiempo);
    tiempo += DT;
    update();
}

void GameWindow::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    p.fillRect(rect(), QColor(20, 20, 35));

    p.setPen(QPen(QColor(180, 180, 200), 2));
    p.setBrush(Qt::NoBrush);
    p.drawRect(1, 1, ANCHO - 2, ALTO - 2);

    p.setBrush(QColor(90, 90, 110));
    p.setPen(QPen(QColor(160, 160, 180), 1));
    p.drawRect(QRectF(350, 250, 120, 40));
    p.drawRect(QRectF(600, 450, 100, 50));
    p.setPen(Qt::white);
    p.setFont(QFont("Arial", 8));
    p.drawText(QRectF(350, 250, 120, 40), Qt::AlignCenter, "e=0.7");
    p.drawText(QRectF(600, 450, 100, 50), Qt::AlignCenter, "e=0.6");

    auto& ps = fisica.getParticulas();
    for (size_t i = 0; i < ps.size(); i++) {
        double r  = ps[i]->getRadio();
        double cx = ps[i]->getX();
        double cy = ps[i]->getY();
        QColor c  = COLORES[i % N_COLORES];

        p.setBrush(QColor(0, 0, 0, 60));
        p.setPen(Qt::NoPen);
        p.drawEllipse(QRectF(cx-r+3, cy-r+3, r*2, r*2));

        p.setBrush(c);
        p.setPen(QPen(c.lighter(160), 1.5));
        p.drawEllipse(QRectF(cx-r, cy-r, r*2, r*2));

        p.setPen(Qt::white);
        p.setFont(QFont("Arial", 7, QFont::Bold));
        p.drawText(QRectF(cx-r, cy-r, r*2, r*2), Qt::AlignCenter,
                   QString("m=%1").arg(ps[i]->getMasa(), 0, 'f', 0));
    }

    p.setPen(QColor(220, 220, 220));
    p.setFont(QFont("Arial", 10));
    p.drawText(10, 20,
               QString("t = %1 s    Particulas: %2")
                   .arg(tiempo, 0, 'f', 2).arg(ps.size()));

    p.setFont(QFont("Arial", 8));
    p.setPen(QColor(160, 200, 160));
    p.drawText(10, ALTO - 30, "Paredes: rebote elastico");
    p.setPen(QColor(200, 160, 100));
    p.drawText(10, ALTO - 15, "Obstaculos: inelastico  |  Particulas: fusion inelastica");
}