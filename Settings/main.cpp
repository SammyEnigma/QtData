#include <QCoreApplication>
#include <qsettings.h>
#include <qdebug.h>

const QString HKEY_CURRENT_USER_QT = "HKEY_CURRENT_USER\\SOFTWARE\\Digia\\Qt";
const QString INI_QT = "C:\Users\YWJ\AppData\Roaming\Digia";

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    /*************************** 读写注册表 ***************************/
    /*************************** 一般存储 ***************************/
    a.setOrganizationName("Digia");
    a.setApplicationName("Qt");

    //    QSettings settings(QSettings::NativeFormat, QSettings::UserScope, a.organizationName(), a.applicationName());
    //    settings.setValue("Name", "Qt Creator");
    //    settings.setValue("Version", 5);

    /*************************** 一般读取 ***************************/
    //    QString strName = settings.value("Name").toString();
    //    int nVersion = settings.value("Version").toInt();
    //    qDebug() << "Name = " << strName << ", Version = " << nVersion;

    /*************************** 分目录存储 ***************************/
    //    如上，我们可以看出，organizationName对应的注册表路径为HKEY_CURRENT_USER\\SoftWare\\Digia
    //            applicationName对应的为其下一级的目录，那么分目录就需要更改其对应的applicationName
    //    QSettings settings2(QSettings::NativeFormat, QSettings::UserScope, QString("%1\\%2").arg(a.organizationName()).arg(a.applicationName()), "Qt5.5");
    //    settings2.setValue("Name", "Qt Creator");
    //    settings2.setValue("Version", "5.5");
    //    QSettings settings3(QSettings::NativeFormat, QSettings::UserScope, QString("%1\\%2").arg(a.organizationName()).arg(a.applicationName()), "Qt5.6");
    //    settings3.setValue("Name", "Qt Creator");
    //    settings3.setValue("Version", "5.6");

    //    替换applicationName的方式看起来有些繁琐，相比之下，使用group分组则会更简单！
    //    QSettings settings;
    //    settings.beginGroup("Qt5.5");
    //    settings.setValue("Name", "Qt Creator");
    //    settings.setValue("Version", "5.5");
    //    settings.endGroup();

    //    settings.beginGroup("Qt5.6");
    //    settings.setValue("Name", "Qt Creator");
    //    settings.setValue("Version", "5.6");
    //    settings.endGroup();



    /*************************** 读写配置文件 ***************************/
    /*************************** 一般存储 ***************************/
    QSettings settings(QSettings::IniFormat, QSettings::UserScope, a.organizationName(), a.applicationName());
    //    settings.setValue("Name", "Qt Creator");
    //    settings.setValue("Version", 5);

    /*************************** 分组存储 ***************************/
    settings.beginGroup("Setting");
    settings.setValue("Name", "Qt Creator");
    settings.setValue("Version", 5);
    settings.endGroup();

    settings.beginGroup("User");
    settings.setValue("UserName", "wangds");
    settings.setValue("Password", "123456");
    settings.endGroup();

    return a.exec();
}
