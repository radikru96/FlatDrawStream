#ifndef MODEL_H
#define MODEL_H

#include <QAbstractTableModel>

class QThread;
class FigureData;
class FlatStream;

class Model : public QAbstractTableModel
{
    Q_OBJECT
public:
    enum Columns {
        Id,
        Type,
        Position,
        Region,
        Visible
    };
    explicit Model(QObject *parent = nullptr);
    ~Model();
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;

private:
    QVector<FigureData*> m_nData;
    QStringList m_Headers;
    QThread *flatStreamThread;
    FlatStream *flatStream;

    QVariant getType(const QModelIndex &index, int role) const;
    QVariant getPosition(const QModelIndex &index, int role) const;
    QVariant getRegion(const QModelIndex &index, int role) const;
    QVariant getPoints(const QModelIndex &index, int role) const;
    QVariant getVisible(const QModelIndex &index, int role) const;

public slots:
    void insertFigureData(QByteArray);
};

#endif // MODEL_H
