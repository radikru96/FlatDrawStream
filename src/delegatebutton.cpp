#include "delegatebutton.h"

#include <QApplication>
#include <QMouseEvent>
#include <QPainter>
#include "model.h"
#include "defines.h"

// #include <QDebug>

DelegateButton::DelegateButton(QObject *parent)
    : QItemDelegate{parent}
{}

void DelegateButton::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->save();
    QStyleOptionButton button;
    button.rect = option.rect;
    if ( index.column() == Columns::Visible ){
        button.icon = QIcon(":/images/v.png");
        if (!index.data().toBool())
            painter->setOpacity(0.3);
    }
    else if ( index.column() == Columns::Delete ){
        button.icon = QIcon(":/images/x.png");
    }
    button.iconSize.scale(option.rect.size(),Qt::KeepAspectRatio );
    button.state = QStyle::State_Enabled;
    QApplication::style()->drawControl(QStyle::CE_PushButtonLabel, &button, painter);
    painter->restore();
}

bool DelegateButton::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    if ( event->type() == QEvent::MouseButtonRelease ) {
        QMouseEvent *e = (QMouseEvent *)event;
        if ( e->pos().x() > option.rect.left() && e->pos().x() < option.rect.right() ) {
            if ( e->pos().y() > option.rect.top() && e->pos().y() < option.rect.bottom() ) {
                if (index.column() == Columns::Visible)
                    return model->setData(index, !model->data(index).toBool() );
                else if (index.column() == Columns::Delete){
                    return static_cast<Model*>(model)->removeRow(index.row(),index);
                }
            }
        }
    }
    return false;
}
