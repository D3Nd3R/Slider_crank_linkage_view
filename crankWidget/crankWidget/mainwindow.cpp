#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <vector>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //    connect(ui->sld_angle, &QSlider::valueChanged,
    //            ui->crankWidget, &CrankWidget::setCrankAngleInt);

    initCranks();
    initTimer();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initCranks()
{
    cranks.reserve(8);
    cranks.push_back(ui->crankWidget);
    cranks.push_back(ui->crankWidget_2);
    cranks.push_back(ui->crankWidget_3);
    cranks.push_back(ui->crankWidget_4);
    cranks.push_back(ui->crankWidget_5);
    cranks.push_back(ui->crankWidget_6);
    cranks.push_back(ui->crankWidget_7);
    cranks.push_back(ui->crankWidget_8);

    for (size_t ii = 0; ii < cranks.size(); ++ii) {
        cranks[ii]->setCrankPhaseShift(ii * 45);
        connect(ui->sld_angle, &QSlider::valueChanged,
                cranks[ii], &CrankWidget::setCrankAngleInt);
    }

}

void MainWindow::initTimer()
{
    timer.setInterval(10);
    connect(&timer, &QTimer::timeout,
            [this](){
                for (auto crank : cranks) {
                    crank->setCrankAngle(crank->crankAngle() + 2.);
                }
            });
}


void MainWindow::on_checBox_isTimerOn_stateChanged(int arg1)
{
    if (arg1 == Qt::Unchecked){
        timer.stop();
        ui->sld_angle->setEnabled(true);
        return;
    }else if (arg1 == Qt::Checked){
        for (auto crank : cranks) {
            crank->setCrankAngle(0);
        }
        ui->sld_angle->setEnabled(false);
        timer.start();

    }


}
