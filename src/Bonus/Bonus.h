#ifndef BONUS_H
#define BONUS_H

#include "../GameObject/GameObject.h"

class Bonus : public GameObject {
public:
    enum class BonusType { None, PaddleResizeUp, PaddleResizeDown, BallSpeedUp, StickyPaddle, ExtraLifeFloor };

    Bonus(b2World& world, sf::Texture& texture, sf::Vector2f position, BonusType type);

    void update(sf::Time dt) override;
    BonusType getType() const;

    void collect();
    bool isCollected() const;

private:
    BonusType mType;
    bool mIsCollected;
    sf::Clock mAnimationClock;
    int mCurrentFrame;
    sf::IntRect mBaseTextureRect;
};





#endif //BONUS_H
