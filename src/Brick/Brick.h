//
// Created by gellertilya on 25.05.25.
//

#ifndef BRICK_H
#define BRICK_H

#include "../GameObject/GameObject.h"
#include "../Bonus/Bonus.h"

class Brick : public GameObject {
public:
    Brick(b2World& world, sf::Texture& texture, sf::IntRect textureRect, sf::Vector2f position, int health, bool indestructible, Bonus::BonusType bonusType);
    void onHit();
    bool isDestroyed() const;
    Bonus::BonusType getBonusTypeToDrop() const;
private:
    int mHealth;
    int mMaxHealth;
    bool mIsIndestructible;
    bool mIsDestroyed;
    Bonus::BonusType mBonusToDrop;
};


#endif //BRICK_H
