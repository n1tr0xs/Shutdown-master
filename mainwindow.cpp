#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "common.h"

#include <QMessageBox>
#include <QProcess>
#include <QTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    connect(ui->pushButtonShutdown,
            &QPushButton::clicked,
            this,
            &MainWindow::onPushButtonShutdownClicked);
    connect(ui->pushButtonCancel,
            &QPushButton::clicked,
            this,
            &MainWindow::onCancelShutdownClicked);
}

MainWindow::~MainWindow() {
    delete ui;
}

int MainWindow::m_getInputTime() {
    int hours = ui->spinBoxHours->value();
    int minutes = ui->spinBoxMinutes->value();
    int seconds = ui->spinBoxSeconds->value();
    return hours * 3600 + minutes * 60 + seconds;
}

int MainWindow::m_getSystemTime() {
    return QTime::currentTime().msecsSinceStartOfDay() / 1000;
}

void MainWindow::onPushButtonShutdownClicked() {
    QStringList args;

    int input_time = m_getInputTime();
    int current_time = m_getSystemTime();
    int option = ui->comboBoxOption->currentIndex();
    int mode = ui->comboBoxMode->currentIndex();

    // "turn off" / "reboot"
    switch (option) {
        case 0: // turn off
            args << "/s";
            break;
        case 1: // reboot
            args << "/r";
            break;
        default:
            return;
    }
    DEBUG("Args after option switch: " << args);

    // "after" / "at"
    int diff;
    switch (mode) {
        case 0: // after
            diff = input_time;
            break;
        case 1: // at
            diff = (input_time - current_time + 24 * 3600) % (24 * 3600);
            if (diff == 0)
                diff = 24 * 3600;
            break;
        default:
            return;
    }
    args << "/t" << QString::number(diff);
    DEBUG("Args after mode switch: " << args);

    m_runCommand("shutdown", args);
}

void MainWindow::onCancelShutdownClicked() {
    QStringList args{"/a"};
    m_runCommand("shutdown", args);
}

void MainWindow::m_runCommand(const QString &command, const QStringList &args) {
    QProcess process;
    DEBUG("Running " << command << args);
    process.start(command, args);
    if (!process.waitForStarted(2000)) {
        QMessageBox::warning(this, "Error", "Couldn't start shutdown.exe");
    }
}
