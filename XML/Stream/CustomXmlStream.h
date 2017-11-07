#ifndef CUSTOMXMLSTREAM_H
#define CUSTOMXMLSTREAM_H

#include <qxmlstream.h>

class CustomXmlStream
{
public:
    CustomXmlStream();

    void writeXml();
    void readXml();

private:
    void parseBlog();

private:
    QXmlStreamReader streamReader;
    QXmlStreamWriter streamWriter;
};

//之前使用的方式主要使用 readNext() 来读取下一个标记，并返回对应的类型。
//这对于读取注释、字符、DTD、结束标签等类型比较方便。当只关心 XML 元素的解析，这时，此种方式就显得比较复杂了，下面介绍一种简单方式。
class XmlReader
{
public:
    XmlReader() {}

    bool read(QIODevice* device);
    QString errorString() const;

private:
    void readXBEL();    //  读取根元素<Blogs>
    void readBlog();    //  读取元素<Blog>
    void readAuthor();  //  读取元素<author>
    void readHome();    //  读取元素<home>
    void readIntroduction();    //  读取元素<introduction>

private:
    QXmlStreamReader reader;
};

#endif // CUSTOMXMLSTREAM_H
