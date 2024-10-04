#ifndef DELEGATEBUTTON_H
#define DELEGATEBUTTON_H

#include <QItemDelegate>

class DelegateButton : public QItemDelegate
{
    Q_OBJECT
public:
    explicit DelegateButton(QObject *parent = nullptr);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);
};

#endif // DELEGATEBUTTON_H
