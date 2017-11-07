#include "Game.h"

Game::Game()
{

}

void Game::newGame()
{
    m_player = Character("Hero", 15, Character::Archer);

    m_levels.clear();

    Level village;
    QList<Character> villageNpcs;
    villageNpcs.append(Character(QStringLiteral("Barry the Blacksmith"), 10, Character::Warrior));
    villageNpcs.append(Character(QStringLiteral("Terry the Trader"), 10, Character::Warrior));
    village.setNpcs(villageNpcs);
    m_levels.append(village);

    Level dungeon;
    QList<Character> dungeonNpcs;
    dungeonNpcs.append(Character(QStringLiteral("Eric the Evil"), 20, Character::Mage));
    dungeonNpcs.append(Character(QStringLiteral("Eric's Sidekick #1"), 5, Character::Warrior));
    dungeonNpcs.append(Character(QStringLiteral("Eric's Sidekick #2"), 5, Character::Warrior));
    dungeon.setNpcs(dungeonNpcs);
    m_levels.append(dungeon);
}

bool Game::loadGame(Game::SaveFormat saveFormat)
{
    QFile file(saveFormat == Json ? QStringLiteral("save.json") : QStringLiteral("save.dat"));
    if(!file.open(QFile::ReadOnly))
    {
        qWarning("Couldn't open save file.");
        return false;
    }

    QByteArray saveData = file.readAll();
    QJsonDocument doc(saveFormat == Json ? QJsonDocument::fromJson(saveData) : QJsonDocument::fromBinaryData(saveData));
    read(doc.object());
    file.close();

    return true;
}

bool Game::saveGame(Game::SaveFormat saveFormat) const
{
    QFile file(saveFormat == Json ? QStringLiteral("save.json") : QStringLiteral("save.dat"));
    if(!file.open(QFile::WriteOnly))
    {
        qWarning("Couldn't open save file.");
        return false;
    }

    QJsonObject gameObject;
    write(gameObject);
    QJsonDocument doc(gameObject);
    file.write(saveFormat == Json ? doc.toJson() : doc.toBinaryData());
    file.close();

    return true;
}

void Game::read(const QJsonObject &json)
{
    m_player.read(json["player"].toObject());

    m_levels.clear();
    QJsonArray levelArray = json["levels"].toArray();
    for(int i = 0; i < levelArray.size(); ++i)
    {
        QJsonObject levelObject = levelArray[i].toObject();
        Level level;
        level.read(levelObject);
        m_levels.append(level);
    }
}

void Game::write(QJsonObject &json) const
{
    QJsonObject playerObject;
    m_player.write(playerObject);
    json["player"] = playerObject;

    QJsonArray levelArray;
    for(const auto& item : m_levels)
    {
        QJsonObject levelObject;
        item.write(levelObject);
        levelArray.append(levelObject);
    }
    json["levels"] = levelArray;
}
