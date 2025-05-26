#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

class Game;

class GameState {
public:
    virtual ~GameState() = default;
    virtual void handleEvent(const sf::Event& event) = 0;
    virtual void update(sf::Time dt) = 0;
    virtual void draw() = 0;
protected:
    GameState(Game& game) : mGame(game) {}
    Game& mGame;
};



#endif //GAMESTATE_H
