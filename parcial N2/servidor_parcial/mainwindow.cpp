#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    servidor = new QTcpServer(this);


    connect(servidor, &QTcpServer::newConnection, this, &MainWindow::nuevaConexion);
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pb_encender_clicked()
{

    quint16 puerto = ui->line_puerto->text().toUShort();


    if (servidor->listen(QHostAddress::Any, puerto)) {
        ui->estado->setText("Escuchando en el puerto " + QString::number(puerto));
    } else {
        ui->estado->setText("Error: " + servidor->errorString());
    }
}


void MainWindow::nuevaConexion()
{

    QTcpSocket *cliente = servidor->nextPendingConnection();
    clientes.append(cliente);


    connect(cliente, &QTcpSocket::readyRead, this, &MainWindow::leerDatos);

    connect(cliente, &QTcpSocket::disconnected, this, &MainWindow::clienteDesconectado);

    ui->estado->setText("Cliente conectado");
}

void MainWindow::leerDatos()
{

    QTcpSocket *cliente = (QTcpSocket*) sender();

    QString recibido = cliente->readAll().trimmed();
    QString respuesta = procesarComando(recibido);

    cliente->write(respuesta.toUtf8());
}


void MainWindow::clienteDesconectado()
{
    QTcpSocket *cliente = (QTcpSocket*) sender();
    clientes.removeOne(cliente);
    cliente->deleteLater();

    ui->estado->setText("Cliente desconectado");
}


QString MainWindow::procesarComando(const QString &recibido)
{
    QDateTime ahora = QDateTime::currentDateTime();

    if (recibido == "day")     return QString::number(ahora.date().day());
    if (recibido == "month")     return QString::number(ahora.date().month());
    if (recibido == "year")    return QString::number(ahora.date().year());
    if (recibido == "hour")    return QString::number(ahora.time().hour());
    if (recibido == "min")  return QString::number(ahora.time().minute());
    if (recibido == "sec") return QString::number(ahora.time().second());


}
