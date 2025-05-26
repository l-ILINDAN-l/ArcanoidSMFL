#pragma once
#include "../GameState/GameState.h"

class MainMenuState : public GameState {
public:
    MainMenuState(Game& game);
    ~MainMenuState() override;
    void handleEvent(const sf::Event& event) override;
    void update(sf::Time dt) override;
    void draw() override;
private:
    tgui::Gui& mGui;
    tgui::Picture::Ptr mBackground, mLogo;
    tgui::Button::Ptr mStartButton, mQuitButton;
};