#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // 改变缺省消息处理程序的输出
    qSetMessagePattern("%{time [yyyy-MM-dd hh:mm:ss ddd]} Message:%{message} File:%{file} Line:%{line} Function:%{function} ");

    // 打印信息
    qDebug("This is a debug message.");
    qInfo("This is a info message.");
    qWarning("This is a warning message.");
    qCritical("This is a critical message.");
    //qFatal("This is a fatal message.");

    return a.exec();
}
