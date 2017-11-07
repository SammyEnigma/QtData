#include "Level.h"

Level::Level()
{
    m_npcs.clear();
}

void Level::read(const QJsonObject &json)
{
    m_npcs.clear();
    QJsonArray npcArray = json["npcs"].toArray();
    for(int i = 0; i < npcArray.size(); ++i)
    {
        QJsonObject npcObject = npcArray[i].toObject();
        Character npc;
        npc.read(npcObject);
        m_npcs.append(npc);
    }
}

void Level::write(QJsonObject &json) const
{
    QJsonArray npcArray;
    for(const auto& npc : m_npcs)
    {
        QJsonObject npcObject;
        npc.write(npcObject);
        npcArray.append(npcObject);
    }
    json["npcs"] = npcArray;
}
