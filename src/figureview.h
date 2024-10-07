#ifndef FIGUREVIEW_H
#define FIGUREVIEW_H

#include <QGraphicsView>
#include <QVector>

class FigureItem;
class FigureData;
class Model;

class FigureView : public QGraphicsView {
    Q_OBJECT

public:
    explicit FigureView(QWidget *parent = nullptr);
    void setModel(Model *model);

public slots:
    void addItemEvent(FigureData *fd);
    void repaintEvent(const QModelIndex &topLeft);

protected:
    QGraphicsScene *scene = new QGraphicsScene(this);
    Model *model = nullptr;
    QVector<FigureItem*> *item;

};

#endif // FIGUREVIEW_H
