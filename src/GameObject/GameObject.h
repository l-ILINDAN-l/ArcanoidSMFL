#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H


#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

class PlayingState;

class GameObject : public sf::Drawable {
public:
    virtual ~GameObject() = default;

    virtual void update(sf::Time dt) {
        if (mBody && mBody->IsActive()) {
            mSprite.setPosition(mBody->GetPosition().x * 30.0f, mBody->GetPosition().y * 30.0f);
            mSprite.setRotation(mBody->GetAngle() * 180.0f / b2_pi);
        }
    }

    b2Body* getBody() const { return mBody; }
    sf::Sprite& getSprite() { return mSprite; }

protected:
    GameObject() : mBody(nullptr) {}

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        if (mBody && mBody->IsActive()) {
            target.draw(mSprite, states);
        }
    }

    sf::Sprite mSprite;
    b2Body* mBody;
};



#endif //GAMEOBJECT_H
