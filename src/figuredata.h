#ifndef FIGUREDATA_H
#define FIGUREDATA_H

#include <QObject>

#include "defines.h"

class QColor;
class QPoint;

class FigureData : public QObject
{
    Q_OBJECT
private:

    static quint64 count;

    const quint64 id;
    bool visible = true;
    QFigureType type;
    QColor *color;
    QVector<QPoint> *points;

public:

    FigureData(QFigureType type, QColor *color, QVector<QPoint>* points);
    FigureData(QByteArray &data);

    const static quint64 getCount();

    const quint64 &getId() const;
    const bool &getVisible() const;
    const QFigureType &getType() const;
    const QColor &getColor() const;
    QVector<QPoint> *getPoints() const;

    void setVisible(bool newVisible);
    void setType(const QFigureType &newType);
    void setColor(const QColor &newColor);
    void setPoints(QVector<QPoint> *newPoints);

};

Q_DECLARE_METATYPE(FigureData*)

#endif // FIGUREDATA_H
