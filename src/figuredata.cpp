#include "figuredata.h"

#include "api_generated.h"

#include <QColor>
#include <QVector>
#include <QPoint>
#include <flatbuffers/flatbuffers.h>
#include <flatbuffers/util.h>
#include <QString>

#include <QDebug>

quint64 FigureData::count=0;

FigureData::FigureData(QFigureType type, QColor *color, QVector<QPoint> *points):
    type(type), color(color), id(count++), points(points) {}

// FigureData::FigureData(QByteArray &data) : id(count++)
// {
// }


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
