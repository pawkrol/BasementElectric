//
// Created by pawkrol on 1/5/16.
//

#ifndef DUDESPATROL_ACTIONOBJECT_H
#define DUDESPATROL_ACTIONOBJECT_H


#include "Renderable.h"

class ActionObject : public Renderable{
private:
    void update(){};

public:
    virtual void update(GameWorld *) = 0;
    virtual void action() = 0;

};


#endif //DUDESPATROL_ACTIONOBJECT_H
