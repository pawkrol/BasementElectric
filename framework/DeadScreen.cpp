//
// Created by pawkrol on 1/2/16.
//

#include "DeadScreen.h"
#include "GameException.h"

DeadScreen::DeadScreen(sf::RenderWindow *w) {
    this->x = 0;
    this->y = 0;
    this->width = w->getSize().x;
    this->height = w->getSize().y;

    init();
}

void DeadScreen::init() {
    redScreen.setPosition(x, y);
    redScreen.setSize(sf::Vector2f(width, height));
    redScreen.setFillColor(sf::Color(255, 0, 0, alpha));

    if (!font.loadFromFile("res/slkscre.ttf")){
        throw GameException("Exception: Can't load font");
    }

    deadText.setFont(font);
    deadText.setString("You are dead!");
    deadText.setCharacterSize(32);
    deadText.setColor(sf::Color::White);

    float textWidthPos = x + width/2 - deadText.getGlobalBounds().width/2;
    deadText.setPosition(textWidthPos, y + height/4);

    infoText.setFont(font);
    infoText.setString("Press <esc> key to continue");
    infoText.setCharacterSize(16);
    infoText.setColor(sf::Color::White);

    float textHeightPos = y + height/4 + deadText.getGlobalBounds().height*2;
    infoText.setPosition(6 + textWidthPos, textHeightPos);

}

void DeadScreen::update() {

}

void DeadScreen::render(sf::RenderWindow *w, Camera *c) {
    w->draw(redScreen);
    w->draw(deadText);
    w->draw(infoText);
}

void DeadScreen::draw(sf::RenderTarget &target, sf::RenderStates states) const {
}
