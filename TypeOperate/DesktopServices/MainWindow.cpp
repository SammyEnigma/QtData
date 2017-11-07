#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QDesktopServices>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QDesktopServices::setUrlHandler("http", this, "openUrl");
    QDesktopServices::setUrlHandler("file", this, "openUrl");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openUrl(const QUrl &url)
{
    QString strScheme = url.scheme();
    if(strScheme.compare("http", Qt::CaseInsensitive) == 0)
    {
        QMessageBox::information(this, QString::fromLocal8Bit("提示"), QStringLiteral("打开的是一个网址：%1").arg(url.url()));
        QDesktopServices::unsetUrlHandler("http");
        return;
    }
    else if(strScheme.compare("file", Qt::CaseInsensitive) == 0)
    {
        QMessageBox::information(this, QString::fromLocal8Bit("提示"), QStringLiteral("打开的是一个文件：%1").arg(url.url()));
        return;
    }
}

void MainWindow::on_pushButton_clicked()
{
    QDesktopServices::openUrl(QUrl(ui->lineEdit->text()));
}
