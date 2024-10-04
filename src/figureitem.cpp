#include "figureitem.h"

#include <QPainter>
#include <QColor>
#include <QVector>
#include <QPoint>

FigureItem::FigureItem(const QFigureType &type, const QColor &color, QVector<QPoint> *points, QGraphicsItem *parent)
    : QGraphicsItem(parent), type(type), color(color)
{
    for ( auto i: qAsConst(*points)) {
        this->points.append(i);
    }
}

QRectF FigureItem::boundingRect() const
{
    if (color != QColor(Qt::transparent)){
        switch (type) {
        case QFigureType::Rect:
            if (points.size() >= 2)
                return QRectF( points[0], points[1]+points[0] );
            break;
        case QFigureType::Ellipse:
            if (points.size() >= 2)
                return QRectF(QRect( QPoint(points[0].x()-points[1].x()
                                           ,points[0].y()-points[1].y() )
                                    ,QSize(points[1].x()*2, points[1].y()*2) ));
            break;
        default:
            return getBoundingRect();
            break;
        }
    }
    return QRectF();
}

QRectF FigureItem::getBoundingRect() const
{
    if ( type != QFigureType::Triangle && type != QFigureType::Line )
        return QRectF();
    QPoint max(points[0].x(),points[0].y());
    QPoint min(max.x(),max.y());
    for ( int i = 1; i < (type==QFigureType::Line? 2 : 3 ); ++i ) {
        if ( max.x() < points[i].x() )
            max.setX( points[i].x() );
        if ( max.y() < points[i].y() )
            max.setY( points[i].y() );
        if ( min.x() > points[i].x() )
            min.setX( points[i].x() );
        if ( min.y() > points[i].y() )
            min.setY( points[i].y() );
    }
    return QRectF(min,max);
}

void FigureItem::setColor(const QColor &newColor)
{
    color = newColor;
}

void FigureItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(QPen(color, 0));
    painter->setBrush(QBrush(color));
    switch (type) {
    case QFigureType::Rect:
        if (points.size() >= 2)
            painter->drawRect(QRect(points[0], points[1]+points[0]));
        break;
    case QFigureType::Line:
        if (points.size() >= 2)
            painter->drawLine(points[0], points[1]);
        break;
    case QFigureType::Ellipse:
        if (points.size() >= 2)
            painter->drawEllipse(points[0], points[1].x(), points[1].y());
        break;
    case QFigureType::Triangle:
        if (points.size() >= 3)
            painter->drawPolygon(QPolygon(points));
        break;
    }
}
