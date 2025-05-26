#ifndef PADDLE_H
#define PADDLE_H

#include "../GameObject/GameObject.h"
#include <vector>
#include <map>
#include <SFML/Graphics.hpp>

class Paddle : public GameObject {
public:
    Paddle(b2World& world, sf::Texture& atlas, sf::Vector2f position);
    void setVelocity(float vx);
    void changeSize(int direction);
    void setSticky(bool sticky);
    bool isSticky() const;
private:
    void applySize();
    int mSizeLevel;
    bool mIsSticky;
    std::map<int, sf::IntRect> mSizeData;
};



#endif //PADDLE_H
