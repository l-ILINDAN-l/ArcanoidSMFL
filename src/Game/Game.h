//
// Created by gellertilya on 25.05.25.
//

#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <memory>
#include "../GameState/GameState.h"

class Game {
public:
    Game();
    void run();

    template<typename T>
    void changeState();

    void quit();

    sf::RenderWindow& getWindow();
    tgui::Gui& getGui();

private:
    void handleEvents();
    void update(sf::Time dt);
    void render();

    sf::RenderWindow mWindow;
    tgui::Gui mGui;
    std::unique_ptr<GameState> mCurrentState;
};

template<typename T>
void Game::changeState() {
    mCurrentState = std::make_unique<T>(*this);
}


#endif //GAME_H
