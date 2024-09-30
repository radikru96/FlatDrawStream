#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QStackedLayout;
class QTableView;
class FigureView;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
private slots:
    void rendering();
    void info();
private:
    void createActions();
    void createMenus();

    QMenu *menu;
    QAction *renderingAct;
    QAction *infoAct;
    QStackedLayout *sl;
    QTableView *tv;
    FigureView *fv;
};
#endif // MAINWINDOW_H
