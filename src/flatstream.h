#ifndef FLATSTREAM_H
#define FLATSTREAM_H

#include <QObject>

class QUdpSocket;

class FlatStream : public QObject
{
    Q_OBJECT
public:
    explicit FlatStream(QObject *parent = nullptr);

private slots:
    void startListening();
    void readPendingDatagrams();
signals:
    void hasPendingDatagram(QByteArray);
private:
    QUdpSocket *socket;
};

#endif // FLATSTREAM_H
