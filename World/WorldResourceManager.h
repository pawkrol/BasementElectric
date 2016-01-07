//
// Created by pawkrol on 1/7/16.
//

#ifndef DUDESPATROL_WORLDRESOURCEMANAGER_H
#define DUDESPATROL_WORLDRESOURCEMANAGER_H


#include <SFML/Graphics/Texture.hpp>

class WorldResourceManager {
private:
    sf::Texture *tileTexture = new sf::Texture;
    sf::Texture *blockTexture = new sf::Texture;
    sf::Texture *doorsTexture = new sf::Texture;
    sf::Texture *ratSpawnerTexture = new sf::Texture;
    sf::Texture *ratTexture = new sf::Texture;
    sf::Texture *bloodSpotTexture = new sf::Texture;
    sf::Texture *explosionTexture = new sf::Texture;
    sf::Texture *collectableHPTexture = new sf::Texture;
    sf::Texture *collectableStaminaTexture = new sf::Texture;
    sf::Texture *leverTexture = new sf::Texture;

    void loadBlob(sf::Texture *texture, const char *location);

public:
    WorldResourceManager();
    ~WorldResourceManager();

    sf::Texture* getTileTexture();
    sf::Texture* getBlockTexture();
    sf::Texture* getDoorsTexture();
    sf::Texture* getRatSpawnerTexture();
    sf::Texture* getRatTexture();
    sf::Texture* getBloodSpotTexture();
    sf::Texture* getExplosionTexture();
    sf::Texture* getCollectableHPTexture();
    sf::Texture* getCollectableStaminaTexture();
    sf::Texture* getLeverTexture();
};


#endif //DUDESPATROL_WORLDRESOURCEMANAGER_H
