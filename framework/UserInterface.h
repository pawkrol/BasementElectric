//
// Created by pawkrol on 1/3/16.
//

#ifndef DUDESPATROL_USERINTERFACE_H
#define DUDESPATROL_USERINTERFACE_H


#include <SFML/Graphics/Sprite.hpp>
#include "../World/Player.h"

class UserInterface {
private:
    Player *player;

    sf::Texture uiTexture;

    sf::Sprite fullHeart;
    sf::Sprite halfHeart;
    sf::Sprite emptyHeart;

    sf::Sprite fullPlus;
    sf::Sprite halfPlus;
    sf::Sprite emptyPlus;

    float zoom = 2.5f;

    float x_hoffset;
    float y_hoffset;
    float x_hfpos;

    float x_soffset;
    float x_sfpos;

    float playerHP;
    float fullPlayerHP;

    float playerStamina;
    float fullPlayerStamina;

public:
    UserInterface();

    void init(Player *player);
    void update();
    void render(sf::RenderWindow *window);

};


#endif //DUDESPATROL_USERINTERFACE_H
