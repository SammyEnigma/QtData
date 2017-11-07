#include <QCoreApplication>
#include "CMyFileSystemWatcher.h"

//QFileSystemWatcher类用于提供监视文件和目录修改的接口。
//QFileSystemWatcher通过监控指定路径的列表，监视文件系统中文件和目录的变更。
//调用addPath()函数可以监控一个特定的文件或目录。如果需要监控多个路径，可以使用addPaths()。
//通过使用removePath()和removePaths()函数来移除现有路径。
//QFileSystemWatcher检查添加到它的每个路径，已添加到QFileSystemWatcher的文件可以使用的files()函数进行访问，
//目录则使用directories()函数进行访问。
//当一个文件被修改、重命名或从磁盘上删除时，会发出fileChanged()信号。
//同样，当一个目录或它的内容被修改或​​删除时，会发射directoryChanged()信号。
//需要注意：文件一旦被重命名或从硬盘删除，目录一旦从磁盘上删除，QFileSystemWatcher将停止监控。
//注：监控文件和目录进行修改的行为会消耗系统资源。这意味着，你的进程同时监控会有文件数量的限制。
//一些系统限制打开的文件描述符的数量默认为256。也就是说，如果你的进程试使用addPath()和addPaths()函数添加超过256个文件或目录到文件系统将会失败。

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    CMyFileSystemWatcher::addWatchPath(argv[1]);

    return a.exec();
}
