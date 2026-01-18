#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>

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

void MainWindow::on_btnGuardar_clicked()
{
    if(ui->txtNombre->text().isEmpty()){
        return; // La caja de texto del nombre está vacía
    }

    QFile archivo("Inventario.txt"); // definir archivo.
    ui->tablaInventario->setRowCount(0); // La tabla tiene 0 filas.

    if(archivo.open(QIODevice::WriteOnly | QIODevice::Append)){
        // escribimos si el archivo se abrió bien.
        QTextStream out(&archivo); //Facilita escribir texto y números en el archivo..
        out << ui->txtNombre->text() << ";" << ui->txtTalla->text() << ";" << ui->txtPrecio->value() << ";" << ui->txtStock->value() << "\n";
        archivo.close();
        ///////// Limpiar
        ui->txtNombre->clear();
        ui->txtTalla->clear();
        ui->txtPrecio->clear();
        ui->txtStock->clear();
    }else{
        qDebug() << "Error al abrir el archivo";
    }
}

