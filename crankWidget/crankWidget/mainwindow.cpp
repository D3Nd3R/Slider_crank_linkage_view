#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->sld_angle, &QSlider::valueChanged,
            ui->crankWidget, &CrankWidget::setCrankAngleInt);
}

MainWindow::~MainWindow()
{
    delete ui;
}

