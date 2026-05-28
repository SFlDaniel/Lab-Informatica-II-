#include "gamewindow.h"
#include <QPainter>
#include <QColor>
#include <QString>
#include <cmath>

static const double DT = 0.05;

static const QColor COLORES[] = {
    QColor(70, 130, 255),
    QColor(255,  80,  80),
    QColor( 80, 220, 100),
    QColor(255, 180,  30),
    QColor(200,  80, 255),
};
static const int N_COLORES = 5;

struct ObsData { double x, y, w, h; };
static const ObsData OBS[4] = {
    {160, 160, 90, 90},
    {550, 160, 90, 90},
    {160, 380, 90, 90},
    {550, 380, 90, 90},
    };

GameWindow::GameWindow(QWidget *parent)
    : QWidget(parent), tiempo(0.0)
{
    setFixedSize(ANCHO, ALTO);
    setWindowTitle("Simulación Colisiones Múltiples - Práctica 5");

    archivo.open("trayectorias.txt");
    if (archivo.is_open()) {
        archivo << "# SIMULACION DE COLISIONES MULTIPLES\n";
        archivo << "# tiempo  id  x  y  velX  velY  masa\n";
        archivo << "# COLISION  tiempo  tipo  info\n";
        archivo << "#--------------------------------------------------\n";
    }

    inicializarEscena();

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &GameWindow::actualizarFrame);
    timer->start(16);
}

GameWindow::~GameWindow()
{
    if (archivo.is_open()) archivo.close();
}

void GameWindow::inicializarEscena()
{
    fisica.agregarParticula(new Particula(100, 300, 90,  40, 1.0));
    fisica.agregarParticula(new Particula(700, 300, 90, 140, 1.5));
    fisica.agregarParticula(new Particula(400,  80, 70, 280, 2.0));
    fisica.agregarParticula(new Particula(400, 520, 80, 100, 1.2));

    for (int i = 0; i < 4; i++)
        fisica.agregarObstaculo(
            new Obstaculo(OBS[i].x, OBS[i].y, OBS[i].w, OBS[i].h, 0.6));
}

void GameWindow::actualizarFrame()
{
    guardarEstado();

    size_t nAntes = fisica.getParticulas().size();
    fisica.actualizarSistema(DT, ANCHO, ALTO);
    size_t nDespues = fisica.getParticulas().size();

    if (nDespues < nAntes && archivo.is_open())
        archivo << "COLISION  " << tiempo
                << "  particula-particula (fusion inelastica)"
                << "  particulas restantes: " << nDespues << "\n";

    tiempo += DT;
    update();
}

void GameWindow::guardarEstado()
{
    if (!archivo.is_open()) return;
    auto& ps = fisica.getParticulas();
    for (size_t i = 0; i < ps.size(); i++) {
        archivo << tiempo           << "  "
                << i                << "  "
                << ps[i]->getX()    << "  "
                << ps[i]->getY()    << "  "
                << ps[i]->getVelX() << "  "
                << ps[i]->getVelY() << "  "
                << ps[i]->getMasa() << "\n";
    }
}

void GameWindow::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    p.fillRect(rect(), QColor(20, 20, 35));

    p.setPen(QPen(QColor(180, 180, 200), 2));
    p.setBrush(Qt::NoBrush);
    p.drawRect(1, 1, ANCHO - 2, ALTO - 2);

    for (int i = 0; i < 4; i++) {
        QRectF r(OBS[i].x, OBS[i].y, OBS[i].w, OBS[i].h);
        p.setBrush(QColor(90, 90, 110));
        p.setPen(QPen(QColor(160, 160, 180), 1));
        p.drawRect(r);
        p.setPen(Qt::white);
        p.setFont(QFont("Arial", 8));
        p.drawText(r, Qt::AlignCenter, "e=0.6");
    }

    auto& ps = fisica.getParticulas();
    for (size_t i = 0; i < ps.size(); i++) {
        double r  = ps[i]->getRadio();
        double cx = ps[i]->getX();
        double cy = ps[i]->getY();
        QColor c  = COLORES[i % N_COLORES];

        p.setBrush(QColor(0, 0, 0, 60));
        p.setPen(Qt::NoPen);
        p.drawEllipse(QRectF(cx - r + 3, cy - r + 3, r*2, r*2));

        p.setBrush(c);
        p.setPen(QPen(c.lighter(160), 1.5));
        p.drawEllipse(QRectF(cx - r, cy - r, r*2, r*2));

        p.setPen(Qt::white);
        p.setFont(QFont("Arial", 7, QFont::Bold));
        p.drawText(QRectF(cx - r, cy - r, r*2, r*2),
                   Qt::AlignCenter,
                   QString("m=%1").arg(ps[i]->getMasa(), 0, 'f', 1));
    }

    p.setPen(QColor(220, 220, 220));
    p.setFont(QFont("Arial", 10));
    p.drawText(10, 20,
               QString("t = %1 s    Particulas activas: %2")
                   .arg(tiempo, 0, 'f', 2)
                   .arg(ps.size()));

    p.setFont(QFont("Arial", 8));
    p.setPen(QColor(160, 200, 160));
    p.drawText(10, ALTO - 30, "Paredes: rebote elastico");
    p.setPen(QColor(200, 160, 100));
    p.drawText(10, ALTO - 15, "Obstaculos: rebote inelastico (e=0.6)  |  Particulas: fusion inelastica");
}