#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <QTimer>
#include <QDebug>
#include <string>
#include <QSound>
#include <QLabel>
#include <QTcpServer>
#include "tcpserver.h"
#include <QHostAddress>
#include <QBuffer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_btnFS_clicked();

    void on_btnQuit_clicked();

    void Display(int index);

    void Tick();

    void Play();

    void Stop();

    void tickManager(int speed);

    void on_slidVideo_sliderMoved(int position);

    void on_btnLecture_clicked();

    void on_spnVitesse_valueChanged(int arg1);

    void on_clientConnection();

    void on_clientDisconnection();

    QString convertIndex(int index);

private:
    Ui::MainWindow *ui;

    // Member variables
    bool _isFullScreen = false;
    QTimer *timer;
    QLabel *clock;
    float _speed = 1;
    bool _isPlaying = false;
    int _imgIndex = 0;
    TCPServer *server;
};

#endif // MAINWINDOW_H
