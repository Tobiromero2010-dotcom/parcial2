#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QTcpServer>
#include <QList>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void on_pb_encender_clicked();
    void nuevaConexion();
    void leerDatos();
    void clienteDesconectado();

private:
    QString procesarComando(const QString &cmd);

    Ui::MainWindow *ui;
    QTcpServer *servidor;
    QList<QTcpSocket*> clientes;
};
#endif // MAINWINDOW_H
