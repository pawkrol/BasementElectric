//
// Created by pawkrol on 1/3/16.
//

#include "UserInterface.h"
#include "GameException.h"

UserInterface::UserInterface() {
    x_hoffset = 16;
    y_hoffset = 128;
}

void UserInterface::init(Player *player) {
    this->player = player;
    fullPlayerHP = player->getFullHP() / 5;
    fullPlayerStamina = player->getFullStamina() / 10;
    prevPlayerHP = fullPlayerHP;

    if (!uiTexture.loadFromFile("res/ui.png"))
        throw GameException("Exception: Can't load ui");

    fullHeart.setTexture(uiTexture);
    fullHeart.setTextureRect(sf::IntRect(0, 0, 32, 32));
    fullHeart.setScale(zoom, zoom);

    halfHeart.setTexture(uiTexture);
    halfHeart.setTextureRect(sf::IntRect(32, 0, 32, 32));
    halfHeart.setScale(zoom, zoom);

    emptyHeart.setTexture(uiTexture);
    emptyHeart.setTextureRect(sf::IntRect(64, 0, 32, 32));
    emptyHeart.setScale(zoom, zoom);

    fullPlus.setTexture(uiTexture);
    fullPlus.setTextureRect(sf::IntRect(0, 32, 32, 32));
    fullPlus.setScale(zoom, zoom);

    halfPlus.setTexture(uiTexture);
    halfPlus.setTextureRect(sf::IntRect(32, 32, 32, 32));
    halfPlus.setScale(zoom, zoom);

    emptyPlus.setTexture(uiTexture);
    emptyPlus.setTextureRect(sf::IntRect(64, 32, 32, 32));
    emptyPlus.setScale(zoom, zoom);

    whiteScreen.setPosition(0, 0);
}

void UserInterface::update() {
    deltaTime += whiteScreenTimer.restart();
    if (isWhiteScreen){

        alpha -= alpha * deltaTime.asSeconds()/100;

        if (alpha < 0) alpha = 0;

        if (alpha == 0 ){//deltaTime >= sf::seconds(whiteAliveTime)){
            isWhiteScreen = false;
            alpha = 40;
        }
    }


    playerHP = player->getHP() / 5;
    if (playerHP < 0) playerHP = 0;

    playerStamina = player->getStamina() / 10;
    if (playerStamina < 0) playerStamina = 0;

    if (prevPlayerHP > playerHP){
        isWhiteScreen = true;
        prevPlayerHP = playerHP;
    }
}

void UserInterface::render(sf::RenderWindow *window) {
    sf::Vector2u windowSize = window->getSize();

    whiteScreen.setSize(sf::Vector2f(windowSize.x, windowSize.y));
    if (isWhiteScreen){
        whiteScreen.setFillColor(sf::Color(255, 10, 10, alpha));
        window->draw(whiteScreen);
    }

    int j = 0;
    for (; j < int(playerHP); j++) {
        x_hfpos = x_hoffset + j * 32 * fullHeart.getScale().x;
        fullHeart.setPosition(x_hfpos, windowSize.y - y_hoffset);
        window->draw(fullHeart);
    }


    if (playerHP - int(playerHP) != 0) {
        x_hfpos = x_hoffset + j * 32 * halfHeart.getScale().x;
        halfHeart.setPosition(x_hfpos, windowSize.y - y_hoffset);
        window->draw(halfHeart);
        j++;
    }

    for (int i = j; i < int(fullPlayerHP); i++) {
        x_hfpos = x_hoffset + i * 32 * emptyHeart.getScale().x;
        emptyHeart.setPosition(x_hfpos, windowSize.y - y_hoffset);
        window->draw(emptyHeart);
    }

    //////////////////STAMINA

    j = 0;
    x_soffset = windowSize.x - 32 * fullPlus.getScale().x;
    for (; j < int(playerStamina); j++) {
        x_sfpos = x_soffset - j * 32 * fullPlus.getScale().x;
        fullPlus.setPosition(x_sfpos, windowSize.y - y_hoffset);
        window->draw(fullPlus);
    }

    if (playerStamina - int(playerStamina) != 0) {
        x_sfpos = x_soffset - j * 32 * halfPlus.getScale().x;
        halfPlus.setPosition(x_sfpos, windowSize.y - y_hoffset);
        window->draw(halfPlus);
        j++;
    }

    for (int i = j; i < int(fullPlayerStamina); i++) {
        x_sfpos = x_soffset - i * 32 * emptyPlus.getScale().x;
        emptyPlus.setPosition(x_sfpos, windowSize.y - y_hoffset);
        window->draw(emptyPlus);
    }
}
