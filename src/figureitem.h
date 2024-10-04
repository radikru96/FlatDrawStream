#ifndef FIGUREITEM_H
#define FIGUREITEM_H

#include <QGraphicsItem>

#include "defines.h"

class FigureItem : public QGraphicsItem
{
public:
    FigureItem( const QFigureType &type, const QColor &color, QVector<QPoint> *points, QGraphicsItem *parent = nullptr );
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr ) override;
    void setColor(const QColor &newColor);

private:
    QRectF getBoundingRect() const;
    QFigureType type;
    QColor color;
    QVector<QPoint> points;
};

Q_DECLARE_METATYPE(FigureItem*)

#endif // FIGUREITEM_H
