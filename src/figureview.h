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
protected:
    QGraphicsScene *scene = new QGraphicsScene();
    Model *model = nullptr;
    QVector<FigureItem*>* item;

    // void paintEvent(QPaintEvent* event = nullptr);
public slots:
    void addItemEvent(const FigureData &fd);
};

#endif // FIGUREVIEW_H
