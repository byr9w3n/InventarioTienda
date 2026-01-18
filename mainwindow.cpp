#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tablaInventario->setColumnCount(4); // Necesitamos 4 columnas
    ui->tablaInventario->setHorizontalHeaderLabels({"Nombre", "Talla", "Precio", "Stock"}); // Ponerle nombre a las columnas

    actualizarTabla();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::actualizarTabla(){
    QFile archivo("Inventario.txt");

    ui->tablaInventario->setRowCount(0); // Borrar todas las filas que haya actualmente.

    if (!archivo.open(QIODevice::ReadOnly)){ // Escribir al final sin borrar lo anterior.
        return; // se sale de la función y no hace nada más.
    }

    QTextStream in(&archivo); // crear al lector.
    int fila = 0; // contador para saber en qué fila de la tabla vamos a escribir.
    while(!in.atEnd()){ // Mientras no hayamos llegado al final del archivo...
        QString linea = in.readLine(); // Lee una línea completa del archivo.
        QStringList datos = linea.split(";");
        if(linea.isEmpty()){
            continue;
        }
        if(datos.size() < 4){
            continue; // si no tiene nombre,talla,precio,stock la ignora.
        }
        ui->tablaInventario->insertRow(fila); // Crea una fila vacía
                                   //fila/columna/item
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
        return; // Evitar que el programa guarde un producto vacio.
    }

    QFile archivo("Inventario.txt"); // definir archivo.

    if(archivo.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)){ // escribir al final sin borrar lo anterior.
        QTextStream out(&archivo); //Facilita escribir texto y números en el archivo.
        out << ui->txtNombre->text() << ";" << ui->txtTalla->text() << ";" << ui->txtPrecio->value() << ";" << ui->txtStock->value() << "\n";
        archivo.close();
        ///////// Limpiar.
        ui->txtNombre->clear();
        ui->txtTalla->clear();
        ui->txtPrecio->setValue(0.00);
        ui->txtStock->setValue(0);
        // Actualizar la visualizacion de la tabla
        actualizarTabla();
    }else{
        qDebug() << "Error al abrir el archivo";
    }
}

