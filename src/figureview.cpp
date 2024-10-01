#include "figureview.h"

#include "model.h"
#include "figureitem.h"
#include "figuredata.h"

#include <QGraphicsScene>
#include <QPainter>
#include <QPaintEvent>

#include <QDebug>

FigureView::FigureView(QWidget *parent) : QGraphicsView(parent) {
    this->setScene(scene); // Crutch???
    item = new QVector<FigureItem*>();
}

void FigureView::setModel(Model *model)
{
    this->model = model;
    scene->clear();
    for ( int row = 0; row < model->rowCount(); ++row ) {
        // FigureData* figureData = static_cast<FigureData*>( model->data(model->index(row,0), Qt::UserRole).value<void*>() );
        if ( !figureData->getVisible() )
            continue;
        // addItem(*figureData);
        addItem(static_cast<FigureData>( model->data(model->index(row,0), Qt::UserRole).value<void*>() ););
    }
}

void FigureView::addItem(const FigureData &fd)
{
    item->append( new FigureItem( fd.getType(), fd.getColor(), fd.getPoints() ) );
    item->last()->setFlags(FigureItem::ItemIsMovable);
    scene->addItem(item->last());
    repaint();
}

void FigureView::addItemEvent(const FigureData &fd)
{
    addItem(fd);
}

