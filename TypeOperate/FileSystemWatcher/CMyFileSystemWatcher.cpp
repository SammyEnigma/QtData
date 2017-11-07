#include "CMyFileSystemWatcher.h"
#include <QFileInfo>
#include <QDir>
#include <QSet>
#include <QDebug>

CMyFileSystemWatcher* CMyFileSystemWatcher::m_pInstance = nullptr;

void CMyFileSystemWatcher::addWatchPath(const QString &path)
{
    qDebug() << QString("Add to watch: %1").arg(path);

    if(m_pInstance == nullptr)
    {
        m_pInstance = new CMyFileSystemWatcher;
        m_pInstance->m_pSystemWatcher = new QFileSystemWatcher;

        connect(m_pInstance->m_pSystemWatcher, SIGNAL(fileChanged(QString)), m_pInstance, SLOT(onFileChanged(QString)));
        connect(m_pInstance->m_pSystemWatcher, SIGNAL(directoryChanged(QString)), m_pInstance, SLOT(onDirectoryChanged(QString)));
    }

    //  添加监控路径
    m_pInstance->m_pSystemWatcher->addPath(path);

    //  如果添加的是一个目录，保存当前内容列表
    QFileInfo file(path);
    if(file.isDir())
    {
        const QDir dir(path);
        m_pInstance->m_currentContentsMap[path] = dir.entryList(QDir::NoDotAndDotDot | QDir::AllDirs | QDir::Files, QDir::DirsFirst);
    }
}

void CMyFileSystemWatcher::onFileChanged(const QString &path)
{
    QFileInfo fileInfo(path);
    const QString& strPath = fileInfo.absoluteFilePath();
    const QString& strName = fileInfo.fileName();

    qDebug() << QString("The file %1 at path %2 is updated.").arg(strName).arg(strPath);
}

void CMyFileSystemWatcher::onDirectoryChanged(const QString &path)
{
    qDebug() << QString("Directory updated: %1").arg(path);

    //  比较最新的内容和保存的内容找出区别
    const QDir dir(path);
    QStringList newEntryList = dir.entryList(QDir::NoDotAndDotDot | QDir::AllDirs | QDir::Files, QDir::DirsFirst);
    QStringList curEntryList = m_currentContentsMap[path];
    QSet<QString> newDirSet = QSet<QString>::fromList(newEntryList);
    QSet<QString> curDirSet = QSet<QString>::fromList(curEntryList);

    //  更新当前设置
    m_currentContentsMap[path] = newEntryList;

    //  添加了文件
    QSet<QString> newFiles = newDirSet - curDirSet;
    QStringList newFileList = newFiles.toList();

    //  文件已被移除
    QSet<QString> deleteFiles = curDirSet - newDirSet;
    QStringList deleteFileList = deleteFiles.toList();

    if(!newFileList.isEmpty() && !deleteFileList.isEmpty())
    {
        //  文件/目录重命名
        if(newFileList.count() == 1 && deleteFileList.count() == 1)
        {
            qDebug() << QString("File Renamed from %1 to %2").arg(deleteFileList.first()).arg(newFileList.first());
        }
    }
    else
    {
        //  添加新文件/目录至Dir
        if(!newFileList.isEmpty())
        {
            qDebug() << "New Files/Dirs added: " << newFileList;

            foreach (QString file, newFileList)
            {
                //  处理操作每个新文件...
            }
        }

        //  从Dir中删除文件/目录
        if(!deleteFileList.isEmpty())
        {
            qDebug() << "Files/Dirs deleted: " << deleteFileList;

            foreach (QString file, deleteFileList)
            {
                //  处理操作每个被删除的文件...
            }
        }
    }
}

CMyFileSystemWatcher::CMyFileSystemWatcher(QObject *parent) : QObject(parent)
{

}
