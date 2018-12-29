#include "game.h"


Game::Game(QObject *parent, std::unique_ptr<Player> &&player1, std::unique_ptr<Player> &&player2, qint32 gameId)
    : QObject(parent),
      m_player1(std::move(player1)),
      m_player2(std::move(player2)),
      m_gameId(gameId)
{}


Game::Game(Game &&other)
    : m_player1(std::move(other.m_player1)),
      m_player2(std::move(other.m_player2)),
      m_gameId(other.m_gameId),
      m_player1ShipsLeft(other.m_player1ShipsLeft),
      m_player2ShipsLeft(other.m_player2ShipsLeft)
{}
