#include "Bonus.h"

Bonus::Bonus(b2World& world, sf::Texture& texture, sf::Vector2f position, BonusType type)
    : mType(type), mIsCollected(false), mCurrentFrame(0) {

    switch (mType) {
        case BonusType::PaddleResizeUp: mBaseTextureRect = sf::IntRect(0, 200, 40, 40); break;
        case BonusType::PaddleResizeDown: mBaseTextureRect = sf::IntRect(0, 240, 40, 40); break;
        default: mBaseTextureRect = sf::IntRect(0, 200, 40, 40); break;
    }

    mSprite.setTexture(texture);
    mSprite.setTextureRect(mBaseTextureRect);
    mSprite.setOrigin(mBaseTextureRect.width / 2.0f, mBaseTextureRect.height / 2.0f);

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(position.x / 30.0f, position.y / 30.0f);
    bodyDef.linearVelocity = b2Vec2(0, 2.0f);
    mBody = world.CreateBody(&bodyDef);
    mBody->SetUserData(this);

    b2PolygonShape shape;
    shape.SetAsBox((mBaseTextureRect.width / 2.0f) / 30.0f, (mBaseTextureRect.height / 2.0f) / 30.0f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.isSensor = true;
    mBody->CreateFixture(&fixtureDef);
}

void Bonus::update(sf::Time dt) {
    GameObject::update(dt);
    if (mAnimationClock.getElapsedTime().asMilliseconds() > 100) {
        mCurrentFrame = (mCurrentFrame + 1) % 7;
        sf::IntRect newRect = mBaseTextureRect;
        newRect.left += newRect.width * mCurrentFrame;
        mSprite.setTextureRect(newRect);
        mAnimationClock.restart();
    }
}

Bonus::BonusType Bonus::getType() const { return mType; }
void Bonus::collect() {
    mIsCollected = true;
    mBody->SetActive(false);
}
bool Bonus::isCollected() const { return mIsCollected; }
