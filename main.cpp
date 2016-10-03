#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QTextStream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();

    QFile f("/Users/oleh/err.txt");
    if (f.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream stream(&f);
        qDebug() << f.isOpen();
        stream << "hello" << endl;
    }
    f.flush();
    f.close();

    QFile f2("/Users/oleh/err.txt");
    if (f2.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream stream(&f2);
        qDebug() << f2.isOpen();
        qDebug() << f2.readAll();
    }

    f2.close();

    return a.exec();
}
