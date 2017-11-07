#include "Character.h"

Character::Character()
    : Character("", 0, Warrior)
{

}

void Character::read(const QJsonObject &json)
{
    m_strName = json["name"].toString();
    m_nLevel = json["level"].toInt();
    m_classType = static_cast<ClassType>(qRound(json["classType"].toDouble()));
}

void Character::write(QJsonObject &json) const
{
    json["name"] = m_strName;
    json["level"] = m_nLevel;
    json["classType"] = m_classType;
}
