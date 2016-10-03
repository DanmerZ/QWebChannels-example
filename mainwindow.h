#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "object.h"
#include <QWebChannel>
#include <QWebEnginePage>
#include <QNetworkAccessManager>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    Object exposedObject;
    QWebChannel *channel;
    QWebEnginePage *page;
    QNetworkAccessManager *manager;

public slots:
    void onPageLoadStarted();
    void onPageLoadProgress(int progress);
    void onPageLoadFinished();
};

#endif // MAINWINDOW_H
