#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QDir>
#include <vector>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tablaInventario->setColumnCount(4);
    ui->tablaInventario->setHorizontalHeaderLabels({"Nombre", "Talla", "Precio", "Stock"});
    actualizarTabla();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::actualizarTabla(){
    QString ruta = QDir::currentPath() + "/../../Productos.txt";
    QFile archivo(ruta);

    ui->tablaInventario->setRowCount(0);

    if (!archivo.open(QIODevice::ReadOnly)){
        return;
    }

    QTextStream in(&archivo);
    int fila = 0;
    while(!in.atEnd()){
        QString linea = in.readLine();
        QStringList datos = linea.split(";");
        if(linea.isEmpty()){
            continue;
        }
        if(datos.size() < 4){
            continue;
        }
        ui->tablaInventario->insertRow(fila);
        ui->tablaInventario->setItem(fila, 0, new QTableWidgetItem(datos[0]));
        ui->tablaInventario->setItem(fila, 1, new QTableWidgetItem(datos[1]));
        ui->tablaInventario->setItem(fila, 2, new QTableWidgetItem(datos[2]));
        ui->tablaInventario->setItem(fila, 3, new QTableWidgetItem(datos[3]));
        fila++;
    }
    archivo.close();
}


void MainWindow::on_btnGuardar_clicked()
{
    if(ui->txtNombre->text().isEmpty()){
        return;
    }

    QString ruta = QDir::currentPath() + "/../../Productos.txt";
    QFile archivo(ruta);

    if(archivo.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)){
        QTextStream out(&archivo);
        out << ui->txtNombre->text() << ";" << ui->txtTalla->currentText() << ";" << ui->txtPrecio->value() << ";" << ui->txtStock->value() << "\n";
        archivo.close();
        ui->txtNombre->clear();
        ui->txtTalla->setCurrentIndex(0);
        ui->txtPrecio->setValue(0.00);
        ui->txtStock->setValue(0);
        actualizarTabla();
    }else{
        QMessageBox::warning(this, "Error", "No se pudo abrir el archivo");
    }
}

void MainWindow::on_btnEditar_clicked()
{
    int filaSeleccionada = ui->tablaInventario->currentRow();
    if(filaSeleccionada == -1){
        return;
    }
    std::vector<Producto> lista;
    QString ruta = QDir::currentPath() + "/../../Productos.txt";
    QFile archivo(ruta);

    if(archivo.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream in(&archivo);
        while(!in.atEnd()){
            QStringList d = in.readLine().split(";");
            if(d.size() == 4){
                lista.push_back({d[0],d[1],d[2].toDouble(),d[3].toInt()});
            }
        }
        archivo.close();
    }

    if(filaSeleccionada < (int)lista.size()){
        lista[filaSeleccionada].nombre = ui->txtNombre->text();
        lista[filaSeleccionada].talla = ui->txtTalla->currentText();
        lista[filaSeleccionada].precio = ui->txtPrecio->value();
        lista[filaSeleccionada].stock = ui->txtStock->value();
    }

    if(archivo.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)){
        QTextStream out(&archivo);

        for(const auto& p : lista){
            out << p.nombre << ";" << p.talla << ";" << p.precio << ";" << p.stock << "\n";
        }
        archivo.close();
    }
    actualizarTabla();
    ui->txtNombre->clear();
    ui->txtTalla->setCurrentIndex(0);
    ui->txtPrecio->setValue(0.00);
    ui->txtStock->setValue(0);
}

void MainWindow::on_btnEliminar_clicked() {
    int filaSeleccionada = ui->tablaInventario->currentRow();
    if (filaSeleccionada == -1){
        return;
    }

    std::vector<Producto> lista;
    QString ruta = QDir::currentPath() + "/../../Productos.txt";
    QFile archivo(ruta);

    if (archivo.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&archivo);
        while (!in.atEnd()) {
            QStringList d = in.readLine().split(';');
            if (d.size() >= 4) {
                lista.push_back({d[0], d[1], d[2].toDouble(), d[3].toInt()});
            }
        }
        archivo.close();
    }

    if (filaSeleccionada < (int)lista.size()) {
        lista.erase(lista.begin() + filaSeleccionada);
    }

    if (archivo.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
        QTextStream out(&archivo);
        for (const auto& p : lista) {
            out << p.nombre << ";" << p.talla << ";" << p.precio << ";" << p.stock << "\n";
        }
        archivo.close();
    }
    actualizarTabla();
    ui->txtNombre->clear();
    ui->txtTalla->setCurrentIndex(0);
    ui->txtPrecio->setValue(0.00);
    ui->txtStock->setValue(0);
}

void MainWindow::on_tablaInventario_itemClicked(){
    int fila = ui->tablaInventario->currentRow();
    if (fila != -1) {
        ui->txtNombre->setText(ui->tablaInventario->item(fila, 0)->text());
        ui->txtTalla->setCurrentText(ui->tablaInventario->item(fila, 1)->text());
        ui->txtPrecio->setValue(ui->tablaInventario->item(fila, 2)->text().toDouble());
        ui->txtStock->setValue(ui->tablaInventario->item(fila, 3)->text().toInt());
    }
}
