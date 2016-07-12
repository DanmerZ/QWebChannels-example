#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QWebChannel>
#include "object.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    ui->webEngineWidget->load(QUrl::fromLocalFile("/Users/oleh/Documents/test/QtProjects/TestWebEngine/index.html"));

    QWebChannel *channel = new QWebChannel(ui->webEngineWidget->page());
    channel->registerObject("myObject", &o);
    ui->webEngineWidget->page()->setWebChannel(channel);

    o.setProperty("info", 5);
    qDebug() << o.property("info");
    qDebug() << o.getInfo();

}

MainWindow::~MainWindow()
{
    delete ui;
}
