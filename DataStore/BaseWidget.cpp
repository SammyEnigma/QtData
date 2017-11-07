#include "BaseWidget.h"

BaseWidget::BaseWidget(QWidget *parent)
    : QWidget(parent)
{
    m_pLayout = new QGridLayout(this);
    this->setLayout(m_pLayout);

    InitListWidget();
    InitComboBox();
}

BaseWidget::~BaseWidget()
{

}

void BaseWidget::onItemClicked(QListWidgetItem *item)
{
    QVariant variant = item->data(Qt::UserRole);
    if(variant.canConvert<User>())
    {
        User user = variant.value<User>();

        qDebug() << "id: " << user.id;
        qDebug() << "name: " << user.strName;
    }
}

void BaseWidget::InitListWidget()
{
    QListWidget* pListWidget = new QListWidget;
    int i = 0;
    do
    {
        QListWidgetItem* pItem = new QListWidgetItem(pListWidget);
        //  单独存储
//        pItem->setData(Qt::UserRole, i);  // 用户数据
//        pItem->setData(Qt::UserRole + 1, QString("Qter %1").arg(i));  // 用户数据

        //  整体存储，推荐
        User user;
        user.id = ++i;
        user.strName = QString("Qter %1").arg(i);
        pItem->setData(Qt::UserRole, QVariant::fromValue(user));
        pItem->setText(QString("Item %1").arg(i));
        pListWidget->addItem(pItem);
    }while(i < 5);

    m_pLayout->addWidget(pListWidget, 0, 0, 5, 3);

    connect(pListWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(onItemClicked(QListWidgetItem*)));
}

void BaseWidget::InitComboBox()
{
    QComboBox* pComboBox = new QComboBox();
    pComboBox->addItem("Chinese", QVariant::fromValue(UI_ZH));
    pComboBox->addItem("English", QVariant::fromValue(UI_EN));

    //  连接信号
    connect(pComboBox, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
          [=](int index)
        {
            qDebug() << pComboBox->itemData(index).value<LANGUAGE>();
        });

    //  add into layout
    m_pLayout->addWidget(pComboBox, 5, 2, Qt::AlignRight | Qt::AlignVCenter);
}
