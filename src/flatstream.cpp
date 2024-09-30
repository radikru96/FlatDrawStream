#include "flatstream.h"
#include <QUdpSocket>

FlatStream::FlatStream(QObject *parent)
    : QObject{parent}
{
    socket = new QUdpSocket(this);
    socket->bind(QHostAddress::LocalHost, 10002);
    startListening();
}

void FlatStream::startListening()
{
    connect(socket, &QUdpSocket::readyRead, this, &FlatStream::readPendingDatagrams);
}

void FlatStream::readPendingDatagrams()
{
    while (socket->hasPendingDatagrams() ) {
        QByteArray datagram;
        datagram.resize(socket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;
        socket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);

        emit hasPendingDatagram(datagram);
        datagram.clear();
    }
}
