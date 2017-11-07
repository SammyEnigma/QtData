#include "SimpleJson.h"

SimpleJson::SimpleJson()
{
    m_byteArray.clear();
}


//{
//    "Company": "Digia",
//    "From": 1991,
//    "Name": "Qt",
//    "Page": {
//        "Developers": "https://www.qt.io/developers/",
//        "Download": "https://www.qt.io/download/",
//        "Home": "https://www.qt.io/"
//    },
//    "Version": [
//        4.8,
//        5.2,
//        5.7
//    ]
//}
void SimpleJson::toJson()
{
    QJsonObject json;
    json.insert("Company", "Digia");
    json.insert("From", 1991);
    json.insert("Name", "Qt");

    QJsonObject pageJson;
    pageJson.insert("Developers", "https://www.qt.io/developers/");
    pageJson.insert("Download", "https://www.qt.io/download/");
    pageJson.insert("Home", "https://www.qt.io/");
    json.insert("Page", pageJson);

    QJsonArray versionArray;
    versionArray.append(4.8);
    versionArray.append(5.2);
    versionArray.append(5.7);
    json.insert("Version", versionArray);

    QJsonDocument doc(json);
    m_byteArray = doc.toJson(QJsonDocument::Compact);
    qDebug() << QString(m_byteArray);
}

void SimpleJson::parseJson()
{
    Q_ASSERT(!m_byteArray.isEmpty());

    QJsonParseError jsonError;
    QJsonDocument doc = QJsonDocument::fromJson(m_byteArray, &jsonError);
    if(!doc.isNull() && jsonError.error == QJsonParseError::NoError)
    {
        if(doc.isObject())
        {
            QJsonObject json = doc.object();
            if(json.contains("Company"))
            {
                qDebug() << "Company: " << json.value("Company").toString();
            }
            if(json.contains("From"))
            {
                qDebug() << "From: " << json.value("From").toInt();
            }
            if(json.contains("Name"))
            {
                qDebug() << "Name: " << json.value("Name").toString();
            }
            if(json.contains("Page"))
            {
                QJsonValue value = json.value("Page");
                if(value.isObject())
                {
                    QJsonObject pageJson = value.toObject();
                    if(pageJson.contains("Developers"))
                    {
                        qDebug() << "Developers: " << pageJson.value("Developers").toString();
                    }
                    if(pageJson.contains("Download"))
                    {
                        qDebug() << "Download: " << pageJson.value("Download").toString();
                    }
                    if(pageJson.contains("Home"))
                    {
                        qDebug() << "Home: " << pageJson.value("Home").toString();
                    }
                }
            }
            if(json.contains("Version"))
            {
                QJsonValue value = json.value("Version");
                if(value.isArray())
                {
                    QJsonArray versionArray = value.toArray();
                    for(int i = 0; i < versionArray.size(); ++i)
                    {
                        qDebug() << "Version: " << versionArray.at(i).toDouble();
                    }
                }
            }
        }
        else
        {
            qDebug() << "This doc isnot an object.";
        }
    }
    else
    {
        qDebug() << jsonError.errorString();
    }
}
