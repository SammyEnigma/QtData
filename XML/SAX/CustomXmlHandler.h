#ifndef CUSTOMXMLHANDLER_H
#define CUSTOMXMLHANDLER_H

#include <QXmlDefaultHandler>
#include <qicon.h>

QT_BEGIN_NAMESPACE
class QTreeWidget;
class QTreeWidgetItem;
QT_END_NAMESPACE

class CustomXmlHandler : public QXmlDefaultHandler
{
public:
    explicit CustomXmlHandler(QTreeWidget* pTreeWidget);

    //  启动xml解析
    bool readFile(const QString& fileName);

public:
    //  解析开始元素
    bool startElement(const QString& namespaceURI, const QString& localName, const QString& qName, const QXmlAttributes& atts) Q_DECL_OVERRIDE;
    //  解析结束元素
    bool endElement(const QString& namespaceURI, const QString& localName, const QString& qName) Q_DECL_OVERRIDE;
    //  解析字符数据
    bool characters(const QString& ch) Q_DECL_OVERRIDE;
    //  解析过程中的错误处理
    bool fatalError(const QXmlParseException& exception) Q_DECL_OVERRIDE;
    QString errorString() const Q_DECL_OVERRIDE;

private:
    //  创建树节点
    QTreeWidgetItem *createChildItem(const QString& tagName);

private:
    QTreeWidget* m_pTreeWidget;
    QTreeWidgetItem* m_pTreeWidgetItem;
    QString m_strError;
    QString m_strCurText;

    QIcon m_iconFolder;
    QIcon m_iconOther;
};

#endif // CUSTOMXMLHANDLER_H
