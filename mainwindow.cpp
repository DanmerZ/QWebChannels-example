#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QWebChannel>
#include "object.h"
#include <QDebug>
#include <QResource>
#include <QFile>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QPrinter>
#include <QTextDocument>
#include <QPrinterInfo>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //ui->webEngineWidget->load(QUrl("qrc:/index.html"));
    //ui->webEngineWidget->load(QUrl("https://habrahabr.ru"));

    // use NAM to load page
    manager = new QNetworkAccessManager(this);

    connect(manager, &QNetworkAccessManager::finished, this, [&](QNetworkReply *reply){
        QByteArray barr = reply->readAll();
        qDebug() << reply->url();
        //qDebug() << "Page: " << barr;
        this->ui->webEngineWidget->page()->setHtml(QString(barr), QUrl("http://www.mysmop.com/"));
    });

    QNetworkRequest req;
    req.setUrl(QUrl("http://www.mysmop.com/"));
    QNetworkReply *reply = manager->get(req);



    page = ui->webEngineWidget->page();


    channel = new QWebChannel;
    channel->registerObject("external", &exposedObject);
    //channel->setObjectName("myChannel");
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
    if (page->webChannel())
        qDebug() << page->webChannel()->objectName();
}

void MainWindow::onPageLoadProgress(int progress)
{
    qDebug() << "Loading in progress: " << progress;
}

void MainWindow::onPageLoadFinished()
{
    qDebug() << "Loading finished";


    QFile file(":/qtwebchannel/qwebchannel.js");
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "not read";
    }
    QString js;
    QTextStream stream(&file);
    js.append(stream.readAll());
    js += "var webChannel = new QWebChannel(qt.webChannelTransport, function(channel){ window.external = channel.objects.external; });";

    page->runJavaScript(js);

    QPrinter printer(QPrinter::PrinterResolution);

    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPaperSize(QPrinter::A4);
    printer.setOutputFileName("file.pdf");


    QTextDocument doc;
    doc.setHtml("<h1>Hello, World!</h1>\n<p>Lorem ipsum dolor sit amet, consectitur adipisci elit.</p>");
    doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
    doc.print(&printer);


    QPrinterInfo pinfo(printer);
    qDebug() << "Printer valid: " << printer.isValid();
        qDebug() << "Printer Name: " << printer.printerName();
        qDebug() << "Printer program: " << printer.printProgram();
        qDebug() << "Is printer null: " << pinfo.isNull();
        qDebug() << "Printer State: " << pinfo.state();
        qDebug() << "Is printer default: " << pinfo.isDefault();
        qDebug() << "Is printer remote: " << pinfo.isRemote();
}
