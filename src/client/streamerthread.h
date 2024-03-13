#ifndef STREAMERTHREAD_H
#define STREAMERTHREAD_H

#include <QObject>
#include <QThread>
#include <QTcpSocket>

class StreamerThread : public QThread
{
    Q_OBJECT

public:
    StreamerThread(QObject *parent);
    void run();
    QTcpSocket *socket;

private:
    QByteArray m_baImage; // Contain the received image.
    bool m_quit; // Variable used to know that the application is closing.

private slots:
    void slotQuit(); // The slot called when closing the application.

signals:
    void signalNouvelleImage(QByteArray baImage); // Signal emitted when a new image is received.
};

#endif // STREAMERTHREAD_H
