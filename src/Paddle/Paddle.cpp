#include "Paddle.h"
#include <algorithm>

Paddle::Paddle(b2World& world, sf::Texture& atlas, sf::Vector2f position) 
    : mSizeLevel(0), mIsSticky(false) {
    
    mSizeData[-3] = sf::IntRect(0, 50, 64, 32);
    mSizeData[-2] = sf::IntRect(64, 50, 80, 32);
    mSizeData[-1] = sf::IntRect(144, 50, 100, 32);
    mSizeData[0]  = sf::IntRect(0, 100, 128, 32);
    mSizeData[1]  = sf::IntRect(128, 100, 150, 32);
    mSizeData[2]  = sf::IntRect(0, 150, 170, 32);
    mSizeData[3]  = sf::IntRect(170, 150, 200, 32);
    
    mSprite.setTexture(atlas);

    b2BodyDef bodyDef;
    bodyDef.type = b2_kinematicBody; 
    bodyDef.position.Set(position.x / 30.0f, position.y / 30.0f);
    mBody = world.CreateBody(&bodyDef);
    mBody->SetUserData(this);
    applySize();
}

void Paddle::setVelocity(float vx) { mBody->SetLinearVelocity(b2Vec2(vx, 0)); }

void Paddle::changeSize(int direction) {
    mSizeLevel = std::clamp(mSizeLevel + direction, -3, 3);
    applySize();
}

void Paddle::applySize() {
    if (mBody->GetFixtureList()) {
        mBody->DestroyFixture(mBody->GetFixtureList());
    }
    sf::IntRect newRect = mSizeData[mSizeLevel];
    b2PolygonShape shape;
    shape.SetAsBox((newRect.width / 2.0f) / 30.0f, (newRect.height / 2.0f) / 30.0f);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 100.0f;
    fixtureDef.friction = 0.0f;
    fixtureDef.restitution = 1.0f;
    mBody->CreateFixture(&fixtureDef);
    mSprite.setTextureRect(newRect);
    mSprite.setOrigin(newRect.width / 2.0f, newRect.height / 2.0f);
}

void Paddle::setSticky(bool sticky) { mIsSticky = sticky; }
bool Paddle::isSticky() const { return mIsSticky; }