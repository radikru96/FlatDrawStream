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

private:
    void addItem(const FigureData &fd);

public slots:
    void addItemEvent(const FigureData &fd);

protected:
    QGraphicsScene *scene = new QGraphicsScene();
    Model *model = nullptr;
    QVector<FigureItem*>* item;

};

#endif // FIGUREVIEW_H
