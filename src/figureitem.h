#ifndef FIGUREITEM_H
#define FIGUREITEM_H

#include <QGraphicsItem>

#include "defines.h"
#include "figuredata.h"

class FigureItem : public QGraphicsItem
{
public:
    FigureItem( FigureData *fd, QGraphicsItem *parent = nullptr );
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr ) override;
    void setColor(const QColor &newColor);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent*);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent*);

private:
    QRectF getBoundingRect() const;
    QFigureType type;
    QColor color;
    QPoint *moveData;
    FigureData *fd;
    QVector<QPoint> points;

};

Q_DECLARE_METATYPE(FigureItem*)

#endif // FIGUREITEM_H
