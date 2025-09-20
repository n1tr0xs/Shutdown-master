#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    // Returns the total time in seconds from user input (HH:MM:SS
    int m_getInputTime();
    // Returns the current time in seconds since the start of the day
    int m_getSystemTime();
    // Runs the specified command with arguments
    void m_runCommand(const QString &command, const QStringList &args);

private slots:
    // Executes shutdown or reboot based on user input
    void onPushButtonShutdownClicked();

    // Cancels any pending shutdown/reboot
    void onCancelShutdownClicked();
};
#endif // MAINWINDOW_H
