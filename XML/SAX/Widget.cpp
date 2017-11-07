#include "Widget.h"
#include "CustomXmlHandler.h"


Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    this->setMinimumSize(600, 400);
    m_pLayout = new QGridLayout(this);
    this->setLayout(m_pLayout);

    m_pTreeWidget = nullptr;

    InitPushBtn();
    InitTreeWidget();
}

Widget::~Widget()
{

}

void Widget::InitPushBtn()
{
    QPushButton* openBtn = new QPushButton(QString(u8"打开"));
    QPushButton* saveBtn = new QPushButton(u8"保存");

    connect(openBtn, SIGNAL(clicked(bool)), this, SLOT(onClickOpen()));
    connect(saveBtn, SIGNAL(clicked(bool)), this, SLOT(onClickSave()));

    m_pLayout->addWidget(openBtn, 0, 0);
    m_pLayout->addWidget(saveBtn, 0, 1);
}

void Widget::InitTreeWidget()
{
    m_pTreeWidget = new QTreeWidget();
    m_pTreeWidget->setColumnCount(2);
    QStringList headerList;
    headerList << u8"标题" << u8"描述";
    m_pTreeWidget->setHeaderLabels(headerList);

    m_pLayout->addWidget(m_pTreeWidget, 1, 0, 5, 5);
}

void Widget::onClickOpen()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::currentPath(), tr("XBEL Files (*.xbel *.xml)"));
    if(fileName.isEmpty())
        return;

    CustomXmlHandler handler(m_pTreeWidget);
    if(handler.readFile(fileName))
        qDebug() << "File loaded";
}

void Widget::onClickSave()
{

}
