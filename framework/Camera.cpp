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

    window->setView(camera);
}

void Camera::update(float x, float y) {
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
