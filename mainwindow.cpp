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
    std::string command = "shutdown ";
    std::string timer = "";
    int inp_time = this->getInputTime(),
        sys_time = this->getSysTime(),
        mode = ui->cmbMode->currentIndex(),
        option = ui->cmbOpt->currentIndex();

    // shutdown "after" or "at"
    if(mode == 0)
        timer = std::to_string(inp_time);
    else if(mode == 1){
        if(inp_time < sys_time)
            timer = std::to_string(24*3600 - (sys_time - inp_time));
        else
            timer = std::to_string(inp_time - sys_time);
    }

    // "turn off" or "reboot"
    if(option == 0)
        command += "/s /t " + timer;
    else if(option == 1)
        command += "/r /t " + timer;

    system(("shutdown /a & " + command).c_str());
}

int MainWindow::getSysTime(){
    time_t now = time(0);
    tm* ltm = localtime(&now);
    return ltm->tm_hour*3600 + ltm->tm_min*60 + ltm->tm_sec;
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
