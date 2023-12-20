#include "mainwindow.h"
#include "./ui_mainwindow.h"

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


void MainWindow::on_pushButton_clicked()
{
    qDebug() << "on_pushButton_clicked begin";

    for (int i = 0; i < 100; ++i)
    {
        Data d{i};
        emit Controler::Get().addWork(d);
    }

    qDebug() << "on_pushButton_clicked end";
}

