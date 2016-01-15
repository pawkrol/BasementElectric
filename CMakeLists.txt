cmake_minimum_required(VERSION 3.3)
project(DudesPatrol)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")

set(SOURCE_FILES main.cpp
        framework/ScreenComponent.cpp framework/ScreenComponent.h
        framework/GameWorld.cpp framework/GameWorld.h
        include/Renderable.h World/Level/Level.cpp World/Level/Level.h
            World/Level/Elements/Tile.cpp World/Level/Elements/Tile.h
        framework/Camera.cpp framework/Camera.h framework/Input/Commands/Command.h
            framework/Input/InputHandler.cpp framework/Input/InputHandler.h include/Entity.h
        framework/Input/Commands/MoveUpCommand.cpp framework/Input/Commands/MoveUpCommand.h
        World/Player.cpp World/Player.h framework/Input/Commands/MoveDownCommand.cpp
        framework/Input/Commands/MoveDownCommand.h framework/Input/Commands/MoveLeftCommand.cpp
            framework/Input/Commands/MoveLeftCommand.h framework/Input/Commands/MoveRightCommand.cpp
        framework/Input/Commands/MoveRightCommand.h framework/sfmlAddon/Animation.cpp
            framework/sfmlAddon/Animation.h framework/sfmlAddon/AnimatedSprite.cpp
        framework/sfmlAddon/AnimatedSprite.h World/Level/Elements/Block.cpp
            World/Level/Elements/Block.h World/Level/Lights/LightSource.cpp
        World/Level/Lights/LightSource.h framework/GameException.h
        World/PlayerResourceManager.cpp World/PlayerResourceManager.h
        framework/Input/Commands/HitCommand.cpp framework/Input/Commands/HitCommand.h
        World/Mobs/Rat.cpp World/Mobs/Rat.h World/Level/Elements/RatSpawner.cpp
        World/Level/Elements/RatSpawner.h World/EffectEntities/BloodSpot.cpp
        World/EffectEntities/BloodSpot.h include/GroundEntity.h World/Mobs/RatAI.cpp
        World/Mobs/RatAI.h World/EffectEntities/Explosion.cpp World/EffectEntities/Explosion.h
        framework/DeadScreen.cpp framework/DeadScreen.h framework/UserInterface.cpp
        framework/UserInterface.h World/CollectableStamina.cpp World/CollectableStamina.h
        World/CollectableHP.cpp World/CollectableHP.h World/Level/Effects/LevelEffects.cpp
        World/Level/Effects/LevelEffects.h World/Level/Elements/Doors.cpp World/Level/Elements/Doors.h
        World/Level/Elements/Lever.cpp World/Level/Elements/Lever.h framework/Input/Commands/ActionCommand.cpp
        framework/Input/Commands/ActionCommand.h include/ActionObject.h
        World/WorldResourceManager.cpp World/WorldResourceManager.h include/Mob.h World/EffectEntities/AOEattack.cpp World/EffectEntities/AOEattack.h framework/Input/Commands/AOECommand.cpp framework/Input/Commands/AOECommand.h World/Mobs/MadPickle.cpp World/Mobs/MadPickle.h World/Mobs/PickleAI.cpp World/Mobs/PickleAI.h World/EffectEntities/PickleShot.cpp World/EffectEntities/PickleShot.h World/Level/Elements/PickleSpawner.cpp World/Level/Elements/PickleSpawner.h)

add_executable(DudesPatrol ${SOURCE_FILES})

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(DudesPatrol ${SFML_LIBRARIES})
endif()