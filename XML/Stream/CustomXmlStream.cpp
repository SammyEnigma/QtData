#include "CustomXmlStream.h"
#include <qfile.h>
#include <qdebug.h>

CustomXmlStream::CustomXmlStream()
{

}

/*************************** Example ***************************/
//<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
//<!--源于开源，回馈开源-->
//<?xml-stylesheet type="text/css" href="style.css"?>
//<!DOCTYPE Blogs [ <!ENTITY Copyright "Copyright 2017《Play With Qt》"> <!ELEMENT Blogs (Blog)> <!ELEMENT Blog (author,home,introduction)> <!ELEMENT author     (#PCDATA)> <!ELEMENT home     (#PCDATA)> <!ELEMENT introduction  (#PCDATA)> ]>
//<Blogs Version="1.0">
//    <Blog>
//        <author>wangds</author>
//        <home>https://github.com/andywong569</home>
//        <introduction>write less, do more</introduction>&Copyright;<![CDATA[<Qt分享&&交流>368241647</Qt分享&&交流>]]>&gt;<Empty/>
//    </Blog>
//</Blogs>

void CustomXmlStream::writeXml()
{
    QFile file("CustomBlogs.xml");
    if(!file.open(QFile::WriteOnly | QFile::Text))  //  只写模式打开文件
    {
        qDebug() << QString("Cannot write file CustomBlogs.xml(%1)").arg(file.errorString());
        return;
    }

    streamWriter.setDevice(&file);
    streamWriter.setAutoFormatting(true);   //  自动格式化
    streamWriter.writeStartDocument("1.0", true);   //  start doc
    streamWriter.writeComment(u8"源于开源，回馈开源");
    streamWriter.writeProcessingInstruction("xml-stylesheet type=\"text/css\" href=\"style.css\"");
    streamWriter.writeDTD("<!DOCTYPE Blogs [ <!ENTITY Copyright \"Copyright 2017《Play With Qt》\"> <!ELEMENT Blogs (Blog)> <!ELEMENT Blog (author,home,introduction)> <!ELEMENT author     (#PCDATA)> <!ELEMENT home     (#PCDATA)> <!ELEMENT introduction  (#PCDATA)> ]>");

    /*************************** Blogs ***************************/
    streamWriter.writeStartElement("Blogs");    //  start root
    streamWriter.writeAttribute("Version", "1.0");

    streamWriter.writeStartElement("Blog"); //  start child
    streamWriter.writeTextElement("author", "wangds");
    streamWriter.writeTextElement("home", "https://github.com/andywong569");
    streamWriter.writeTextElement("introduction", "write less, do more");
    streamWriter.writeEntityReference("Copyright");
    streamWriter.writeCDATA(u8"<Qt分享&&交流>368241647</Qt分享&&交流>");
    streamWriter.writeCharacters(">");
    streamWriter.writeEmptyElement("Empty");
    streamWriter.writeEndElement(); //  end child

    streamWriter.writeEndElement(); //  end root
    streamWriter.writeEndDocument();    //  end doc

    file.close();
}

void CustomXmlStream::readXml()
{
    QFile file("CustomBlogs.xml");
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug() << QString("Cannot read file CustomBlogs.xml(%1)").arg(file.errorString());
        return;
    }

    streamReader.setDevice(&file);
    while (!streamReader.atEnd())
    {
        switch (streamReader.readNext())
        {
        case QXmlStreamReader::StartDocument:
            {
                qDebug() << u8"**********开始文档**********";
                qDebug() << QString(u8"版本：%1    编码：%2   Standalone：%3")
                            .arg(streamReader.documentVersion().toString())
                            .arg(streamReader.documentEncoding().toString())
                            .arg(streamReader.isStandaloneDocument()) << "\r\n";
            }
            break;
        case QXmlStreamReader::StartElement:
            {
                if(streamReader.name().toString().compare("Blogs") == 0)
                {
                    qDebug() << u8"********** 开始元素<Blogs> ********** ";
                    if(streamReader.attributes().hasAttribute("Version"))
                        qDebug() << u8"属性：Version(" << streamReader.attributes().value("Version").toString() << u8")";
                    parseBlog();
                }
            }
            break;
        case QXmlStreamReader::EndDocument:
            {
                qDebug() << u8"**********结束文档**********";
            }
            break;
        default:
            break;
        }
    }
    if(streamReader.hasError())
    {
        qDebug() << QString(u8"错误信息：%1  行号：%2   列号：%3   字符位移：%4")
                    .arg(streamReader.errorString())
                    .arg(streamReader.lineNumber())
                    .arg(streamReader.columnNumber())
                    .arg(streamReader.characterOffset());
    }

    file.close();
}

void CustomXmlStream::parseBlog()
{
    while (!streamReader.atEnd())
    {
        streamReader.readNext();
        if(streamReader.isStartElement())   // 开始元素
        {
            if(streamReader.name().toString().compare("Blog") == 0)
            {
                qDebug() << u8"********** 开始元素<Blog> ********** ";
            }
            else if(streamReader.name().toString().compare("author") == 0)  //  方式一
            {
                streamReader.readNext();
                if(streamReader.isCharacters())
                    qDebug() << QString(u8"作者：%1").arg(streamReader.text().toString());
            }
            else if(streamReader.name().toString().compare("home") == 0)    //  方式二
            {
                qDebug() << QString(u8"主页：%1").arg(streamReader.readElementText());
            }
            else if(streamReader.name().toString().compare("introduction") == 0)
            {

            }
        }
        else if(streamReader.isEntityReference())   // 实体引用
        {
            qDebug() << QString("EntityReference : %1(%2)").arg(streamReader.name().toString()).arg(streamReader.text().toString());
        }
        else if(streamReader.isCDATA())     // CDATA
        {
            qDebug() << QString("CDATA : %1").arg(streamReader.text().toString());

            streamReader.readNext();
            if (streamReader.isCharacters())
            {
                qDebug() << QString("Characters : %1").arg(streamReader.text().toString());
            }
        }
        else if(streamReader.isEndElement())    // 结束元素
        {
            if(streamReader.name().toString().compare("Blogs") == 0)
            {
                qDebug() << u8"********** 结束元素<Blogs> ********** ";
                break;  // 跳出循环（解析 QXmlStreamReader::EndDocument）
            }
            else if(streamReader.name().toString().compare("Blog") == 0)
            {
                qDebug() << u8"********** 结束元素<Blog> ********** ";
            }
        }
    }
}

static const QString ROOT_ELEMENT = u8"Blogs";
static const QString BLOG_ELEMENT = u8"Blog";
static const QString AUTHOR_ELEMENT = u8"author";
static const QString HOME_ELEMENT = u8"home";
static const QString INTRODUCTION_ELEMENT = u8"introduction";
static const QString VERSION_ELEMENT = u8"Version";

bool XmlReader::read(QIODevice *device)
{
    reader.setDevice(device);
    if(reader.readNextStartElement())
    {
        if(reader.name().toString().compare(ROOT_ELEMENT) == 0) //  根元素
        {
            if(reader.attributes().value(VERSION_ELEMENT).toString().compare("1.0") == 0)
            {
                readXBEL();
            }
            else
            {
                reader.raiseError("The file is not an XBEL version 1.0 file.");
            }
        }
        else
        {
            reader.raiseError("Xml file format error.");
        }
    }

    return !reader.error();
}

QString XmlReader::errorString() const
{
    return QString("Error:%1  Line:%2  Column:%3")
                .arg(reader.errorString())
                .arg(reader.lineNumber())
                .arg(reader.columnNumber());
}

void XmlReader::readXBEL()
{
    Q_ASSERT(reader.isStartElement() && reader.name().toString() == ROOT_ELEMENT);

    while (reader.readNextStartElement())
    {
        if(reader.name().toString().compare(BLOG_ELEMENT) == 0)
        {
            readBlog();
        }
        else
        {
            reader.skipCurrentElement();    //  跳过当前元素
        }
    }
}

void XmlReader::readBlog()
{
    Q_ASSERT(reader.isStartElement() && reader.name().toString() == BLOG_ELEMENT);

    while (reader.readNextStartElement())
    {
        if(reader.name().toString().compare(AUTHOR_ELEMENT) == 0)
        {
            readAuthor();
        }
        else if(reader.name().toString().compare(HOME_ELEMENT) == 0)
        {
            readHome();
        }
        else if(reader.name().toString().compare(INTRODUCTION_ELEMENT) == 0)
        {
            readIntroduction();
        }
        else
        {
            reader.skipCurrentElement();    //  跳过当前元素
        }
    }
}

void XmlReader::readAuthor()
{
    Q_ASSERT(reader.isStartElement() && reader.name().toString() == AUTHOR_ELEMENT);

    qDebug() << u8"作者：" << reader.readElementText();
}

void XmlReader::readHome()
{
    Q_ASSERT(reader.isStartElement() && reader.name().toString() == HOME_ELEMENT);

    qDebug() << u8"主页：" << reader.readElementText();
}

void XmlReader::readIntroduction()
{
    Q_ASSERT(reader.isStartElement() && reader.name().toString() == INTRODUCTION_ELEMENT);

    qDebug() << u8"个人说明：" << reader.readElementText();
}
