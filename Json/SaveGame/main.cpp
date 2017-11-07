#include <QCoreApplication>

#include "Game.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Game game;
    game.newGame();

    // 游戏开始，加载数据...

    // 假设玩家度过了快乐的时光，取得了伟大的成就，改变 Character、Level 和 Game 对象的内部状态。
    if (!game.saveGame(Game::Json))
        return 1;

    if (!game.saveGame(Game::Binary))
        return 1;

    Game fromJsonGame;
    if (!fromJsonGame.loadGame(Game::Json))
        return 1;

    Game fromBinaryGame;
    if (!fromBinaryGame.loadGame(Game::Binary))
        return 1;

    return a.exec();
}
