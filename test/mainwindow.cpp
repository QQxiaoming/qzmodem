#include <QFileDialog>
#include <QMessageBox>
#include <QFileInfo>

#include "qsendzmodem.h"
#include "qrecvzmodem.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit_Send->setPlaceholderText("Enter the file path to send");
    ui->lineEdit_Recv->setPlaceholderText("Enter the file path to receive");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_toolButton_Send_clicked()
{
    QString file = QFileDialog::getOpenFileName(this, "Select a file to send");
    ui->lineEdit_Send->setText(file);
}

void MainWindow::on_toolButton_recv_clicked()
{
    QString file = QFileDialog::getSaveFileName(this, "Select a file to receive");
    ui->lineEdit_Recv->setText(file);
}

void MainWindow::on_pushButton_Start_clicked()
{
    QString send = ui->lineEdit_Send->text();
    QString recv = ui->lineEdit_Recv->text();
    if (send.isEmpty() || recv.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please enter the file path");
        return;
    }
    if (send == recv) {
        QMessageBox::warning(this, "Error", "The file path to send and receive cannot be the same");
        return;
    }
    ui->lineEdit_Send->setDisabled(true);
    ui->lineEdit_Recv->setDisabled(true);
    ui->toolButton_Send->setDisabled(true);
    ui->toolButton_recv->setDisabled(true);
    
    QSendZmodem *s = new QSendZmodem(-1,this);
    QRecvZmodem *r = new QRecvZmodem(-1,this);
    connect(s,&QSendZmodem::sendData,r,&QRecvZmodem::onRecvData);
    connect(r,&QRecvZmodem::sendData,s,&QSendZmodem::onRecvData);

    connect(s,&QSendZmodem::complete,this,[=](QString filename, int result, size_t size, time_t date){
        if (result == 0)
            qDebug()<<"'"+filename+" ("+QString::number(size)+" bytes)': successful send";
        else
            qDebug()<<"'"+filename+": failed to send";
    });
    connect(r,&QRecvZmodem::complete,this,[=](QString filename, int result, size_t size, time_t date) {
        if (result == 0)
            qDebug()<<"'"+filename+" ("+QString::number(size)+" bytes)': successful recv";
        else
            qDebug()<<"'"+filename+": failed to recv";
    });

    connect(s,&QSendZmodem::tick,this,[=](const char *fname, long bytes_sent, long bytes_total, long last_bps,
                                            int min_left, int sec_left, bool *ret){
        *ret = true;
    },Qt::BlockingQueuedConnection);
    connect(r,&QRecvZmodem::tick,this,[=](const char *fname, long bytes_sent, long bytes_total, long last_bps,
                                            int min_left, int sec_left, bool *ret) {
        *ret = true;
    },Qt::BlockingQueuedConnection);
    connect(r,&QRecvZmodem::approver,this,[=](const char *filename, size_t size, time_t date, bool *ret) {
        qDebug("Sender requests to send %s: %zu bytes", filename, size);
        *ret = true;
    },Qt::BlockingQueuedConnection);

    QString sendFilePath = send;
    QFileInfo sendFileInfo(sendFilePath);
    QString sendFileName = sendFileInfo.fileName();
    QString recvFilePath = recv;
    QFileInfo recvFileInfo(recvFilePath);
    QString recvFileName = recvFileInfo.fileName();
    QString recvFileDir = recvFileInfo.dir().absolutePath();

    QStringList testSend;
    testSend.append(sendFilePath);
    QStringList testRecv;
    testRecv.append(recvFileName);
    s->setFilePath(testSend,testRecv);
    r->setFileDirPath(recvFileDir);

    connect(s,&QSendZmodem::finished,this,[=]{
        ui->lineEdit_Send->setDisabled(false);
        ui->lineEdit_Recv->setDisabled(false);
        ui->toolButton_Send->setDisabled(false);
        ui->toolButton_recv->setDisabled(false);
        s->deleteLater();
    });
    connect(r,&QRecvZmodem::finished,this,[=]{
        ui->lineEdit_Send->setDisabled(false);
        ui->lineEdit_Recv->setDisabled(false);
        ui->toolButton_Send->setDisabled(false);
        ui->toolButton_recv->setDisabled(false);
        r->deleteLater();
    });

    s->start();
    r->start();
}
