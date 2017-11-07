#ifndef SIMPLEJSON_H
#define SIMPLEJSON_H

#include <QtCore>

class SimpleJson
{
public:
    SimpleJson();

    void toJson();
    void parseJson();

private:
    QByteArray m_byteArray;
};

#endif // SIMPLEJSON_H
