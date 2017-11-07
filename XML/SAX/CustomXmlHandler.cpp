#include "CustomXmlHandler.h"
#include <QtWidgets>

CustomXmlHandler::CustomXmlHandler(QTreeWidget *pTreeWidget)
    : QXmlDefaultHandler(),
      m_pTreeWidget(pTreeWidget)
{
    m_pTreeWidgetItem = nullptr;
    m_strError = m_strCurText = "";

    QStyle* style = m_pTreeWidget->style();
    m_iconFolder.addPixmap(style->standardPixmap(QStyle::SP_DirClosedIcon), QIcon::Normal, QIcon::Off);
    m_iconFolder.addPixmap(style->standardPixmap(QStyle::SP_DirOpenIcon), QIcon::Normal, QIcon::On);
    m_iconOther.addPixmap(style->standardPixmap(QStyle::SP_FileIcon));
}

bool CustomXmlHandler::readFile(const QString &fileName)
{
    if(fileName.isNull())
        return false;

    QFile file(fileName);
    QXmlInputSource inputSrc(&file);

    QXmlSimpleReader reader;
    reader.setContentHandler(this);
    reader.setErrorHandler(this);

    return reader.parse(inputSrc);
}

//<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
//<!--源于开源，回馈开源-->
//<?xml-stylesheet type="text/css" href="style.css"?>
//<Blogs Version="1.0">
// <Blog>
//  <author>wangds</author>
//  <home>https://github.com/andywong569</home>
//  <introduction>write less, do more</introduction>
// </Blog>
// <Blog>
//  <author>奇趣科技</author>
//  <home>https://www.qt.io</home>
//  <introduction>Qt 是由奇趣科技开发的跨平台 C++ 图形用户界面应用程序开发框架！</introduction>
// </Blog>
//</Blogs>
bool CustomXmlHandler::startElement(const QString &namespaceURI, const QString &localName, const QString &qName, const QXmlAttributes &atts)
{
    if(qName.compare("Blogs") == 0)
    {
        QString version = atts.value("Version");
        if(version.isEmpty() || version.compare("1.0") != 0)
        {
            m_strError = QObject::tr("The file is not an Xml version 1.0 file.");
            return false;
        }

        m_pTreeWidgetItem = createChildItem(qName);
        m_pTreeWidgetItem->setFlags(m_pTreeWidgetItem->flags() | Qt::ItemIsEditable);
        m_pTreeWidgetItem->setIcon(0, m_iconFolder);
        m_pTreeWidgetItem->setText(0, qName);
        m_pTreeWidgetItem->setExpanded(true);
    }
    else if(qName.compare("Blog") == 0)
    {
        m_pTreeWidgetItem = createChildItem(qName);
        m_pTreeWidgetItem->setFlags(m_pTreeWidgetItem->flags() | Qt::ItemIsEditable);
        m_pTreeWidgetItem->setIcon(0, m_iconFolder);
        m_pTreeWidgetItem->setText(0, qName);
        m_pTreeWidgetItem->setExpanded(true);
    }
    else if(qName.compare("author") == 0
            || qName.compare("home") == 0
            || qName.compare("introduction") == 0)
    {
        m_pTreeWidgetItem = createChildItem(qName);
        m_pTreeWidgetItem->setFlags(m_pTreeWidgetItem->flags() | Qt::ItemIsEditable);
        m_pTreeWidgetItem->setIcon(0, m_iconOther);
        m_pTreeWidgetItem->setText(0, qName);
    }

    m_strCurText.clear();
    return true;
}

//  在遇到结束标签时回调此函数。
//  遇到</Blog></author></home></introduction>标签时将当前结点指向父节点，保证下次创建子节点时的指向正确
bool CustomXmlHandler::endElement(const QString &namespaceURI, const QString &localName, const QString &qName)
{
    if(qName.compare("Blog") == 0)
    {
        if(m_pTreeWidgetItem)
            m_pTreeWidgetItem = m_pTreeWidgetItem->parent();
    }
    else if(qName.compare("author") == 0
            || qName.compare("home") == 0
            || qName.compare("introduction") == 0)
    {
        m_pTreeWidgetItem->setText(1, m_strCurText);
        if(m_pTreeWidgetItem)
            m_pTreeWidgetItem = m_pTreeWidgetItem->parent();
    }

    return true;
}

//  将标签的内容保存至成员变量中，之后由endElement()设置为结点的文本
bool CustomXmlHandler::characters(const QString &ch)
{
    m_strCurText.append(ch);
    return true;
}

//  当遇到处理失败的时候SAX会回调该函数。
bool CustomXmlHandler::fatalError(const QXmlParseException &exception)
{
    QMessageBox::information(m_pTreeWidget->window(), QObject::tr("SAX Parser"),
                             QObject::tr("Parse error at line %1, column %2:\n"
                                         "%3")
                             .arg(exception.lineNumber())
                             .arg(exception.columnNumber())
                             .arg(exception.message()));
    return false;
}

//  当handler的任何一个函数返回false时，该函数会得到一个错误的字符串。
QString CustomXmlHandler::errorString() const
{
    return m_strError;
}

QTreeWidgetItem *CustomXmlHandler::createChildItem(const QString &tagName)
{
    QTreeWidgetItem* childItem = nullptr;
    if(m_pTreeWidgetItem)
    {
        childItem = new QTreeWidgetItem(m_pTreeWidgetItem);
    }
    else
    {
        childItem = new QTreeWidgetItem(m_pTreeWidget);
    }
    childItem->setData(0, Qt::UserRole, tagName);
    return childItem;
}
