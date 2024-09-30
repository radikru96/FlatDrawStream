#ifndef FIGUREVIEW_H
#define FIGUREVIEW_H

#include <QGraphicsView>

class Model;

class FigureView : public QGraphicsView {
    Q_OBJECT

public:
    explicit FigureView(QWidget *parent = nullptr);
    void setModel(Model *model);
protected:
    QGraphicsScene *scene = new QGraphicsScene;
    Model *model = nullptr;
};

#endif // FIGUREVIEW_H
