#ifndef MYDOM_H
#define MYDOM_H

#include <QtXml>

class MyDom
{
public:
    static void writeXML();
    static void readXML();

private:
    MyDom() = delete;
};

#endif // MYDOM_H
