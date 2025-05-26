#ifndef BALL_H
#define BALL_H

#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>

#include "../GameObject/GameObject.h"

class Ball : public GameObject {
public:
    Ball(b2World& world, sf::Texture& texture, sf::Vector2f position);
    void launch(const b2Vec2& velocity);
    void increaseSpeed(float factor);
    void stickToPaddle(b2Body* paddleBody);
    bool isStuck() const;
    void reset(sf::Vector2f position, b2Body* paddleBody);
private:
    b2World& mWorld;
    b2WeldJoint* mStickJoint;
    bool mIsStuck;
};



#endif //BALL_H
