#include "figuredata.h"

#include "api_generated.h"

#include <QColor>
#include <QVector>
#include <QPoint>
#include <flatbuffers/flatbuffers.h>
#include <flatbuffers/util.h>

quint64 FigureData::count=0;

FigureData::FigureData(QFigureType type, QColor *color, QVector<QPoint> *points):
    type(type), color(color), id(count++), points(points) {}

FigureData::FigureData(QByteArray &data) : id(count++)
{
    auto buffer = flatbuffers::GetRoot<Figure>(data.constData());
    type = static_cast<QFigureType>( buffer->type() );
    auto payload = QByteArray::fromRawData(buffer->payload()->c_str(),buffer->payload()->size());
    switch (type) {
    case QFigureType::Rect: {
        auto fd = flatbuffers::GetRoot<RectData>(payload.constData());
        points = new QVector<QPoint>{QPoint(fd->x(),fd->y() ),
                                     QPoint( fd->width(),fd->height() )};
        color = new QColor( fd->color_hex()->c_str() );
        break; }
    case QFigureType::Ellipse: {
        auto fd = flatbuffers::GetRoot<EllipseData>(payload.constData());
        points = new QVector<QPoint>{QPoint(fd->x(),fd->y() ),
                                     QPoint( fd->r1(),fd->r2() )};
        color = new QColor( fd->color_hex()->c_str() );
        break; }
    case QFigureType::Triangle: {
        auto fd = flatbuffers::GetRoot<TriangleData>(payload.constData());
        points = new QVector<QPoint>{QPoint(fd->x1(),fd->y1() ),
                                     QPoint( fd->x2(),fd->y2() ),
                                     QPoint( fd->x3(),fd->y3() )};
        color = new QColor( fd->color_hex()->c_str() );
        break; }
    case QFigureType::Line: {
        auto fd = flatbuffers::GetRoot<LineData>(payload.constData());
        points = new QVector<QPoint>{QPoint(fd->x1(),fd->y1() ),
                                     QPoint( fd->x2(),fd->y2() )};
        color = new QColor( fd->color_hex()->c_str() );
        break; }
    }
}


const quint64 FigureData::getCount()
{
    return count;
}


const quint64 &FigureData::getId() const
{
    return id;
}

const bool &FigureData::getVisible() const
{
    return visible;
}

const QFigureType &FigureData::getType() const
{
    return type;
}

const QColor &FigureData::getColor() const
{
    return *color;
}

QVector<QPoint> *FigureData::getPoints() const
{
    return points;
}

void FigureData::setVisible(bool newVisible)
{
    visible = newVisible;
}

void FigureData::setType(const QFigureType &newType)
{
    type = newType;
}

void FigureData::setColor(const QColor &newColor)
{
    *color = newColor;
}

void FigureData::setPoints(QVector<QPoint> *newPoints)
{
    points = newPoints;
}
