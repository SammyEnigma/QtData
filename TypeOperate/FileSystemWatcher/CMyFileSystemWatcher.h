#ifndef CMYFILESYSTEMWATCHER_H
#define CMYFILESYSTEMWATCHER_H

#include <QObject>
#include <QFileSystemWatcher>
#include <QMap>

class CMyFileSystemWatcher : public QObject
{
    Q_OBJECT
public:
    static void addWatchPath(const QString& path);

signals:

public slots:
    void onFileChanged(const QString& path);    //  文件被修改时调用，path是监控的路径
    void onDirectoryChanged(const QString& path);   //  目录更新时调用，path是监控的路径

private:
    explicit CMyFileSystemWatcher(QObject *parent = nullptr);

private:
    static CMyFileSystemWatcher* m_pInstance;   //  单例
    QFileSystemWatcher* m_pSystemWatcher;   //  QFileSystemWatcher变量
    QMap<QString, QStringList> m_currentContentsMap;    //  当前每个监控的内容目录列表
};

#endif // CMYFILESYSTEMWATCHER_H
