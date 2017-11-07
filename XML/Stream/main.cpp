#include <QCoreApplication>
#include "CustomXmlStream.h"
#include <qfile.h>
#include <qdebug.h>

int main(int argc, char *argv[])
{
    //CustomXmlStream stream;
    //stream.writeXml();
    //stream.readXml();

    QFile file("CustomBlogs.xml");
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug() << QString(u8"Cannot read file CustomBlogs.xml(%1).").arg(file.errorString());
        return -1;
    }
    XmlReader reader;
    if(!reader.read(&file))
    {
        qDebug() << QString("Parse error in file CustomBlogs.xml(%1).").arg(reader.errorString());
    }
}
