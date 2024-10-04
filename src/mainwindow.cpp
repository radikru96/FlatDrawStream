#include "mainwindow.h"

#include "model.h"
#include "figureview.h"
#include "delegatebutton.h"

#include <QMenuBar>
#include <QKeySequence>
#include <QHeaderView>
#include <QTableView>
#include <QStackedLayout>

MainWindow::MainWindow(QWidget *parent)
{
    QWidget *w = new QWidget;
    setCentralWidget(w);

    Model *model = new Model();

    tv = new QTableView();
    tv->setModel(model);
    tv->verticalHeader()->hide();
    tv->resizeColumnsToContents();

    auto *delegate = new DelegateButton();
    tv->setItemDelegateForColumn(Columns::Visible,delegate);
    tv->setItemDelegateForColumn(Columns::Delete,delegate);


    fv = new FigureView();
    fv->setModel(model);

    sl = new QStackedLayout();
    sl->addWidget(tv);
    sl->addWidget(fv);
    w->setLayout(sl);

    createActions();
    createMenus();

    setMinimumSize(160, 160);
    resize(480, 320);

    connect(model, SIGNAL(insertedFigureEvent(FigureData)), fv, SLOT(addItemEvent(FigureData)) );
    connect(model, SIGNAL(visibleChanged(QModelIndex)), fv, SLOT(repaintEvent(QModelIndex)) );
    connect(model, SIGNAL(rowRemoved(QModelIndex)), fv, SLOT(repaintEvent(QModelIndex)) );
}

void MainWindow::rendering()
{
    sl->setCurrentWidget(fv);
}

void MainWindow::info()
{
    sl->setCurrentWidget(tv);
}

void MainWindow::createActions()
{
    renderingAct = new QAction(tr("&Render"),this);
    renderingAct->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_R));
    connect(renderingAct, &QAction::triggered, this, &MainWindow::rendering);

    infoAct = new QAction(tr("&Info"),this);
    infoAct->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_I));
    connect(infoAct, &QAction::triggered, this, &MainWindow::info);
}

void MainWindow::createMenus()
{
    menu = menuBar()->addMenu(tr("&Menu"));
    menu->addAction(renderingAct);
    menu->addAction(infoAct);
}
