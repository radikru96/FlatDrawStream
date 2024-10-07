#include "model.h"
#include "figureitem.h"
#include "figuredata.h"

#include "figureview.h"

#include <QGraphicsScene>
#include <QPainter>
#include <QPaintEvent>

FigureView::FigureView(QWidget *parent) : QGraphicsView(parent) {
    this->setScene(scene);
    item = new QVector<FigureItem*>(); //need anchor scene to view
}

void FigureView::setModel(Model *model)
{
    this->model = model;
    scene->clear();
    for ( int row = 0; row < model->rowCount(); ++row ) {
        addItemEvent(static_cast<FigureData*>( model->data(model->index(row,0), Qt::UserRole).value<void*>() ) );
    }
}

void FigureView::addItemEvent(FigureData *fd)
{
    if ( fd->getVisible() ) {
        item->append( new FigureItem( fd ) );
        item->last()->setFlags(FigureItem::ItemIsMovable);
        scene->addItem(item->last());
        repaint();
    }
}

void FigureView::repaintEvent(const QModelIndex &index)
{
    if (index.column() == Columns::Visible) {
        if (index.data().toBool()) item->at(index.row())->show();
        else item->at(index.row())->hide();
    }
    else if (index.column() == Columns::Delete){
        scene->removeItem(item->at(index.row()));
        item->remove(index.row());
    }
    repaint();
}
