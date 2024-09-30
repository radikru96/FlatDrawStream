#include "figureview.h"

#include "model.h"
#include "figureitem.h"
#include "figuredata.h"

#include <QGraphicsScene>
#include <QPainter>
#include <QDebug>

FigureView::FigureView(QWidget *parent) : QGraphicsView(parent) {
    this->setScene(scene); // Crutch???
}

void FigureView::setModel(Model *model)
{
    this->model = model;
    scene->clear();
    for ( int row = 0; row < model->rowCount(); ++row ) {
        QModelIndex index = model->index(row,0);
        FigureData* figureData = static_cast<FigureData*>( model->data(index,Qt::UserRole).value<void*>() );
        if ( !figureData->getVisible() )
            continue;
        FigureItem* item = new FigureItem( figureData->getType(),figureData->getColor(),figureData->getPoints() );
        item->setFlags(FigureItem::ItemIsMovable);
        scene->addItem(item);

        // for (int row = 0; row < model->rowCount(); ++row) {
        //     QModelIndex index = model->index(row, 0);
        //     if (!model->data(index, Qt::DisplayRole).toBool()) continue;
        //     FigureType type = model->data(index, Model::Type).value<FigureType>();
        //     QColor color = model->data(index, Model::Region).value<QColor>();
        //     QVector<QPoint>* points = model->data(index, Model::Position).value<QVector<QPoint>*>();
        //     // Create and add FigureItem
        //     FigureItem* item = new FigureItem(type, color, *points, scene);
        //     scene->addItem(item);
        // }
    }
}
