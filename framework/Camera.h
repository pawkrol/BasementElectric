//
// Created by pawkrol on 11/29/15.
//

#ifndef DUDESPATROL_CAMERA_H
#define DUDESPATROL_CAMERA_H


#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Camera {
private:
    const float _zoom = .3f;

    sf::View camera;

    sf::Vector2f size;
    sf::Vector2f center;

    sf::Clock shakeClock;
    bool isShaking = false;
    float shakeTime = .3f;
    float shakeSize = 2.f;

    sf::RenderWindow *window;

public:
    Camera(sf::RenderWindow *window, sf::Vector2f size, sf::Vector2f center);

    void update(float x, float y);
    sf::FloatRect getViewport();
    sf::Vector2f getSize();
    sf::Vector2f getCenter();
    float getZoom();
    void shake();
};


#endif //DUDESPATROL_CAMERA_H
