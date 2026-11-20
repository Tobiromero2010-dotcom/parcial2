#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>

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
    void connect_to_server();
    void enviar_mensaje();
    void leer_respuesta();

private:
    Ui::MainWindow *ui;
    QTcpSocket socket;
    QString comando;   // último comando enviado
};
#endif // MAINWINDOW_H
