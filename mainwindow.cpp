#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    QObject::connect(ui->btnReady, SIGNAL(clicked()), this, SLOT(createCommand()));
    QObject::connect(ui->btnCancel, SIGNAL(clicked()), this, SLOT(cancelShutdown()));
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::createCommand(){
    QStringList args;
    QString timer;
    int inp_time = this->getInputTime(),
        sys_time = this->getSysTime(),
        mode = ui->cmbMode->currentIndex(),
        option = ui->cmbOpt->currentIndex();

    // "turn off" or "reboot"
    if(option==0)
        args.append("/s");
    else
        args.append("/r");

    args.append("/t");
    // shutdown "after" or "at"
    if(mode == 0)
        timer = QString::number(inp_time);
    else if(mode == 1){
        if(inp_time < sys_time)
            timer = QString::number(24*3600 - (sys_time - inp_time));
        else
            timer = QString::number(inp_time - sys_time);
    }
    args.append(timer);
    this->process.start("shutdown", args);
}

int MainWindow::getSysTime(){
    return QTime::currentTime().msecsSinceStartOfDay()/1000;
}

int MainWindow::getInputTime(){
    int hours = ui->lineH->text().toInt(),
        minutes = ui->lineM->text().toInt(),
        seconds = ui->lineS->text().toInt();
    return hours*3600 + minutes*60 + seconds;
}

void MainWindow::cancelShutdown(){
    system("shutdown /a");
}
