#include "gamewindow.h"
#include <QPainter>
#include <QColor>

// Dimensiones de la ventana (caja de simulación)
static const double ANCHO = 800.0;
static const double ALTO  = 600.0;
static const double DT    = 0.05;

GameWindow::GameWindow(QWidget *parent)
    : QWidget(parent), tiempo(0.0)
{
    setFixedSize((int)ANCHO, (int)ALTO);
    setWindowTitle("Simulación de Partículas - Práctica 5");

    // Abrir archivo de salida
    archivo.open("trayectorias.txt");
    if (archivo.is_open())
        archivo << "# tiempo id x y velX velY masa\n";

    inicializarObstaculos();
    inicializarParticulas();

    // Timer: ~60 fps
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout,
            this,  &GameWindow::actualizarFrame);
    timer->start(16);
}

GameWindow::~GameWindow()
{
    if (archivo.is_open())
        archivo.close();
}

// Configuración inicia

void GameWindow::inicializarParticulas()
{
    // 4 partículas: x, y, velocidad, ángulo, masa
    fisica.agregarParticula(new Particula(100, 300, 80,  45,  1.0));
    fisica.agregarParticula(new Particula(700, 300, 80, 135,  1.5));
    fisica.agregarParticula(new Particula(400, 100, 60, 270,  2.0));
    fisica.agregarParticula(new Particula(400, 500, 70,  90,  1.2));
}

void GameWindow::inicializarObstaculos()
{
    // 4 obstáculos: x, y, ancho, alto, coef. restitución
    fisica.agregarObstaculo(new Obstaculo(150, 200, 80, 80, 0.6));
    fisica.agregarObstaculo(new Obstaculo(570, 200, 80, 80, 0.6));
    fisica.agregarObstaculo(new Obstaculo(150, 420, 80, 80, 0.6));
    fisica.agregarObstaculo(new Obstaculo(570, 420, 80, 80, 0.6));
}

//Lógica por frame ─

void GameWindow::actualizarFrame()
{
    guardarEstado();
    fisica.actualizarSistema(DT, ANCHO, ALTO);
    tiempo += DT;
    update(); // Redibuja
}

void GameWindow::guardarEstado()
{
    if (!archivo.is_open()) return;

    auto& particulas = fisica.getParticulas();
    for (size_t i = 0; i < particulas.size(); i++) {
        archivo << tiempo             << " "
                << i                  << " "
                << particulas[i]->getX()    << " "
                << particulas[i]->getY()    << " "
                << particulas[i]->getVelX() << " "
                << particulas[i]->getVelY() << " "
                << particulas[i]->getMasa() << "\n";
    }
}

//  Dibuj

void GameWindow::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Fondo negro
    painter.fillRect(rect(), Qt::black);

    // Obstáculos (gris)
    painter.setBrush(QColor(100, 100, 100));
    painter.setPen(Qt::white);
    // No tenemos lista directa de obstáculos en GameWindow,
    // pero los dibujamos con las posiciones que conocemos
    QList<QRectF> obs = {
        {150, 200, 80, 80},
        {570, 200, 80, 80},
        {150, 420, 80, 80},
        {570, 420, 80, 80}
    };
    for (auto& r : obs)
        painter.drawRect(r);

    QList<QColor> colores = {Qt::blue, Qt::red, Qt::green, QColor(255,165,0)};
    auto& particulas = fisica.getParticulas();
    for (size_t i = 0; i < particulas.size(); i++) {
        double r = particulas[i]->getRadio();
        double x = particulas[i]->getX() - r;
        double y = particulas[i]->getY() - r;
        QColor c = colores[(int)i % colores.size()];
        painter.setBrush(c);
        painter.setPen(Qt::white);
        painter.drawEllipse(QRectF(x, y, r*2, r*2));
    }

    // HUD: tiempo
    painter.setPen(Qt::white);
    painter.drawText(10, 20,
                     QString("t = %1 s  |  Partículas: %2")
                         .arg(tiempo, 0, 'f', 1)
                         .arg(particulas.size()));
}
