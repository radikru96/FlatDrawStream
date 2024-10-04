#ifndef MODEL_H
#define MODEL_H

#include <QAbstractTableModel>
#include "defines.h"

class QThread;
class FigureData;
class FlatStream;

class Model : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit Model(QObject *parent = nullptr);
    ~Model();
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QColor getColor(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    bool removeRow(int row, const QModelIndex &parent);
    bool removeRows(int row, int count, const QModelIndex &parent);

private:
    QVector<FigureData*> m_nData;
    QStringList m_Headers;
    QThread *flatStreamThread;
    FlatStream *flatStream;

    QVariant getType(const QModelIndex &index, int role) const;
    QVariant getPosition(const QModelIndex &index, int role) const;
    QVariant getRegion(const QModelIndex &index, int role) const;
    QVariant getPoints(const QModelIndex &index, int role) const;

public slots:
    void insertFigureData(QByteArray);
signals:
    void insertedFigureEvent(const FigureData&);
    void visibleChanged(const QModelIndex&);
    void rowRemoved(const QModelIndex&);
};

#endif // MODEL_H
