#include <QCoreApplication>
#include "MyDom.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    //MyDom::writeXML();
    MyDom::readXML();

    return a.exec();
}
