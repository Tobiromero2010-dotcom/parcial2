#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "muparser/muParser.h"
#include <cmath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->grafico->addGraph();
    ui->grafico->addGraph();
    ui->grafico->graph(1)->setPen(QPen(Qt::red));

    ui->line_azul->setText("x^2-0.5*x-3");
    ui->line_rojo->setText("-x^2+8");

    connect(ui->line_azul,&QLineEdit::returnPressed,this,&MainWindow::on_pb_graficar_clicked);
    connect(ui->line_rojo,&QLineEdit::returnPressed,this,&MainWindow::on_pb_graficar_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pb_graficar_clicked()
{
    double x;
    QVector<double> vyRojo;
    vx.clear();
    vy.clear();

    mu::Parser azul, rojo;
    azul.DefineVar("x", &x);
    rojo.DefineVar("x", &x);

    try {
        azul.SetExpr(ui->line_azul->text().toStdString());
        rojo.SetExpr(ui->line_rojo->text().toStdString());
        for (int i = -400; i <= 400; i++) {
            x = i / 100.0;
            vx.append(x);
            vy.append(azul.Eval());
            vyRojo.append(rojo.Eval());
        }
    } catch (mu::Parser::exception_type &e) {
        ui->statusbar->showMessage(QString::fromStdString(e.GetMsg()));
        return;
    }

    ui->grafico->graph(0)->setData(vx, vy);
    ui->grafico->graph(1)->setData(vx, vyRojo);
    ui->grafico->rescaleAxes();
    ui->grafico->replot();


    int i1 = -1, i2 = -1;
    for (int i = 0; i < vx.size() - 1; i++) {
        double fa = vy[i] - vyRojo[i];
        double fb = vy[i+1] - vyRojo[i+1];
        if (fa * fb < 0) {
            if (i1 == -1) i1 = i;
            else          i2 = i;
        }
    }




    double area = 0;
    for (int i = i1; i < i2; i++) {
        double h  = vx[i+1] - vx[i];
        double d1 = fabs(vy[i]   - vyRojo[i]);
        double d2 = fabs(vy[i+1] - vyRojo[i+1]);
        area += (d1 + d2) / 2 * h;
    }

    ui->lbl_resultados->setText(QString("raices = %1\n  = %2\nArea = %3")
                                    .arg(vx[i1]).arg(vx[i2]).arg(area));
}
