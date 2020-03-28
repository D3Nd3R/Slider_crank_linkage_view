#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

class CrankWidget;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_checBox_isTimerOn_stateChanged(int arg1);

private:
    void initCranks();
    void initTimer();

private:
    Ui::MainWindow *ui;
    std::vector<CrankWidget*> cranks;

    QTimer timer;
};
#endif // MAINWINDOW_H
