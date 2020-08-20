#include "MyAbstractItemModel.h"

MyAbstractItemModel::MyAbstractItemModel(QObject *parent)
    : QAbstractItemModel(parent)
{

}

void MyAbstractItemModel::rowAddedSlot()
{
    emit setIndexWhenRecordAdded();
}

