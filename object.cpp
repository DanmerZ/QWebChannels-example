#include "object.h"
#include <QDebug>

Object::Object(QObject *parent) : QObject(parent)
{

}

QString Object::getInfo() const
{
    return m_info;
}

void Object::setInfo(QString inf)
{
    m_info = inf;
}

void Object::callFromJS()
{
    qDebug("called");
}
