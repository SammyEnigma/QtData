#ifndef LEVEL_H
#define LEVEL_H

#include "Character.h"

class Level
{
public:
    Level();

    const QList<Character>& npcs() const
    { return m_npcs; }
    void setNpcs(const QList<Character>& npcs)
    { m_npcs = npcs; }

    void read(const QJsonObject& json);
    void write(QJsonObject& json) const;

private:
    QList<Character> m_npcs;
};

#endif // LEVEL_H
