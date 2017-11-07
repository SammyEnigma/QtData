#include <QCoreApplication>
#include <stdio.h>
#include <stdlib.h>
#include <qdatetime.h>
#include <qfile.h>
#include <qdir.h>
#include <mutex>

//  自定义消息处理程序
void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QByteArray localMsg = msg.toLocal8Bit();
    switch (type)
    {
    case QtDebugMsg:
        fprintf(stderr, "Debug: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtInfoMsg:
        fprintf(stderr, "Info: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtWarningMsg:
        fprintf(stderr, "Warning: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtCriticalMsg:
        fprintf(stderr, "Critical: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtFatalMsg:
        fprintf(stderr, "Fatal: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        abort();
    }
}

//  自定义消息重定向至文件
void myMessageOutputLog(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    //  设置输出信息格式
    QString strDateTime = QDateTime::currentDateTime().toString("HH:mm:s.zzz");
    QString strMsg("");

    QByteArray localMsg = msg.toLocal8Bit();
    switch (type)
    {
    case QtDebugMsg:
        strMsg = QString::fromUtf8("[%1] [Debug] %2 (%3:%4, %5)\r\n").arg(strDateTime).arg(localMsg.constData()).arg(context.file).arg(context.line).arg(context.function);
        break;
    case QtInfoMsg:
        strMsg = QString::fromUtf8("[%1] [Info] %2 (%3:%4, %5)\r\n").arg(strDateTime).arg(localMsg.constData()).arg(context.file).arg(context.line).arg(context.function);
        break;
    case QtWarningMsg:
        strMsg = QString::fromUtf8("[%1] [Warning] %2 (%3:%4, %5)\r\n").arg(strDateTime).arg(localMsg.constData()).arg(context.file).arg(context.line).arg(context.function);
        break;
    case QtCriticalMsg:
        strMsg = QString::fromUtf8("[%1] [Critical] %2 (%3:%4, %5)\r\n").arg(strDateTime).arg(localMsg.constData()).arg(context.file).arg(context.line).arg(context.function);
        break;
    case QtFatalMsg:
        strMsg = QString::fromUtf8("[%1] [Fatal] %2 (%3:%4, %5)\r\n").arg(strDateTime).arg(localMsg.constData()).arg(context.file).arg(context.line).arg(context.function);
        abort();
    }

    //  输出信息至文件中（读写、追加形式）
    QString strLogFilePath(QString::fromUtf8("%1\\log").arg(qApp->applicationDirPath()));
    QDir dir;
    dir.mkpath(strLogFilePath);
    strLogFilePath = QString::fromUtf8("%1\\Log_%2%3%4.log").arg(strLogFilePath).arg(QDateTime::currentDateTime().date().year()).arg(QDateTime::currentDateTime().date().month()).arg(QDateTime::currentDateTime().date().day());

    //  多线程安全
    static std::mutex mtx;
    std::lock_guard<std::mutex> lck(mtx);

    QFile file(strLogFilePath);
    file.open(QIODevice::ReadWrite | QIODevice::Append);
    file.write(strMsg.toUtf8());
    file.close();
}

int main(int argc, char *argv[])
{
    qInstallMessageHandler(myMessageOutputLog);
    QCoreApplication a(argc, argv);

    // 打印信息
    qInfo(u8"提示消息");
//    qDebug("This is a debug message.");
//    qWarning("This is a warning message.");
//    qCritical("This is a critical message.");
    //qFatal("This is a fatal message.");

    return a.exec();
}
