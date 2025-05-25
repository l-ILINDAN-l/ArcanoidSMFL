//
// Created by gellertilya on 25.05.25.
//

#ifndef BALL_H
#define BALL_H

#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>

class Ball {
public:
    Ball();
    void launch();
    void stickToPaddle();
    void update(float dt);
    void draw(sf::RenderWindow& target);
private:
    sf::Sprite sprite;
    sf::Texture texture;
    b2Body* m_body;
    bool m_isSticky;
    bool m_isOnPaddle;
};



#endif //BALL_H
