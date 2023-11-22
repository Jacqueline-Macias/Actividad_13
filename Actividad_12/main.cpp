#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QPlainTextEdit>
#include <QFileDialog>
#include <fstream>
#include <vector>
#include <iostream>
#include <QVBoxLayout>

class Neurona {
public:
    Neurona(int id, double voltaje, int posX, int posY, int red, int green, int blue)
        : id(id), voltaje(voltaje), posX(posX), posY(posY), red(red), green(green), blue(blue), x(x), y(y) {
    }

    void print() const {
        std::cout << "ID: " << id << std::endl;
        std::cout << "Voltaje: " << voltaje << std::endl;
        std::cout << "Posición X: " << posX << std::endl;
                std::cout << "Posición Y: " << posY << std::endl;
                         std::cout << "RGB: (" << red << ", " << green << ", " << blue << ")" << std::endl;
    }

    int getId() const { return id; }
    double getVoltaje() const { return voltaje; }
    int getPosX() const { return posX; }
    int getPosY() const { return posY; }
    int getRed() const { return red; }
    int getGreen() const { return green; }
    int getBlue() const { return blue; }

private:
    int id;
    double voltaje;
    int posX;
    int posY;
    int red;
    int green;
    int blue;
};

class AdministradorNeuronas {
public:
    void agregarInicio(const Neurona& neurona) {
        neuronas.insert(neuronas.begin(), neurona);
    }

    void agregarFinal(const Neurona& neurona) {
        neuronas.push_back(neurona);
    }

    const std::vector<Neurona>& getNeuronas() const {
        return neuronas;
    }

    void borrarNeuronas() {
        neuronas.clear();
    }

    void guardarNeuronas(const std::string& fileName) const {
        std::ofstream file(fileName);

        if (file.is_open()) {
            for (const Neurona& neurona : neuronas) {
                file << neurona.getId() << " "
                     << neurona.getVoltaje() << " "
                     << neurona.getPosX() << " "
                     << neurona.getPosY() << " "
                     << neurona.getRed() << " "
                     << neurona.getGreen() << " "
                     << neurona.getBlue() << std::endl;
            }
            file.close();
        }
    }

    void cargarNeuronas(const std::string& fileName) {
        std::ifstream file(fileName);

        if (file.is_open()) {
            borrarNeuronas();

            int id, posX, posY, red, green, blue;
            double voltaje;

            while (file >> id >> voltaje >> posX >> posY >> red >> green >> blue) {
                Neurona neurona(id, voltaje, posX, posY, red, green, blue);
                agregarFinal(neurona);
            }

            file.close();
        }
    }

private:
    std::vector<Neurona> neuronas;
};

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr) : QMainWindow(parent) {
        setWindowTitle("Administrador de Neuronas");

        QPushButton *agregarInicioButton = new QPushButton("Agregar al Inicio", this);
        QPushButton *agregarFinalButton = new QPushButton("Agregar al Final", this);
        QPushButton *mostrarButton = new QPushButton("Mostrar Neuronas", this);
        QPushButton *guardarButton = new QPushButton("Guardar Neuronas", this);
        QPushButton *cargarButton = new QPushButton("Cargar Neuronas", this);
        plainTextEdit = new QPlainTextEdit(this);

        administrador = new AdministradorNeuronas;

        connect(agregarInicioButton, &QPushButton::clicked, this, &MainWindow::agregarNeuronaAlInicio);
        connect(agregarFinalButton, &QPushButton::clicked, this, &MainWindow::agregarNeuronaAlFinal);
        connect(mostrarButton, &QPushButton::clicked, this, &MainWindow::mostrarNeuronas);
        connect(guardarButton, &QPushButton::clicked, this, &MainWindow::guardarNeuronas);
        connect(cargarButton, &QPushButton::clicked, this, &MainWindow::cargarNeuronas);

        setCentralWidget(plainTextEdit);

        // Layout
        QVBoxLayout *layout = new QVBoxLayout;
        layout->addWidget(agregarInicioButton);
        layout->addWidget(agregarFinalButton);
        layout->addWidget(mostrarButton);
        layout->addWidget(guardarButton);
        layout->addWidget(cargarButton);
        layout->addWidget(plainTextEdit);

        QWidget *widget = new QWidget(this);
        widget->setLayout(layout);
        setCentralWidget(widget);
    }

private slots:
    void agregarNeuronaAlInicio() {

        int id = 1; // Reemplaza esto con la lógica para obtener el ID desde un widget
        double voltaje = 2.0; // Reemplaza esto con la lógica para obtener el voltaje desde un widget
        int posX = 3; // Reemplaza esto con la lógica para obtener la posición X desde un widget
        int posY = 4; // Reemplaza esto con la lógica para obtener la posición Y desde un widget
        int red = 255; // Reemplaza esto con la lógica para obtener el valor rojo desde un widget
        int green = 0; // Reemplaza esto con la lógica para obtener el valor verde desde un widget
        int blue = 0; // Reemplaza esto con la lógica para obtener el valor azul desde un widget

        Neurona neurona(id, voltaje, posX, posY, red, green, blue);
        administrador->agregarInicio(neurona);
    }

    void agregarNeuronaAlFinal() {
    }

    void mostrarNeuronas() {
        plainTextEdit->clear();
        const std::vector<Neurona>& neuronas = administrador->getNeuronas();
        for (const Neurona& neurona : neuronas) {
            neurona.print();
        }
    }

    void guardarNeuronas() {
        QString fileName = QFileDialog::getSaveFileName(this, "Guardar Neuronas", "", "Archivos de Texto (*.txt)");
        if (!fileName.isEmpty()) {
            administrador->guardarNeuronas(fileName.toStdString());
        }
    }

    void cargarNeuronas() {
        QString fileName = QFileDialog::getOpenFileName(this, "Cargar Neuronas", "", "Archivos de Texto (*.txt)");
        if (!fileName.isEmpty()) {
            administrador->cargarNeuronas(fileName.toStdString());
        }
    }

private:
    QPlainTextEdit *plainTextEdit;
    AdministradorNeuronas *administrador;
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow mainWindow;
    mainWindow.show();
    return app.exec();
}

private slots:
void ordenarNeuronasPorId() {
    std::vector<Neurona>& neuronas = administrador->getNeuronas();
    std::sort(neuronas.begin(), neuronas.end(), [](const Neurona& a, const Neurona& b) {
        return a.getId() < b.getId();
    });
    mostrarNeuronas();
}

void ordenarNeuronasPorVoltaje() {
    std::vector<Neurona>& neuronas = administrador->getNeuronas();
    std::sort(neuronas.begin(), neuronas.end(), [](const Neurona& a, const Neurona& b) {
        return a.getVoltaje() < b.getVoltaje();
    });
    mostrarNeuronas();
}

double calcularDistancia(const Neurona& neurona1, const Neurona& neurona2) {
    double dx = neurona1.x - neurona2.x;
    double dy = neurona1.y - neurona2.y;
    return sqrt(dx * dx + dy * dy);
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QGraphicsScene scene;
    QGraphicsView view(&scene);
    view.setWindowTitle("Representación de Neuronas como Grafo");
    view.resize(800, 600);

    QPlainTextEdit textoAdyacencia;
    textoAdyacencia.setFixedSize(200, 600);

    for (int i = 0; i < neuronas.size(); ++i) {
        QGraphicsEllipseItem *nodo = scene.addEllipse(neuronas[i].x - 5, neuronas[i].y - 5, 10, 10);
        nodo->setBrush(Qt::blue);
        nodo->setFlag(QGraphicsItem::ItemIsMovable);
        QGraphicsTextItem *idTexto = scene.addText(QString::number(neuronas[i].id));
        idTexto->setPos(neuronas[i].x + 10, neuronas[i].y + 10);

        for (int j = 0; j < neuronas.size(); ++j) {
            if (i != j) {
                double distancia = calcularDistancia(neuronas[i], neuronas[j]);

                QGraphicsLineItem *arista = scene.addLine(neuronas[i].x, neuronas[i].y, neuronas[j].x, neuronas[j].y);
                arista->setPen(QPen(Qt::red, 2));

                QGraphicsTextItem *pesoTexto = scene.addText(QString::number(distancia));
                pesoTexto->setPos((neuronas[i].x + neuronas[j].x) / 2, (neuronas[i].y + neuronas[j].y) / 2);

                 textoAdyacencia.appendPlainText("Nodo " + QString::number(neuronas[i].id) + " -> Nodo " + QString::number(neuronas[j].id) + ": " + QString::number(distancia));
            }
        }
    }
    view.show();
    textoAdyacencia.show();

    return app.exec();
}

class GrafoMainWindow : public QMainWindow {
    Q_OBJECT

public:
    GrafoMainWindow(QWidget *parent = nullptr) : QMainWindow(parent) {
        setWindowTitle("Recorrido de Grafo");

        QPushButton *agregarNodoButton = new QPushButton("Agregar Nodo", this);
        QPushButton *recorrerDFSButton = new QPushButton("Recorrer DFS", this);
        QPushButton *recorrerBFSButton = new QPushButton("Recorrer BFS", this);

        // Agrega acciones a los botones
        connect(agregarNodoButton, &QPushButton::clicked, this, &GrafoMainWindow::agregarNodo);
        connect(recorrerDFSButton, &QPushButton::clicked, this, &GrafoMainWindow::recorrerDFS);
        connect(recorrerBFSButton, &QPushButton::clicked, this, &GrafoMainWindow::recorrerBFS);

        graphicsView = new QGraphicsView(this);
        scene = new QGraphicsScene(this);
        graphicsView->setScene(scene);

        // Diseño de la interfaz
        QVBoxLayout *layout = new QVBoxLayout;
        layout->addWidget(agregarNodoButton);
        layout->addWidget(recorrerDFSButton);
        layout->addWidget(recorrerBFSButton);
        layout->addWidget(graphicsView);

        QWidget *centralWidget = new QWidget(this);
        centralWidget->setLayout(layout);
        setCentralWidget(centralWidget);

        // Inicializa tu grafo
        grafo = new Grafo;  // Reemplaza con la inicialización de tu clase de grafo
    }

private slots:
    void agregarNodo() {
        // Solicita al usuario ingresar un identificador para el nuevo nodo
        bool ok;
        int id = QInputDialog::getInt(this, "Agregar Nodo", "Ingrese el ID del Nodo:", 0, 0, 100, 1, &ok);

        if (ok) {
            // Agrega el nodo al grafo
            grafo->agregarNodo(id);

            // Dibuja el nodo en el QGraphicsScene
            QGraphicsEllipseItem *nodeItem = scene->addEllipse(0, 0, 20, 20, QPen(Qt::black), QBrush(Qt::red));
            nodeItem->setPos(id * 30, 50);

            // Refresca la vista del QGraphicsScene
            graphicsView->viewport()->update();
        }
    }

    void recorrerDFS() {
        // Solicita al usuario ingresar el nodo inicial para el recorrido DFS
        bool ok;
        int nodoInicial = QInputDialog::getInt(this, "Recorrido DFS", "Ingrese el nodo inicial:", 0, 0, 100, 1, &ok);

        if (ok) {
           
            std::vector<int> nodosVisitados = grafo->recorrerDFS(nodoInicial);

            actualizarInterfaz(nodosVisitados);
        }
    }

    void recorrerBFS() {
        bool ok;
        int nodoInicial = QInputDialog::getInt(this, "Recorrido BFS", "Ingrese el nodo inicial:", 0, 0, 100, 1, &ok);

        if (ok) {
            std::vector<int> nodosVisitados = grafo->recorrerBFS(nodoInicial);
            actualizarInterfaz(nodosVisitados);
        }
    }

    void actualizarInterfaz(const std::vector<int>& nodosVisitados) {
        for (int nodo : nodosVisitados) {
            QGraphicsEllipseItem *nodeItem = scene->addEllipse(0, 0, 20, 20, QPen(Qt::black), QBrush(Qt::green));
            nodeItem->setPos(nodo * 30, 50);
        }

        graphicsView->viewport()->update();
    }

private:
    QGraphicsView *graphicsView;
    QGraphicsScene *scene;
    Grafo *grafo;
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    GrafoMainWindow mainWindow;
    mainWindow.show();
    return app.exec();
}
