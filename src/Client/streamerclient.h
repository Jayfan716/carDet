#ifndef STREAMERCLIENT_H
#define STREAMERCLIENT_H

#include <QMainWindow>
//extern int state0,state1,state2,state3,state4;
#include <QCheckBox>

namespace Ui {
class TheStreamerClient;
}

class TheStreamerClient : public QMainWindow
{
    Q_OBJECT

public:
    explicit TheStreamerClient(QWidget *parent = 0);
    ~TheStreamerClient();

private:
    Ui::TheStreamerClient *ui;
    // Declare checkbox pointers as member variables
    QCheckBox *checkBox;
    QCheckBox *checkBox_2;
    QCheckBox *checkBox_3;

    int classId = 0;

private slots:

    void slotNouvelleImage(QByteArray baImag); // Slot called when receiving a new image.

    void on_checkBox_stateChanged(int arg1);

    void on_checkBox_2_stateChanged(int arg1);

    void on_checkBox_3_stateChanged(int arg1);

    void on_btnFS_clicked();

    void on_btnQuit_clicked();


signals:
    void signalQuit(); // Signal emitted when closing the application.
};

#endif // STREAMERCLIENT_H
