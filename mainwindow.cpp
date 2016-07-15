#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QWebChannel>
#include "object.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->webEngineWidget->load(QUrl("qrc:/index.html"));
    page = ui->webEngineWidget->page();

    channel = new QWebChannel;
    channel->registerObject("external", &exposedObject);
    page->setWebChannel(channel);

    connect(page, &QWebEnginePage::loadStarted, this, &MainWindow::onPageLoadStarted);
    connect(page, &QWebEnginePage::loadProgress, this, &MainWindow::onPageLoadProgress);
    connect(page, &QWebEnginePage::loadFinished, this, &MainWindow::onPageLoadFinished);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onPageLoadStarted()
{
    qDebug() << "Loading started";
}

void MainWindow::onPageLoadProgress(int progress)
{
    qDebug() << "Loading in progress: " << progress;
}

void MainWindow::onPageLoadFinished()
{
    qDebug() << "Loading finished";
}
