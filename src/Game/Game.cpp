#include "Game.h"
#include "../MainMenuState/MainMenuState.h"

Game::Game() : mWindow(sf::VideoMode(1600, 900), "Arcanoid") {
    mWindow.setFramerateLimit(60);
    mGui.setTarget(mWindow);
    mCurrentState = std::make_unique<MainMenuState>(*this);
}

void Game::run() {
    sf::Clock clock;
    while (mWindow.isOpen()) {
        sf::Time dt = clock.restart();
        handleEvents();
        update(dt);
        render();
    }
}

void Game::handleEvents() {
    sf::Event event;
    while (mWindow.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            quit();
        }
        mCurrentState->handleEvent(event);
    }
}

void Game::update(sf::Time dt) {
    mCurrentState->update(dt);
}

void Game::render() {
    mWindow.clear();
    mCurrentState->draw();
    mWindow.display();
}

void Game::quit() { mWindow.close(); }
sf::RenderWindow& Game::getWindow() { return mWindow; }
tgui::Gui& Game::getGui() { return mGui; }
