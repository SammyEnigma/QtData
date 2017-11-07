#include "MyDom.h"

//QDomDocument 类表示一个 XML 文档。

//QDomDocument 类表示整个 XML 文档。从概念上讲，它是文档树的根，并提供对文档数据的主要访问。

//因为元素、文本节点、注释、处理指令等不能存在于文档的上下文之外，所以文档类还包含创建这些对象所需的工厂函数。
//创建的节点对象有一个 ownerDocument() 函数，将它们与在其上下文中创建的文档相关联。
//最常用的 DOM 类是 QDomNode、QDomDocument、QDomElement 和 QDomText。

//解析的 XML 在内部由对象树表示，可以使用各种 QDom 类访问，所有的 QDom 类只引用内部树中的对象。
//一旦最后一个 QDom 对象引用它们或 QDomDocument 本身被删除，DOM 树中的内部对象将被删除。

//元素、文本节点等的创建使用此类中提供的各种工厂函数完成。使用 QDom 类的默认构造函数只会导致无法操作或插入到 Document 中的空对象。

//QDomDocument 类具有创建文档数据的多个函数，
//例如：createElement()、createTextNode()、createComment()、createCDATASection()、
//    createProcessingInstruction()、createAttribute() 和 createEntityReference()。
//这些函数中的一些具有支持命名空间的版本，即：createElementNS() 和 createAttributeNS()。
//createDocumentFragment() 函数用于保存文档的各部分，这对于处理复杂文档很有用。

//文档的整个内容使用 setContent() 设置。此函数解析的字符串，作为一个 XML 文档以及创建表示文档的 DOM 树传递。
//根元素可以使用 documentElement() 来获取，文档的文本表示可以使用 toString() 获取。

//注意：如果 XML 文档较大，DOM 树可能最终会保留大量内存。对于这样的文档，QXmlStreamReader 或 QXmlQuery 类可能是更好的解决方案。

//可以使用 importNode() 将来自另一个文档的节点插入到文档中。

//可以根据 elementsByTagName() 或 elementsByTagNameNS() 获取具有特定标记的所有元素的列表。



//<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
//<!--源于开源，回馈开源-->
//<?xml-stylesheet type="text/css" href="style.css"?>
//<Blogs Version="1.0">
// <Blog>
//  <作者>wangds</作者>
//  <主页>https://github.com/andywong569</主页>
//  <个人说明>write less, do more</个人说明>
// </Blog>
//</Blogs>

void MyDom::writeXML()
{
    QDomDocument doc;

    QDomProcessingInstruction xmlInstruction = doc.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"");
    QDomComment comment = doc.createComment(QString::fromUtf8(u8"源于开源，回馈开源"));
    QDomProcessingInstruction styleInstruction = doc.createProcessingInstruction("xml-stylesheet", "type=\"text/css\" href=\"style.css\"");
    doc.appendChild(xmlInstruction);  // 开始文档（XML 声明）
    doc.appendChild(comment);  // 注释
    doc.appendChild(styleInstruction);  // 处理指令

    // 根元素 <Blogs>
    QDomElement root = doc.createElement("Blogs");
    root.setAttribute("Version", "1.0");  // 属性
    doc.appendChild(root);

    // 元素 <Blog>
    QDomElement child = doc.createElement("Blog");
    root.appendChild(child);

    // 元素 <作者>、<主页>、<个人说明>
    QDomElement author = doc.createElement(QString::fromUtf8(u8"作者"));
    QDomElement home = doc.createElement(QString::fromUtf8(u8"主页"));
    QDomElement instroduction = doc.createElement(QString::fromUtf8(u8"个人说明"));
    child.appendChild(author);
    child.appendChild(home);
    child.appendChild(instroduction);

    // 元素的文本数据
    QDomText authorText = doc.createTextNode(QString::fromUtf8("wangds"));
    QDomText homeText = doc.createTextNode("https://github.com/andywong569");
    QDomText instroductionText = doc.createTextNode(QString::fromUtf8("write less, do more"));
    author.appendChild(authorText);
    home.appendChild(homeText);
    instroduction.appendChild(instroductionText);

    // 保存 XML 文件
    QFile file(QString("Blogs.xml"));
    if (file.open(QFile::WriteOnly | QFile::Text))
    { // 只写模式打开文件
        QTextStream out(&file);
        doc.save(out, QDomNode::EncodingFromDocument);
        file.close();
    }
}

void MyDom::readXML()
{
    QDomDocument doc("blogs");
    QFile file("Blogs.xml");
    if(!file.open(QFile::ReadOnly))
        return;
    if(!doc.setContent(&file))
    {
        file.close();
        return;
    }
    file.close();

    /*************************** 根元素<Blogs> ***************************/
    QDomElement rootElem = doc.documentElement();
    qDebug() << rootElem.tagName();
    if(rootElem.hasAttribute("Version"))
        qDebug() << rootElem.attribute("Version");

    /*************************** 根元素之上（声明、注释等） ***************************/
    QDomNode node = rootElem.previousSibling();
    while(!node.isNull())
    {
        switch (node.nodeType())
        {
        case QDomNode::CommentNode:
            {
                QDomComment comment = node.toComment();
                qDebug() << comment.data();
            }
            break;
        case QDomNode::ProcessingInstructionNode:
            {
                QDomProcessingInstruction instruction = node.toProcessingInstruction();
                qDebug() << instruction.data();

                if(instruction.target().compare("xml") == 0)
                {
                    // ...
                    qDebug() << "xml";
                }
                else if(instruction.target().compare("xml-stylesheet") == 0)
                {
                    // ...
                    qDebug() << "xml-stylesheet";
                }
            }
            break;
        default:
            break;
        }
        node = node.previousSibling();
    }

    /*************************** 元素<Blog> ***************************/
    node = rootElem.firstChild();
    while (!node.isNull())
    {
        QDomElement elem = node.toElement();
        if(!elem.isNull() && elem.tagName().compare("Blog") == 0)
        {
            qDebug() << elem.tagName();

            /*************************** 遍历元素<作者><主页><个人说明> ***************************/
            QDomNodeList nodeList = elem.childNodes();
            for(int i = 0; i < nodeList.count(); ++i)
            {
                node = nodeList.at(i);
                elem = node.toElement();
                if(!elem.isNull())
                {
                    qDebug() << elem.tagName() << elem.text();
                    if(elem.tagName().compare(QString::fromUtf8(u8"作者")) == 0)
                    {
                        //  ...
                    }
                    else if(elem.tagName().compare(QString::fromUtf8(u8"主页")) == 0)
                    {
                        //  ...
                    }
                    else if(elem.tagName().compare(QString::fromUtf8(u8"个人说明")) == 0)
                    {
                        //  ...
                    }
                }
            }
        }
        node = node.nextSibling();
    }
}
