#include "Brick.h"

Brick::Brick(b2World& world, sf::Texture& texture, sf::IntRect textureRect, sf::Vector2f position, int health, bool indestructible, Bonus::BonusType bonusType)
    : mHealth(health), mMaxHealth(health), mIsIndestructible(indestructible), mIsDestroyed(false), mBonusToDrop(bonusType) {

    mSprite.setTexture(texture);
    mSprite.setTextureRect(textureRect);
    mSprite.setOrigin(textureRect.width / 2.0f, textureRect.height / 2.0f);

    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(position.x / 30.0f, position.y / 30.0f);
    mBody = world.CreateBody(&bodyDef);
    mBody->SetUserData(this);

    b2PolygonShape shape;
    shape.SetAsBox((textureRect.width / 2.0f) / 30.0f, (textureRect.height / 2.0f) / 30.0f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    fixtureDef.restitution = 1.0f;
    mBody->CreateFixture(&fixtureDef);
}

void Brick::onHit() {
    if (mIsIndestructible || mIsDestroyed) return;

    mHealth--;
    if (mHealth > 0 && mMaxHealth > 1) {
        sf::Uint8 intensity = 55 + (200 * mHealth / mMaxHealth);
        mSprite.setColor(sf::Color(255, intensity, intensity));
    } else {
        mIsDestroyed = true;
        mBody->SetActive(false);
    }
}

bool Brick::isDestroyed() const { return mIsDestroyed; }
Bonus::BonusType Brick::getBonusTypeToDrop() const { return mBonusToDrop; }