//
// Created by pawkrol on 11/27/15.
//

#ifndef DUDESPATROL_TILE_H
#define DUDESPATROL_TILE_H

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/VertexArray.hpp>

#include "../../../include/Renderable.h"

class Tile : public Renderable{
private:
    sf::VertexArray vertexArray;

    bool isInWindow(Camera *c);

protected:
    sf::Uint8 defaultDarkness = 0;
    sf::Uint8 darkness;

    void updateDarkness();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void create();

public:
    static int const WIDTH = 32;
    static int const HEIGHT = 32;

    Tile();
    Tile(float x, float y);

    virtual void init();
    void update();
    void render(sf::RenderWindow *w, Camera *c);

    void setDarkness(sf::Uint8 darkness);
};


#endif //DUDESPATROL_TILE_H
