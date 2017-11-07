#include "Widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    this->setMinimumSize(QSize(400, 150));
    QGridLayout* playout = new QGridLayout(this);
    this->setLayout(playout);

    QPushButton* pStartBtn = new QPushButton(QString::fromUtf8(u8"开始"));
    QPushButton* pStopBtn = new QPushButton(QString::fromUtf8(u8"停止"));
    m_pProgressBar = new QProgressBar();
    m_pProgressBar->setRange(0, 100);
    m_pProgressBar->setValue(50);
    m_pProgressBar->setFixedHeight(20);


    playout->addWidget(m_pProgressBar, 0, 0, 1, 4);
    playout->addWidget(pStartBtn, 1, 2, Qt::AlignRight | Qt::AlignVCenter);
    playout->addWidget(pStopBtn, 1, 3, Qt::AlignRight | Qt::AlignVCenter);

    m_pTimer = new QTimer();
    m_pTimer->setInterval(50);

    connect(pStartBtn, SIGNAL(clicked(bool)), m_pTimer, SLOT(start()));
    connect(pStopBtn, SIGNAL(clicked(bool)), m_pTimer, SLOT(stop()));
    connect(m_pTimer, SIGNAL(timeout()), this, SLOT(onUpdateProgress()));
}

Widget::~Widget()
{

}

void Widget::onUpdateProgress()
{
    int nCurValue = m_pProgressBar->value();
    if(nCurValue > 100)
    {
        m_pTimer->stop();
    }
    else
    {
        ++nCurValue;
        m_pProgressBar->setValue(nCurValue);
    }
}
