#ifndef CHARACTER_H
#define CHARACTER_H

#include <QtCore>

//The Character class represents a non-player character (NPC) in our game, and stores the player's name, level, and class type.
//It provides read() and write() functions to serialise its member variables.
class Character
{
public:
    enum ClassType
    {
        Warrior = 01,
        Mage    = 02,
        Archer  = 04
    };

    Character();
    Character(const QString& name, int level, ClassType classType)
        : m_strName(name),
          m_nLevel(level),
          m_classType(classType)
    {}

    const QString& name() const
    { return m_strName; }
    void setNmae(const QString& name)
    { m_strName = name; }

    int level() const
    { return m_nLevel; }
    void setLevel(int level)
    { m_nLevel = level; }

    const ClassType& classType() const
    { return m_classType; }
    void setClassType(const ClassType& classType)
    { m_classType = classType; }

    void read(const QJsonObject& json);
    void write(QJsonObject& json) const;

private:
    QString m_strName;
    int m_nLevel;
    ClassType m_classType;
};

#endif // CHARACTER_H
