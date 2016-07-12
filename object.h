#ifndef OBJECT_H
#define OBJECT_H

#include <QObject>

class Object : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString info MEMBER m_info READ getInfo WRITE setInfo NOTIFY infoChanged)
public:
    explicit Object(QObject *parent = 0);

    QString getInfo() const;
    void setInfo(QString inf);

signals:
    void infoChanged(QString);
public slots:
    void callFromJS();
private:
    QString m_info;
};

#endif // OBJECT_H
