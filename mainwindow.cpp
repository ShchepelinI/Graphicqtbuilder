#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QPainterPath>
#include <QPen>
#include <math.h>
#include "poland.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    resize(800, 600);
    button = new QPushButton(this);


    button->setGeometry(width()/2+207, height()/2+200, 145, 50);

    button->setText("Build");

    connect(button, SIGNAL(clicked()), this, SLOT(mybuttonclicked()));


}

void MainWindow::on_lineEdit_editingFinished()
{
    QString s = ui->lineEdit->text();
}


void MainWindow::on_lineEdit_2_editingFinished()
{
    QString s2 = ui->lineEdit->text();
}


void MainWindow::on_lineEdit_3_editingFinished()
{
    QString s3 = ui->lineEdit->text();
}


void MainWindow::on_lineEdit_4_editingFinished()
{
    QString s4 = ui->lineEdit->text();
}


void MainWindow::on_lineEdit_5_editingFinished()
{
    QString s5 = ui->lineEdit->text();
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mybuttonclicked(){

    ui->label->setGeometry(width()/2-340, height()/2 - 250, 500, 500);
    QPixmap pm(500, 500);
    pm.fill(Qt::white);
    ui->label->setPixmap(pm);

    QPainter painter;
    painter.begin(&pm);
    QPainterPath path;
    QPen pen;
    pen.setColor(Qt::black);
    painter.setPen(pen);

    //const double pi = 3.14159265358980;
    QString s = ui->lineEdit->text();
    QString s2 = ui->lineEdit_2->text();
    s2.replace ("pi", "3.14159");
    QString s3 = ui->lineEdit_3->text();
    s3.replace ("pi", "3.14159");
    QString s4 = ui->lineEdit_4->text();
    s4.replace ("pi", "3.14159");
    QString s5 = ui->lineEdit_5->text();
    s5.replace ("pi", "3.14159");
    double xmin = s2.toDouble();
    double xmax = s3.toDouble();
    double ymin = s4.toDouble();
    double ymax = s5.toDouble();
    int xgmin = 0;
    int xgmax = pm.width();
    int ygmin = 0;
    int ygmax = pm.height();
    //double x = xmin;
    //double y;
    //int xg;
    //int yg;
    double kx = (xgmax - xgmin)/(xmax - xmin);
    double ky = (ygmin - ygmax)/(ymax - ymin);
    double stepx = ((xmax - xmin)/(xgmax - xgmin))*0.01;
    double x0 = xgmin - kx * xmin;
    double y0 = ygmin - ky * ymax;
    painter.drawLine(0, y0, xgmax, y0);
    painter.drawLine(x0, 0, x0, ygmax);
    pen.setColor(Qt::red);
    painter.setPen(pen);

    bool check = true;
    for (double x = xmin; x <= xmax; x += stepx) {
        QString t = s;
        t.replace("x", "(" + QString().setNum(x, 'g', 8) + ")");
        double y = 0.0;
        bool p = calculate (t.toStdString(), y);
        if (y <= ymax && y >= ymin && p) {
            int xg = xgmin + kx * (x - xmin);
            int yg = ygmin + ky * (y - ymax);
            if (check) {
                path.moveTo(xg, yg);
                check = false;
            }
            else {
            path.lineTo(xg, yg);
            }

        }
        else {
            check = true;
        }

    }





        //double rez;
        //calculate(sx.toStdString(), rez);

        //path.moveTo(0, rez);



        //double rez;
        //calculate(sx.toStdString(), rez);
        //yg = rez;

        //yg = ygmin + ky * (y - ymax);
        //path.lineTo(xg, yg);
        //x += stepx;

    painter.drawPath(path);
    ui->label->setPixmap(pm);
}
