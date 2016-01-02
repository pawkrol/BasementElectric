//
// Created by pawkrol on 1/1/16.
//

#include "MobAI.h"
#include "../framework/GameWorld.h"

MobAI::MobAI(Entity *mob) {
    this->mob = mob;

    srand((unsigned int)(time(NULL)));
    ticker.restart();

    dir = rand() % 2;
    sign = rand() % 2;

    sign = (sign >= 0) ? 1 : -1;
}

std::vector<Renderable *> MobAI::getMobObstacles(GameWorld *world) {
    std::vector<Renderable *> obstacles = world->getClosestObstacles(mob);
    std::vector<Renderable *> entities = world->getClosestEntities(mob, mob->width);

    obstacles.insert(obstacles.end(), entities.begin(), entities.end());

    return obstacles;
}

sf::Vector2f MobAI::getMoveTo(GameWorld *world, float deltaTime) {
    Player *player = world->getPlayer();

    mob->toCarCords();
    player->toCarCords();
        sf::Vector2f mobCords(mob->x, mob->y);
        sf::Vector2f playerCords(player->x, player->y);
    mob->toIsoCords();
    player->toIsoCords();

    float x = mobCords.x - playerCords.x;
    float y = mobCords.y - playerCords.y;

    double distance = sqrt(x*x + y*y);
    if (distance < mob->width*6) {

        int sx = (x >= 0) ? -1 : 1;
        int sy = (y >= 0) ? -1 : 1;

        if (mob->checkCollision(getMobObstacles(world))){
            sx = -sx;
            sy = -sy;
        }

        if (fabs(x) >= fabs(y)) {
            return sf::Vector2f(mobCords.x + (sx * mob->speed) * deltaTime, mobCords.y);
        } else {
            return sf::Vector2f(mobCords.x, mobCords.y + (sy * mob->speed) * deltaTime);
        }
    } else {
        if (ticker.getElapsedTime().asSeconds() > 2) {
            dir = rand() % 2;
            sign = rand() % 2;

            sign = (sign == 0) ? 1 : -1;

            ticker.restart();
        }

        if (mob->checkCollision(getMobObstacles(world))){
            sign = -sign;
        }

        if (dir == 0){
            return sf::Vector2f(mobCords.x + (sign * mob->speed) * deltaTime, mobCords.y);
        } else {
            return sf::Vector2f(mobCords.x, mobCords.y + (sign * mob->speed) * deltaTime);
        }
    }
}
