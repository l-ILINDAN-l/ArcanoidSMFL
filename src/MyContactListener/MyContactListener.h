#ifndef MYCONTACTLISTENER_H
#define MYCONTACTLISTENER_H

#include <box2d/box2d.h>

class PlayingState;

class MyContactListener : public b2ContactListener {
public:
    explicit MyContactListener(PlayingState* state);
    void BeginContact(b2Contact* contact) override;
private:
    PlayingState* mPlayingState;
};


#endif //MYCONTACTLISTENER_H
