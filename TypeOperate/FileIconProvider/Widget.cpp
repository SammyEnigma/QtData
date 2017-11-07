#include "Widget.h"
#include <QFileIconProvider>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    this->setMinimumSize(QSize(500, 300));
    QGridLayout* pLayout = new QGridLayout(this);
    this->setLayout(pLayout);

    QListWidget* pListWidget = new QListWidget();
    pListWidget->setIconSize(QSize(48, 48));    //  设置单元项图片大小
    pListWidget->setResizeMode(QListView::Adjust);  //  设置大小模式-可调节
    pListWidget->setViewMode(QListView::IconMode);  //  设置显示模式
    pListWidget->setMovement(QListView::Static);    //  设置单元项不可被拖动
    pListWidget->setSpacing(10);    //  设置单元项间距
    for(int i = 0; i <= 6; ++i)
    {
        //  获取图标
        QFileIconProvider provider;
        QIcon icon = provider.icon((QFileIconProvider::IconType)i);

        //  添加单元项
        QListWidgetItem* pItem = new QListWidgetItem(pListWidget);
        pItem->setIcon(icon);
        pListWidget->addItem(pItem);
    }

    pLayout->addWidget(pListWidget);

    QStringList strList;
    strList << QString::fromUtf8("7e529e856633a9bc6c48caee6c86c3") << QString::fromUtf8("360Downloads")
            << QString::fromUtf8("不存在此文件.exe") << QString::fromUtf8("BaiduYunDownload")
            << QString::fromUtf8("1.dat") << QString::fromUtf8("config.ini")
            << QString::fromUtf8("FunBSS64.dll") << QString::fromUtf8("glib_2.18.4-1_win32.zip");

    QListWidget* pListWidget2 = new QListWidget();
    pListWidget2->setIconSize(QSize(48, 48));    //  设置单元项图片大小
    pListWidget2->setResizeMode(QListView::Adjust);  //  设置大小模式-可调节
    pListWidget2->setViewMode(QListView::IconMode);  //  设置显示模式
    pListWidget2->setMovement(QListView::Static);    //  设置单元项不可被拖动
    pListWidget2->setSpacing(10);    //  设置单元项间距
    for (int i = 0; i < strList.count(); ++i)
    {
        QFileInfo info(QString("E:\\%1").arg(strList.at(i)));

        // 获取图标、类型
        QFileIconProvider provider;
        QIcon icon = provider.icon(info);
        QString strType = provider.type(info);

        // 添加单元项
        QListWidgetItem *pItem = new QListWidgetItem(pListWidget2);
        pItem->setIcon(icon);
        pItem->setText(strType);
        pListWidget2->addItem(pItem);
    }
    pLayout->addWidget(pListWidget2, 1, 0);
}

Widget::~Widget()
{

}
