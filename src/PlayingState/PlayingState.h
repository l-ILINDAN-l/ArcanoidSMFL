

#ifndef PLAYINGSTATE_H
#define PLAYINGSTATE_H

#include "../GameState/GameState.h"
#include "../MyContactListener/MyContactListener.h"
#include "../Bonus/Bonus.h"
#include <memory>
#include <vector>

class Paddle;
class Ball;
class Brick;

class PlayingState : public GameState {
public:
    PlayingState(Game& game);
    ~PlayingState() override;
    void handleEvent(const sf::Event& event) override;
    void update(sf::Time dt) override;
    void draw() override;

    void handleBallBrickCollision(Ball* ball, Brick* brick);
    void handleBallPaddleCollision(Ball* ball, Paddle* paddle);
    void handlePaddleBonusCollision(Paddle* paddle, Bonus* bonus);

    void addScore(int points);
    tgui::Gui& getGui() { return mGui; }
    sf::RenderWindow& getWindow() { return mWindow; }
    sf::Texture& getAtlas() { return mTextureAtlas; }

    static constexpr float SCALE = 30.0f;

private:
    void initPhysics();
    void loadLevel(const std::string& levelPath);
    void createEntities();
    void updateUI();
    void checkGameStatus();
    void cleanupDeadObjects();
    void applyBonus(Bonus::BonusType type);
    void resetRound();

    tgui::Gui& mGui;
    sf::RenderWindow& mWindow;
    b2World mWorld;
    std::unique_ptr<MyContactListener> mContactListener;

    sf::Texture mTextureAtlas;
    sf::Sprite mBackgroundSprite;
    sf::Texture mBackgroundTexture;

    std::unique_ptr<Paddle> mPaddle;
    std::unique_ptr<Ball> mBall;
    std::vector<std::unique_ptr<Brick>> mBricks;
    std::vector<std::unique_ptr<Bonus>> mBonuses;

    int mScore = 0;
    int mLives = 3;
    unsigned int mBricksRemaining = 0;
    bool mIsGameOver = false;

    tgui::Label::Ptr mScoreLabel, mLivesLabel, mInfoLabel;
};



#endif //PLAYINGSTATE_H
