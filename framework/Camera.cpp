//
// Created by pawkrol on 11/29/15.
//

#include "Camera.h"

Camera::Camera(sf::RenderWindow *window, sf::Vector2f size, sf::Vector2f center) {
    this->window = window;
    this->size = size;
    this->center = center;

    camera.setSize(size);
    camera.zoom(_zoom);
    camera.setCenter(center);

    srand((unsigned int)time(NULL));

    window->setView(camera);
}

void Camera::update(float x, float y) {
    if (isShaking){
        x += sin(rand()%360 * (3.1415/180)) * shakeSize;
        y += sin(rand()%360 * (3.1415/180)) * shakeSize;

        if (shakeClock.getElapsedTime().asSeconds() > shakeTime){
            isShaking = false;
        }
    }

    center.x = x;
    center.y = y;

    camera.setCenter(center);
    window->setView(camera);
}

sf::FloatRect Camera::getViewport() {
    return camera.getViewport();
}

sf::Vector2f Camera::getSize() {
    return size;
}

sf::Vector2f Camera::getCenter() {
    return center;
}

float Camera::getZoom() {
    return _zoom;
}

void Camera::shake(){
    isShaking = true;
    shakeClock.restart();
}
