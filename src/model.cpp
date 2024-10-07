#include "model.h"

#include "figuredata.h"
#include "flatstream.h"

#include <QVector>
#include <QPoint>
#include <QStringList>
#include <QThread>
#include <QColor>
#include <QButtonGroup>

Model::Model(QObject *parent)
    : QAbstractTableModel{parent}
{
    m_Headers << "ID" << "Type" << "Position(X, Y)" << "Region(Width, Height)" << "" << "";
    flatStreamThread = new QThread();
    flatStream = new FlatStream();
    flatStream->moveToThread(flatStreamThread);
    connect(flatStreamThread,&QThread::finished, flatStream, &QObject::deleteLater);
    connect(flatStream,SIGNAL(hasPendingDatagram(QByteArray)),SLOT(insertFigureData(QByteArray)));
    flatStreamThread->start();
}

Model::~Model()
{
    flatStreamThread->quit();
    flatStreamThread->wait();
}

int Model::rowCount(const QModelIndex &parent) const
{
    return m_nData.count();
}

int Model::columnCount(const QModelIndex &parent) const
{
    return 6;
}

QVariant Model::data(const QModelIndex &index, int role) const
{
    if ( !index.isValid() || ( role != Qt::DisplayRole && role != Qt::UserRole ) )
        return QVariant();
    if ( role == Qt::UserRole )
        return QVariant(QVariant::fromValue( static_cast<void*>(m_nData[index.row()])));

    switch (static_cast<Columns>(index.column())) {
        case Id: return m_nData[index.row()]->getId();
        case Type: return getType(index,role);
        case Position: return getPosition(index,role);
        case Region: return getRegion(index,role);
        case Visible: return m_nData[index.row()]->getVisible();
    }
    return QVariant();
}

QVariant Model::headerData(int section, Qt::Orientation orientation, int role) const
{
    if ( role != Qt::DisplayRole || orientation != Qt::Horizontal )
        return QVariant();
    return m_Headers[section];
}

QColor Model::getColor(const QModelIndex &index) const
{
    return m_nData[index.row()]->getColor();
}

bool Model::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if ( index.isValid() ){
        FigureData* p = m_nData[index.row()];
        if (static_cast<Columns>(index.column()) == Visible) {
            p->setVisible( value.toBool() );
            emit visibleChanged(index);
            emit dataChanged(index,index);
            return true;
        }
    }
    return false;
}

bool Model::removeRow(int row, const QModelIndex &parent)
{
    return removeRows(row,1,parent);
}

bool Model::removeRows(int row, int count, const QModelIndex &parent)
{
    if (!parent.isValid())
        return false;
    beginRemoveRows(parent,row,row+count-1);
    m_nData.remove(row,count);
    endRemoveRows();
    emit rowRemoved(parent);
    emit dataChanged(index(row,0),index(row,columnCount()));
    return true;
}

QVariant Model::getType(const QModelIndex &index, int role) const
{
    if ( role == Qt::DisplayRole ) {
        switch ( static_cast<QFigureType>(m_nData[index.row()]->getType())) {
        case Rect : return "Rect ";
        case Ellipse: return "Ellipse";
        case Triangle: return "Triangle";
        case Line: return "Line";
        default: return QVariant();
        }
    }
    return m_nData[index.row()]->getType();
}

QVariant Model::getPosition(const QModelIndex &index, int role) const
{
    if ( role == Qt::DisplayRole ) {
        QPoint val(m_nData[index.row()]->getPoints()->first().x(),m_nData[index.row()]->getPoints()->first().y());
        switch ( static_cast<QFigureType>(m_nData[index.row()]->getType())) {
        case Rect: break;
        case Ellipse:{
            val.setX(val.x()-m_nData[index.row()]->getPoints()->at(1).x());
            val.setY(val.y()-m_nData[index.row()]->getPoints()->at(1).y());
            break;
        }
        default:{
            for ( auto i : qAsConst(*m_nData[index.row()]->getPoints()) ) {
                if ( val.x() > i.x() )
                    val.setX( i.x() );
                if ( val.y() > i.y() )
                    val.setY( i.y() );
            }
        }
        }
        return QString( QString::number(val.x()) + "px, " + QString::number(val.y()) + "px" );
    }
    return getPoints(index,role);
}

QVariant Model::getRegion(const QModelIndex &index, int role) const
{
    if ( role == Qt::DisplayRole ) {
        QPoint max(m_nData[index.row()]->getPoints()->first().x(),m_nData[index.row()]->getPoints()->first().y());
        QPoint min(0,0);
        switch (m_nData[index.row()]->getType()) {
        case QFigureType::Rect: {
            max = QPoint(m_nData[index.row()]->getPoints()->at(1).x(),m_nData[index.row()]->getPoints()->at(1).y());
            break;
        }
        case QFigureType::Ellipse:{
            max = QPoint(m_nData[index.row()]->getPoints()->at(1).x()*2,m_nData[index.row()]->getPoints()->at(1).y()*2);
            break;
        }
        case QFigureType::Line:
        case QFigureType::Triangle:{
            min = max;
            for ( auto i : qAsConst(*m_nData[index.row()]->getPoints()) ) {
                if ( max.x() < i.x() )
                    max.setX( i.x() );
                if ( max.y() < i.y() )
                    max.setY( i.y() );
                if ( min.x() > i.x() )
                    min.setX( i.x() );
                if ( min.y() > i.y() )
                    min.setY( i.y() );
            }
            break;
        default:
            return QVariant();
        }
        }
        return QString( QString::number(max.x()-min.x()) + "px, " + QString::number(max.y()-min.y()) + "px" );
    }
    return getPoints(index,role);
}

QVariant Model::getPoints(const QModelIndex &index, int role) const
{
    QList<QVariant> val;
    for ( auto i : qAsConst(*m_nData[index.row()]->getPoints() ) ) {
        val.append(i);
    }
    return QVariant( val );
}

void Model::insertFigureData(QByteArray datagram)
{
    beginInsertRows(index(this->rowCount()+1,0),this->rowCount()+1,this->rowCount()+1);
    m_nData.append( new FigureData(datagram) );
    endInsertRows();
    emit insertedFigureEvent(m_nData.last());
    connect(m_nData.last(),SIGNAL(figureMoved()),SIGNAL(figureMoved()));
}
