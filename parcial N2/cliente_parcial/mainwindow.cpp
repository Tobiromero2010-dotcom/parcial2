#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pb_conectar, &QPushButton::clicked, this, &MainWindow::connect_to_server);
    connect(ui->pb_enviar, &QPushButton::clicked, this, &MainWindow::enviar_mensaje);
    connect(&socket, &QTcpSocket::readyRead, this, &MainWindow::leer_respuesta);
    ui->estado->setText("desconectado");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connect_to_server()
{
    if (socket.state() == QAbstractSocket::UnconnectedState)
    {
        socket.connectToHost(ui->line_ip->text(), ui->line_puerto->text().toInt());
        ui->pb_conectar->setText("desconectar");
        ui->estado->setText("conectado");
    }
    else
    {
        socket.abort();
        ui->pb_conectar->setText("conectar");
    }
}

void MainWindow::enviar_mensaje()
{
    comando = ui->line_pedido->text();
    socket.write(comando.toUtf8() + '\n');
    ui->line_pedido->clear();
}

void MainWindow::leer_respuesta()
{
    QString respuesta = QString::fromUtf8(socket.readAll()).trimmed();

    if (comando == "year")
        ui->line_year->setText(respuesta);
    else if (comando == "month")
        ui->line_month->setText(respuesta);
    else if (comando == "day")
        ui->line_day->setText(respuesta);
    else if (comando == "date")
        ui->line_date->setText(respuesta);
    else if(comando=="hour")
        ui->line_hour->setText(respuesta);
    else if (comando =="min")
        ui->line_min->setText(respuesta);
    else if(comando=="sec")
        ui->line_sec->setText(respuesta);
    else if(comando=="time")
        ui->line_time->setText(respuesta);
    else if(comando=="datetime")
        ui->line_dateTime->setText(respuesta);
}
