//
// Created by pawkrol on 1/7/16.
//

#include <string.h>
#include "WorldResourceManager.h"
#include "../framework/GameException.h"

WorldResourceManager::WorldResourceManager() {
    loadBlob(doorsTexture, "res/door.png");
    loadBlob(blockTexture, "res/block.png");
    loadBlob(tileTexture, "res/tile.png");
    loadBlob(ratSpawnerTexture, "res/ratSpawner.png");
    loadBlob(ratTexture, "res/ratWalk.png");
    loadBlob(bloodSpotTexture, "res/bloodSpot.png");
    loadBlob(explosionTexture, "res/explosion.png");
    loadBlob(collectableHPTexture, "res/collectTomato.png");
    loadBlob(collectableStaminaTexture, "res/collectCucumber.png");
    loadBlob(leverTexture, "res/lever.png");
    loadBlob(aoeTexture, "res/aoe.png");
    loadBlob(pickleTexture, "res/madPickle.png");
    loadBlob(pickleShotTexture, "res/pickleShot.png");
    loadBlob(pickleSpawnerTexture, "res/picklespawner.png");
}

void WorldResourceManager::loadBlob(sf::Texture *texture, const char *location) {
    if (!texture->loadFromFile(location)){
        throw GameException(strcat((char *) "Exception: Can't load ", location));
    }
}

sf::Texture* WorldResourceManager::getTileTexture() {
    return tileTexture;
}

sf::Texture* WorldResourceManager::getBlockTexture() {
    return blockTexture;
}

sf::Texture* WorldResourceManager::getDoorsTexture() {
    return doorsTexture;
}

sf::Texture* WorldResourceManager::getRatSpawnerTexture() {
    return ratSpawnerTexture;
}

sf::Texture* WorldResourceManager::getRatTexture() {
    return ratTexture;
}

sf::Texture* WorldResourceManager::getBloodSpotTexture() {
    return bloodSpotTexture;
}

sf::Texture* WorldResourceManager::getExplosionTexture() {
    return explosionTexture;
}

sf::Texture* WorldResourceManager::getCollectableHPTexture() {
    return collectableHPTexture;
}

sf::Texture* WorldResourceManager::getCollectableStaminaTexture() {
    return collectableStaminaTexture;
}

sf::Texture* WorldResourceManager::getLeverTexture() {
    return leverTexture;
}

sf::Texture* WorldResourceManager::getAOETexture() {
    return aoeTexture;
}

sf::Texture* WorldResourceManager::getPickleTexture() {
    return pickleTexture;
}

sf::Texture* WorldResourceManager::getPickleShotTexture() {
    return pickleShotTexture;
}

sf::Texture* WorldResourceManager::getPickleSpawnerTexture(){
    return pickleSpawnerTexture;
}

WorldResourceManager::~WorldResourceManager() {
    delete tileTexture;
    delete blockTexture;
    delete doorsTexture;
    delete ratSpawnerTexture;
    delete ratTexture;
    delete bloodSpotTexture;
    delete explosionTexture;
    delete collectableHPTexture;
    delete collectableStaminaTexture;
    delete leverTexture;
    delete aoeTexture;
    delete pickleTexture;
    delete pickleShotTexture;
    delete pickleSpawnerTexture;
}