#ifndef WIDGET_H
#define WIDGET_H

//#include <QWidget>
#include <QtWidgets>
#include <QTimer>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void onUpdateProgress();

private:
    QTimer* m_pTimer;
    QProgressBar* m_pProgressBar;
};

#endif // WIDGET_H
