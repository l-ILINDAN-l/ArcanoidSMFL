#include "MainMenuState.h"
#include "../Game/Game.h"
#include "../PlayingState/PlayingState.h"
#include <iostream>

MainMenuState::MainMenuState(Game& game) : GameState(game), mGui(game.getGui()) {
    mBackground = tgui::Picture::create("texture/background.png");
    mGui.add(mBackground);

    mLogo = tgui::Picture::create("texture/Arcanoid-logo.png");
    mLogo->setPosition("(parent.width - width) / 2", "10%");
    mGui.add(mLogo);

    mStartButton = tgui::Button::create();
    mStartButton->getRenderer()->setTexture("texture/ButtonStartND.png");
    mStartButton->getRenderer()->setTextureHover("texture/ButtonStartD.png");
    mStartButton->setSize(430, 200);
    mStartButton->setPosition("(parent.width - width) / 2", "45%");
    mStartButton->onPress(&Game::changeState<PlayingState>, &mGame);
    mGui.add(mStartButton);

    mQuitButton = tgui::Button::create();
    mQuitButton->getRenderer()->setTexture("texture/QuitButtonND.png");
    mQuitButton->getRenderer()->setTextureHover("texture/QuitButtonD.png");
    mQuitButton->setSize(400, 168);
    mQuitButton->setPosition("(parent.width - width) / 2", "70%");
    mQuitButton->onPress(&Game::quit, &mGame);
    mGui.add(mQuitButton);
}

MainMenuState::~MainMenuState() {
    mGui.remove(mBackground);
    mGui.remove(mLogo);
    mGui.remove(mStartButton);
    mGui.remove(mQuitButton);
}
void MainMenuState::handleEvent(const sf::Event& event) { mGui.handleEvent(event); }
void MainMenuState::update(sf::Time dt) {}
void MainMenuState::draw() { mGui.draw(); }