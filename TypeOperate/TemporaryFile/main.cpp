#include <QCoreApplication>
#include <qtemporaryfile.h>
#include <qdir.h>
#include <qdebug.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //  设置模板名称
    QString strFileName = QDir::tempPath() + QDir::separator() + qApp->applicationName() + "_XXXXXX." + "ini";
    QTemporaryFile tmpFile(strFileName);

    //  设置不自动删除，只为做验证，可手动删除
    tmpFile.setAutoRemove(false);

    qDebug() << "tmpPath: " << QDir::tempPath();

    if(tmpFile.open())
    {
        tmpFile.close();

        qDebug() << "fileTemplate: " << tmpFile.fileTemplate();
        qDebug() << "fileName: " << tmpFile.fileName();
    }
    else
    {
        qCritical() << "failed to write temporary file.";
    }

    return a.exec();
}
