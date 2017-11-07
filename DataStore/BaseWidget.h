#ifndef BASEWIDGET_H
#define BASEWIDGET_H

#include <QtWidgets>

//绝大部分存储用户数据的接口都使用的是QVariant，也就是我们常说的“万能变量”。
//对于自定义数据类型，如果要使用QVariant，就必须使用Q_DECLARE_METATYPE注册。

//  用户信息
struct User
{
    QString strName;
    int id;
};
Q_DECLARE_METATYPE(User)

//  语言
typedef enum
{
    UI_ZH,  //  中文
    UI_EN   //  英文
} LANGUAGE;
Q_DECLARE_METATYPE(LANGUAGE)

class BaseWidget : public QWidget
{
    Q_OBJECT

public:
    BaseWidget(QWidget *parent = 0);
    ~BaseWidget();

private slots:
    void onItemClicked(QListWidgetItem* item);

private:
    void InitListWidget();
    void InitComboBox();

private:
    QGridLayout* m_pLayout;
};

#endif // BASEWIDGET_H
