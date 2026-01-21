#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "producto.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnGuardar_clicked();
    void actualizarTabla();
    void on_btnEditar_clicked();
    void on_tablaInventario_itemClicked();
    void on_btnEliminar_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
