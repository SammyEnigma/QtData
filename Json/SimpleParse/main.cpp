#include <QCoreApplication>
#include <SimpleJson.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    SimpleJson simpleJson;
    simpleJson.toJson();
    simpleJson.parseJson();

    return a.exec();
}
