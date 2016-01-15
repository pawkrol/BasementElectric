//
// Created by pawkrol on 1/5/16.
//

#ifndef DUDESPATROL_LEVER_H
#define DUDESPATROL_LEVER_H


#include <SFML/Graphics/Sprite.hpp>

#include "../../../include/Renderable.h"
#include "../../../include/ActionObject.h"
#include "Doors.h"

class Lever : public ActionObject{
private:
    Doors *door;

    sf::Uint8 darkness;
    sf::Texture *texture;

    bool _on = false;

    sf::Sprite sprite;
    sf::IntRect onRect;
    sf::IntRect offRect;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const{};

public:
    Lever(float x, float y, bool isOn, Doors *door);

    void init();
    void update(GameWorld *);
    void render(sf::RenderWindow *w, Camera *c);

    bool isOn();
    void action();
    void setDoors(Doors *door);
};


#endif //DUDESPATROL_LEVER_H
