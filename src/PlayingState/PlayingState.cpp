#include "PlayingState.h"
#include "Game.h"
#include "nlohmann/json.hpp"
#include "Paddle.h"
#include "Ball.h"
#include "Brick.h"
#include <fstream>
#include <iostream>

PlayingState::PlayingState(Game& game)
    : GameState(game), mGui(game.getGui()), mWindow(game.getWindow()), mWorld(b2Vec2(0.0f, 0.0f)) {

    mContactListener = std::make_unique<MyContactListener>(this);
    mWorld.SetContactListener(mContactListener.get());

    mTextureAtlas.loadFromFile("texture/textures.png");
    mBackgroundTexture.loadFromFile("texture/Fields/field1.png");
    mBackgroundSprite.setTexture(mBackgroundTexture);

    initPhysics();
    createEntities();
    loadLevel("levels/level1.json");

    mScoreLabel = tgui::Label::create();
    mScoreLabel->setPosition(10, 10);
    mScoreLabel->setTextSize(24);
    mGui.add(mScoreLabel);

    mLivesLabel = tgui::Label::create();
    mLivesLabel->setPosition("parent.width - width - 10", 10);
    mLivesLabel->setTextSize(24);
    mGui.add(mLivesLabel);

    mInfoLabel = tgui::Label::create();
    mInfoLabel->setTextSize(64);
    mInfoLabel->setPosition("(parent.width - width) / 2", "40%");
    mGui.add(mInfoLabel);
    mInfoLabel->setVisible(false);

    updateUI();
}

PlayingState::~PlayingState() {
    mGui.remove(mScoreLabel);
    mGui.remove(mLivesLabel);
    mGui.remove(mInfoLabel);
}

void PlayingState::initPhysics() {
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(0.0f, 0.0f);
    b2Body* worldBounds = mWorld.CreateBody(&bodyDef);
    b2EdgeShape edge;
    float w = mWindow.getSize().x / SCALE;
    float h = mWindow.getSize().y / SCALE;
    edge.SetTwoSided(b2Vec2(0, 0), b2Vec2(w, 0));
    worldBounds->CreateFixture(&edge, 0.0f);
    edge.SetTwoSided(b2Vec2(0, 0), b2Vec2(0, h));
    worldBounds->CreateFixture(&edge, 0.0f);
    edge.SetTwoSided(b2Vec2(w, 0), b2Vec2(w, h));
    worldBounds->CreateFixture(&edge, 0.0f);
}

void PlayingState::createEntities() {
    sf::Vector2f paddlePos(mWindow.getSize().x / 2.0f, mWindow.getSize().y - 50.f);
    mPaddle = std::make_unique<Paddle>(mWorld, mTextureAtlas, paddlePos);
    sf::Vector2f ballPos(paddlePos.x, paddlePos.y - 35.f);
    mBall = std::make_unique<Ball>(mWorld, mTextureAtlas, ballPos);
    mBall->stickToPaddle(mPaddle->getBody());
}

void PlayingState::loadLevel(const std::string& levelPath) {
    std::ifstream f(levelPath);
    if (!f.is_open()) return;
    nlohmann::json data = nlohmann::json::parse(f);
    const auto& bricks_info = data["bricks"];
    const auto& layout = data["layout"];
    sf::Vector2f brickSize(50.f, 20.f), offset(mWindow.getSize().x/2.f - (layout[0].size()/2.f * (brickSize.x+2)), 50.f);

    for (size_t r = 0; r < layout.size(); ++r) {
        for (size_t c = 0; c < layout[r].size(); ++c) {
            int id = layout[r][c];
            if (id == 0) continue;
            const auto& info = bricks_info[std::to_string(id)];
            std::string type = info.value("type", "normal");
            int health = info.value("health", 1);
            auto rect_arr = info["texture_rect"];
            sf::IntRect rect(rect_arr[0], rect_arr[1], rect_arr[2], rect_arr[3]);
            Bonus::BonusType bonus = (info.value("bonus_type", "none") == "resize_up") ? Bonus::BonusType::PaddleResizeUp : Bonus::BonusType::None;
            sf::Vector2f pos(offset.x + c * (brickSize.x + 2), offset.y + r * (brickSize.y + 2));
            auto brick = std::make_unique<Brick>(mWorld, mTextureAtlas, rect, pos, health, type == "indestructible", bonus);
            if (type != "indestructible") mBricksRemaining++;
            mBricks.push_back(std::move(brick));
        }
    }
}

void PlayingState::handleEvent(const sf::Event& event) {
    if (mIsGameOver) {
        if (event.type == sf::Event::MouseButtonPressed) mGame.changeState<MainMenuState>();
        return;
    }
    if (event.type == sf::Event::MouseMoved) {
        mPaddle->getBody()->SetTransform(b2Vec2(static_cast<float>(event.mouseMove.x) / SCALE, mPaddle->getBody()->GetPosition().y), 0);
    }
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && mBall->isStuck()) {
        mBall->launch(b2Vec2(2.f, -10.f));
    }
}

void PlayingState::update(sf::Time dt) {
    if (mIsGameOver) return;
    mWorld.Step(dt.asSeconds(), 8, 3);
    mPaddle->update(dt);
    mBall->update(dt);
    for (auto& bonus : mBonuses) bonus->update(dt);
    cleanupDeadObjects();
    checkGameStatus();
}

void PlayingState::cleanupDeadObjects() {
    mBricks.erase(std::remove_if(mBricks.begin(), mBricks.end(), [](const auto& b){ return b->isDestroyed(); }), mBricks.end());
    mBonuses.erase(std::remove_if(mBonuses.begin(), mBonuses.end(),[](const auto& b){ return b->isCollected(); }), mBonuses.end());
}

void PlayingState::checkGameStatus() {
    if (mBall->getBody()->GetPosition().y * SCALE > mWindow.getSize().y + 50) {
        mLives--;
        updateUI();
        if (mLives <= 0) {
            mIsGameOver = true;
            mInfoLabel->setText("GAME OVER");
            mInfoLabel->setVisible(true);
        } else {
            resetRound();
        }
    }
    if (mBricksRemaining == 0) {
        mIsGameOver = true;
        mInfoLabel->setText("YOU WIN!");
        mInfoLabel->setVisible(true);
    }
}

void PlayingState::resetRound() {
    auto paddlePos = mPaddle->getBody()->GetPosition();
    mBall->reset({paddlePos.x * SCALE, paddlePos.y * SCALE - 35.f}, mPaddle->getBody());
}

void PlayingState::updateUI() {
    mScoreLabel->setText("Score: " + std::to_string(mScore));
    mLivesLabel->setText("Lives: " + std::to_string(mLives));
}

void PlayingState::draw() {
    mWindow.draw(mBackgroundSprite);
    for (const auto& brick : mBricks) mWindow.draw(*brick);
    for (const auto& bonus : mBonuses) mWindow.draw(*bonus);
    mWindow.draw(*mPaddle);
    mWindow.draw(*mBall);
    mGui.draw();
}

void PlayingState::addScore(int points) {
    mScore += points;
    updateUI();
}

void PlayingState::handleBallBrickCollision(Ball* ball, Brick* brick) {
    if (brick->isDestroyed()) return;
    brick->onHit();
    if (brick->isDestroyed()) {
        addScore(10);
        mBricksRemaining--;
        if (brick->getBonusTypeToDrop() != Bonus::BonusType::None) {
            auto pos = brick->getBody()->GetPosition();
            mBonuses.emplace_back(std::make_unique<Bonus>(mWorld, mTextureAtlas, sf::Vector2f(pos.x*SCALE, pos.y*SCALE), brick->getBonusTypeToDrop()));
        }
    } else addScore(1);
}

void PlayingState::handleBallPaddleCollision(Ball* ball, Paddle* paddle) {
    if (paddle->isSticky() && !ball->isStuck()) {
        ball->stickToPaddle(paddle->getBody());
    } else {
        b2Vec2 vel = ball->getBody()->GetLinearVelocity();
        vel.x = (ball->getBody()->GetPosition().x - paddle->getBody()->GetPosition().x) * 5.0f;
        ball->getBody()->SetLinearVelocity(vel);
    }
}

void PlayingState::handlePaddleBonusCollision(Paddle* paddle, Bonus* bonus) {
    if (bonus->isCollected()) return;
    bonus->collect();
    applyBonus(bonus->getType());
}

void PlayingState::applyBonus(Bonus::BonusType type) {
    if (type == Bonus::BonusType::PaddleResizeUp) mPaddle->changeSize(1);
    else if (type == Bonus::BonusType::PaddleResizeDown) mPaddle->changeSize(-1);
}
