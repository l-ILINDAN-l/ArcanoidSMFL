#include "MyContactListener.h"
#include "../PlayingState/PlayingState.h"
#include "../GameObject/GameObject.h"
#include "../Ball/Ball.h"
#include "../Brick/Brick.h"
#include "../Paddle/Paddle.h"
#include "../Bonus/Bonus.h"

MyContactListener::MyContactListener(PlayingState* state) : mPlayingState(state) {}

void MyContactListener::BeginContact(b2Contact* contact) {
    void* bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
    void* bodyUserDataB = contact->GetFixtureB()->GetBody()->GetUserData();
    if (!bodyUserDataA || !bodyUserDataB) return;

    auto objA = static_cast<GameObject*>(bodyUserDataA);
    auto objB = static_cast<GameObject*>(bodyUserDataB);

    auto handle = [&](auto* first, auto* second) {
        if (auto ball = dynamic_cast<Ball*>(first)) {
            if (auto brick = dynamic_cast<Brick*>(second)) {
                mPlayingState->handleBallBrickCollision(ball, brick);
            } else if (auto paddle = dynamic_cast<Paddle*>(second)) {
                mPlayingState->handleBallPaddleCollision(ball, paddle);
            }
        } else if (auto paddle = dynamic_cast<Paddle*>(first)) {
            if (auto bonus = dynamic_cast<Bonus*>(second)) {
                mPlayingState->handlePaddleBonusCollision(paddle, bonus);
            }
        }
    };
    handle(objA, objB);
    handle(objB, objA);
}
