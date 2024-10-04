#include "model.h"
#include "figureitem.h"
#include "figuredata.h"

#include "figureview.h"

#include <QGraphicsScene>
#include <QPainter>
#include <QPaintEvent>

// #include <QDebug>

FigureView::FigureView(QWidget *parent) : QGraphicsView(parent) {
    this->setScene(scene); // Crutch???
    item = new QVector<FigureItem*>();
}

void FigureView::setModel(Model *model)
{
    this->model = model;
    scene->clear();
    for ( int row = 0; row < model->rowCount(); ++row ) {
        addItemEvent(*static_cast<FigureData*>( model->data(model->index(row,0), Qt::UserRole).value<void*>() ) );
    }
}

void FigureView::addItemEvent(const FigureData &fd)
{
    if ( fd.getVisible() ) {
        item->append( new FigureItem( fd.getType(), fd.getColor(), fd.getPoints() ) );
        item->last()->setFlags(FigureItem::ItemIsMovable);
        scene->addItem(item->last());
        repaint();
    }
}

void FigureView::repaintEvent(const QModelIndex &index)
{
    if (index.column() == Columns::Visible)
        item->at(index.row())->setColor(index.data().toBool() ? model->getColor(index) : QColor(Qt::transparent));
    else if (index.column() == Columns::Delete){
        scene->removeItem(item->at(index.row()));
        item->remove(index.row());
    }
    repaint();
}
