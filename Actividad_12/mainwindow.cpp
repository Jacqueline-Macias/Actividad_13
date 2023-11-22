#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QPushButton *ordenarPorIdButton = new QPushButton("Ordenar por ID", this);
QPushButton *ordenarPorVoltajeButton = new QPushButton("Ordenar por Voltaje", this);

connect(ordenarPorIdButton, &QPushButton::clicked, this, &MainWindow::ordenarNeuronasPorId);
connect(ordenarPorVoltajeButton, &QPushButton::clicked, this, &MainWindow::ordenarNeuronasPorVoltaje);

private slots:
void mostrarPuntos() {
    scene->clear();

    const std::vector<Neurona>& neuronas = administrador->getNeuronas();

    for (const Neurona& neurona : neuronas) {
        int x = neurona.getPosX();
        int y = neurona.getPosY();
        QGraphicsEllipseItem *pointItem = scene->addEllipse(x - 2, y - 2, 4, 4, QPen(Qt::black), QBrush(Qt::black));
    }

    graphicsView->viewport()->update();
}

void calcularPuntosCercanos() {
    scene->clear();

    const std::vector<Neurona>& neuronas = administrador->getNeuronas();

    for (size_t i = 0; i < neuronas.size(); i++) {
        for (size_t j = i + 1; j < neuronas.size(); j++) {
            const Neurona& neurona1 = neuronas[i];
            const Neurona& neurona2 = neuronas[j];
            int x1 = neurona1.getPosX();
            int y1 = neurona1.getPosY();
            int x2 = neurona2.getPosX();
            int y2 = neurona2.getPosY();

            double distancia = std::sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));

            if (distancia < distanciaMinima) {
                QGraphicsLineItem *lineItem = scene->addLine(x1, y1, x2, y2, QPen(Qt::red));
                distanciaMinima = distancia;
            }
        }
    }

    graphicsView->viewport()->update();
}
