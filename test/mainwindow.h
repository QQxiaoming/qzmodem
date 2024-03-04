#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "qsendzmodem.h"
#include "qrecvzmodem.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_toolButton_Send_clicked();
    void on_toolButton_recv_clicked();
    void on_pushButton_Start_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
