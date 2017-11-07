#ifndef GAME_H
#define GAME_H

#include "Level.h"

class Game
{
public:
    Game();

    enum SaveFormat
    {
        Json, Binary
    };

    const Character& player() const
    { return m_player; }
    const QList<Level>& levels() const
    { return m_levels; }

    void newGame();
    bool loadGame(SaveFormat saveFormat);
    bool saveGame(SaveFormat saveFormat) const;

    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;

private:
    Character m_player;
    QList<Level> m_levels;
};

#endif // GAME_H
