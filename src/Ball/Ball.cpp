#include "Ball.h"
#include <iostream>

Ball::Ball(b2World& world, sf::Texture& texture, sf::Vector2f position)
    : mWorld(world), mStickJoint(nullptr), mIsStuck(true) {

    sf::IntRect textureRect(32, 150, 32, 32);
    mSprite.setTexture(texture);
    mSprite.setTextureRect(textureRect);
    mSprite.setOrigin(textureRect.width / 2.0f, textureRect.height / 2.0f);

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(position.x / 30.0f, position.y / 30.0f);
    bodyDef.bullet = true;
    bodyDef.linearDamping = 0.0f;
    mBody = world.CreateBody(&bodyDef);
    mBody->SetUserData(this);

    b2CircleShape shape;
    shape.m_radius = (textureRect.width / 2.0f) / 30.0f;

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.0f;
    fixtureDef.restitution = 1.0f;
    fixtureDef.restitutionThreshold = 0.0f;
    mBody->CreateFixture(&fixtureDef);
}

void Ball::launch(const b2Vec2& velocity) {
    if (!mIsStuck || !mStickJoint) return;
    mWorld.DestroyJoint(mStickJoint);
    mStickJoint = nullptr;
    mIsStuck = false;
    mBody->SetLinearVelocity(velocity);
}

void Ball::stickToPaddle(b2Body* paddleBody) {
    if (mIsStuck || !paddleBody) return;
    b2WeldJointDef jointDef;
    jointDef.Initialize(paddleBody, mBody, paddleBody->GetWorldCenter() + b2Vec2(0, -0.7f));
    jointDef.collideConnected = false;
    mStickJoint = (b2WeldJoint*)mWorld.CreateJoint(&jointDef);
    mIsStuck = true;
    mBody->SetLinearVelocity(b2Vec2(0,0));
}

bool Ball::isStuck() const { return mIsStuck; }

void Ball::reset(sf::Vector2f position, b2Body* paddleBody) {
    mBody->SetLinearVelocity(b2Vec2(0,0));
    mBody->SetTransform(b2Vec2(position.x / 30.0f, position.y / 30.0f), 0);
    stickToPaddle(paddleBody);
}

void Ball::increaseSpeed(float factor) {
    if (mIsStuck) return;
    b2Vec2 vel = mBody->GetLinearVelocity();
    vel *= factor;
    mBody->SetLinearVelocity(vel);
}