#include "gamewindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>

// ─────────────────────────────────────────────
// Dimensiones de la escena (coordenadas Qt)
//   x  →  crece a la derecha
//   y  ↓  crece hacia abajo
//
// El suelo está en y = ALTO_ESCENA - SUELO_Y
// Los jugadores/infraestructura se colocan
// cerca del suelo.
// ─────────────────────────────────────────────
static const double ANCHO_ESCENA = 1200.0;
static const double ALTO_ESCENA  =  600.0;

// Margen del suelo (píxeles desde el borde inferior)
static const double MARGEN_SUELO = 60.0;

// Posición Y del suelo en coords Qt
static const double Y_SUELO = ALTO_ESCENA - MARGEN_SUELO;

// ── Jugador 1 (izquierda, azul) ───────────────
static const double J1_X      =  50.0;   // centro del sprite
static const double J1_Y      = Y_SUELO - 20.0;

// ── Jugador 2 (derecha, rojo) ─────────────────
static const double J2_X      = ANCHO_ESCENA - 80.0;
static const double J2_Y      = Y_SUELO - 20.0;

// ── Infraestructura J1 (tres bloques) ─────────
//   Bloque izquierdo, central y derecho
//   todos apoyados sobre el suelo
static const double INF1_ANCHO = 100.0;
static const double INF1_ALTO  =  60.0;

//   x, y (esquina sup-izq en coords Qt), ancho, alto
static const double INF1A_X = 180.0;
static const double INF1A_Y = Y_SUELO - INF1_ALTO;

static const double INF1B_X = 310.0;
static const double INF1B_Y = Y_SUELO - INF1_ALTO;

static const double INF1C_X = 245.0;                        // encima del central
static const double INF1C_Y = Y_SUELO - INF1_ALTO * 2.0;  // segunda fila

// ── Infraestructura J2 (espejo de J1) ─────────
static const double INF2A_X = ANCHO_ESCENA - INF1A_X - INF1_ANCHO;
static const double INF2A_Y = INF1A_Y;

static const double INF2B_X = ANCHO_ESCENA - INF1B_X - INF1_ANCHO;
static const double INF2B_Y = INF1B_Y;

static const double INF2C_X = ANCHO_ESCENA - INF1C_X - INF1_ANCHO;
static const double INF2C_Y = INF1C_Y;

// ─────────────────────────────────────────────
// Constructor
// ─────────────────────────────────────────────
GameWindow::GameWindow(QWidget *parent)
    : QWidget(parent)
{
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, ANCHO_ESCENA, ALTO_ESCENA);
    scene->setBackgroundBrush(QBrush(QColor(30, 30, 50)));   // fondo oscuro

    view = new QGraphicsView(scene);
    view->setFixedSize(
        static_cast<int>(ANCHO_ESCENA) + 4,
        static_cast<int>(ALTO_ESCENA)  + 4);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    panel      = new PanelControl(this);
    turnoLabel = new QLabel(this);
    vidaLabel  = new QLabel(this);

    timer = new QTimer(this);

    crearEscena();

    // ── Layout ──────────────────────────────────
    QVBoxLayout* panelDerecho = new QVBoxLayout;
    panelDerecho->addWidget(turnoLabel);
    panelDerecho->addWidget(vidaLabel);
    panelDerecho->addWidget(panel);
    panelDerecho->addStretch();

    QHBoxLayout* layout = new QHBoxLayout;
    layout->addWidget(view);
    layout->addLayout(panelDerecho);
    setLayout(layout);

    // ── Conexiones ──────────────────────────────
    connect(timer, &QTimer::timeout,
            this,  &GameWindow::actualizarGUI);

    connect(panel, &PanelControl::dispararSolicitado,
            this,  &GameWindow::lanzarProyectil);

    timer->start(16);   // ~60 fps
}

// ─────────────────────────────────────────────
// crearEscena
// ─────────────────────────────────────────────
void GameWindow::crearEscena()
{
    // ── Suelo ────────────────────────────────────
    scene->addRect(0, Y_SUELO, ANCHO_ESCENA, MARGEN_SUELO,
                   QPen(Qt::NoPen),
                   QBrush(QColor(60, 40, 20)));   // marrón tierra

    // ── Jugador 1 (azul) ─────────────────────────
    jugador1Item = scene->addEllipse(
        J1_X, J1_Y, 30, 30,
        QPen(Qt::white),
        QBrush(Qt::blue));

    scene->addSimpleText("J1")->setPos(J1_X + 4, J1_Y + 6);

    // ── Jugador 2 (rojo) ─────────────────────────
    jugador2Item = scene->addEllipse(
        J2_X, J2_Y, 30, 30,
        QPen(Qt::white),
        QBrush(Qt::red));

    scene->addSimpleText("J2")->setPos(J2_X + 4, J2_Y + 6);

    // ── Helper: crea un bloque de infraestructura ─
    auto crearBloque = [&](double bx, double by, double bw, double bh,
                           double resistencia, double restitucion,
                           int owner, const QColor& color)
        -> Infraestructura*
    {
        auto* inf = new Infraestructura(
            bx, by, bw, bh,
            resistencia, restitucion, owner);

        juego.getFisica().agregarInfraestructura(inf);

        if (owner == 1)
            juego.getJugador1().agregarInfraestructura(inf);
        else
            juego.getJugador2().agregarInfraestructura(inf);

        // Rectángulo gráfico
        QGraphicsRectItem* rect = scene->addRect(
            bx, by, bw, bh,
            QPen(Qt::white),
            QBrush(color));
        (void)rect;   // no necesitamos guardarlo por ahora

        // Etiqueta de resistencia encima del bloque
        QGraphicsTextItem* txt = scene->addText(
            QString::number(static_cast<int>(resistencia)));
        txt->setDefaultTextColor(Qt::white);
        txt->setPos(bx + bw/2 - 10, by - 20);

        return inf;
    };

    // ── Infraestructura Jugador 1 ─────────────────
    crearBloque(INF1A_X, INF1A_Y, INF1_ANCHO, INF1_ALTO, 200, 0.6, 1,
                QColor(50, 80, 200));
    crearBloque(INF1B_X, INF1B_Y, INF1_ANCHO, INF1_ALTO, 200, 0.6, 1,
                QColor(50, 80, 200));
    crearBloque(INF1C_X, INF1C_Y, INF1_ANCHO, INF1_ALTO, 150, 0.6, 1,
                QColor(80, 110, 220));

    // ── Infraestructura Jugador 2 ─────────────────
    crearBloque(INF2A_X, INF2A_Y, INF1_ANCHO, INF1_ALTO, 200, 0.6, 2,
                QColor(200, 50, 50));
    crearBloque(INF2B_X, INF2B_Y, INF1_ANCHO, INF1_ALTO, 200, 0.6, 2,
                QColor(200, 50, 50));
    crearBloque(INF2C_X, INF2C_Y, INF1_ANCHO, INF1_ALTO, 150, 0.6, 2,
                QColor(220, 80, 80));

    // ── Labels iniciales ─────────────────────────
    turnoLabel->setText("Turno: Jugador 1");
    vidaLabel->setText("Infra J1: 550   Infra J2: 550");

    // ── Hint de prueba ───────────────────────────
    // J1 dispara: ángulo ~35°, velocidad ~450 → impacta bloques J2
    // J2 dispara: ángulo ~145°, velocidad ~450 → impacta bloques J1
    // (el panel ya invierte el ángulo para J2, así que J2 ingresa ~35°)
    QGraphicsTextItem* hint = scene->addText(
        "Prueba: angulo 35, velocidad 450");
    hint->setDefaultTextColor(QColor(200, 200, 100));
    hint->setPos(ANCHO_ESCENA/2 - 120, 10);
}

// ─────────────────────────────────────────────
// lanzarProyectil
// ─────────────────────────────────────────────
void GameWindow::lanzarProyectil()
{
    double angulo    = panel->obtenerAngulo();
    double velocidad = panel->obtenerVelocidad();

    double xInicial, yInicial;

    if (juego.getTurnoActual() == 1)
    {
        // Dispara desde el jugador 1 (izquierda)
        xInicial = J1_X + 30;          // borde derecho del sprite
        yInicial = J1_Y + 10;          // centro vertical del sprite
        // angulo positivo → lanza hacia arriba-derecha
        // velX = v·cos(θ)  >0   velY = -v·sin(θ)  <0 (Qt: y↓, arriba es negativo)
    }
    else
    {
        // Dispara desde el jugador 2 (derecha)
        xInicial = J2_X;               // borde izquierdo del sprite
        yInicial = J2_Y + 10;
        angulo   = 180.0 - angulo;     // espeja para que vaya hacia la izquierda
    }

    juego.disparar(xInicial, yInicial, velocidad, angulo, 10.0);

    // Ítem gráfico del proyectil
    QGraphicsEllipseItem* item = scene->addEllipse(
        0, 0, 14, 14,
        QPen(Qt::NoPen),
        QBrush(QColor(255, 200, 0)));   // amarillo-naranja
    proyectilesGraficos.push_back(item);

    // Cambiar turno
    juego.cambiarTurno();
    turnoLabel->setText(
        juego.getTurnoActual() == 1
            ? "Turno: Jugador 1"
            : "Turno: Jugador 2");
}

// ─────────────────────────────────────────────
// actualizarGUI  (llamado ~60 veces por segundo)
// ─────────────────────────────────────────────
void GameWindow::actualizarGUI()
{
    // ── Avanzar simulación ────────────────────────
    juego.getFisica().actualizarSistema(0.016, ANCHO_ESCENA, ALTO_ESCENA);

    // ── Sincronizar sprites de proyectiles ────────
    auto& proyectiles = juego.getFisica().getProyectiles();
    for (size_t i = 0;
         i < proyectiles.size() && i < proyectilesGraficos.size();
         ++i)
    {
        // La física usa coords Qt (y↓), así que no hay conversión
        proyectilesGraficos[i]->setPos(
            proyectiles[i]->getX() - 7,   // centrar el círculo de 14px
            proyectiles[i]->getY() - 7);
    }

    // ── Actualizar label de resistencias ─────────
    double totalJ1 = 0.0, totalJ2 = 0.0;
    for (auto* inf : juego.getJugador1().getInfraestructuras())
        totalJ1 += inf->getResistencia();
    for (auto* inf : juego.getJugador2().getInfraestructuras())
        totalJ2 += inf->getResistencia();

    vidaLabel->setText(
        QString("Infra J1: %1   Infra J2: %2")
            .arg(static_cast<int>(totalJ1))
            .arg(static_cast<int>(totalJ2)));

    // ── Comprobar victoria ────────────────────────
    if (juego.verificarVictoria())
    {
        timer->stop();
        panel->setEnabled(false);

        Jugador* ganador = juego.obtenerGanador();
        QString msg = ganador
                          ? "¡Ganó " + ganador->getNombre() + "!"
                          : "¡Empate!";

        // Texto grande en el centro de la escena
        QGraphicsTextItem* txt = scene->addText(msg);
        txt->setDefaultTextColor(Qt::yellow);
        txt->setFont(QFont("Arial", 36, QFont::Bold));
        txt->setPos(ANCHO_ESCENA/2 - 160, ALTO_ESCENA/2 - 30);

        QMessageBox::information(this, "Fin del juego", msg);
    }
}
