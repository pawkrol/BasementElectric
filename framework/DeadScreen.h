//
// Created by pawkrol on 1/2/16.
//

#ifndef DUDESPATROL_DEADSCREEN_H
#define DUDESPATROL_DEADSCREEN_H


#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include "../include/Renderable.h"

class DeadScreen : public Renderable{
private:
    sf::RectangleShape redScreen;
    sf::Text deadText;
    sf::Text infoText;
    sf::Font font;

    sf::Uint8 alpha = 80;

protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;

public:
    DeadScreen(sf::RenderWindow *w);

    void init();
    void update();
    void render(sf::RenderWindow *w, Camera *c);
};


#endif //DUDESPATROL_DEADSCREEN_H
