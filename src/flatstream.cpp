#include "flatstream.h"
#include <QUdpSocket>
#include <QDebug>

#include "api_generated.h"

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

        flatbuffers::FlatBufferBuilder builder;
        auto buffer = flatbuffers::GetRoot<Figure>(datagram.constData());
        FigureType type = static_cast<FigureType>( buffer->type() );
        switch (type) {
        case FigureType::FigureType_Rect: {
            // auto fd = buffer->
            // auto fd = flatbuffers::GetRoot<RectData>(datagram.constData());
            RectData fd = buffer->Get( Figure::VT_PAYLOAD );
            // RectData fd = buffer->payload()->GetStructFromOffset(RectDataBuilder);
            qDebug() << "Rect:x=" << fd.x() << ", y=" << fd.y()
                     << ", width=" << fd.width() << ", height=" << fd.height()
                     // << ", color=" << QString(fd-color_hex()->data())
                ;
            // *color = QColor( fd->color_hex()->data() );
            break; }
        case FigureType::FigureType_Ellipse: {
            // auto fd = flatbuffers::GetRoot<EllipseData>(data.constData());
            // // EllipseData fd = buffer->payload();
            // points = new QVector<QPoint>{QPoint(fd->x(),fd->y() ),
            //                              QPoint( fd->r1(),fd->r2() )};
            // qDebug() << "fd->color_hex()->data() == " << fd->color_hex()->data();
            // *color = QColor( fd->color_hex()->data() );
            break; }
        case FigureType::FigureType_Triangle: {
            // auto fd = flatbuffers::GetRoot<TriangleData>(data.constData());
            // // TriangleData fd = (buffer->payload());
            // points = new QVector<QPoint>{QPoint(fd->x1(),fd->y1() ),
            //                              QPoint( fd->x2(),fd->y2() ),
            //                              QPoint( fd->x3(),fd->y3() )};
            // qDebug() << "fd->color_hex()->data() == " << fd->color_hex()->data();
            // *color = QColor( fd->color_hex()->data() );
            break; }
        case FigureType::FigureType_Line: {
            // auto fd = flatbuffers::GetRoot<LineData>(data.constData());
            // // LineData fd = (buffer->payload());
            // points = new QVector<QPoint>{QPoint(fd->x1(),fd->y1() ),
            //                              QPoint( fd->x2(),fd->y2() )};
            // qDebug() << "fd->color_hex()->data() == " << fd->color_hex()->data();
            // *color = QColor( fd->color_hex()->data() );
            break; }
        }

        emit hasPendingDatagram(datagram);
        qDebug() << sender << senderPort << "datagram";
        datagram.clear();
    }
}
