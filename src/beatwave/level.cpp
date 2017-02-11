#include <string>
#include <beatwave/level.hpp>

// TODO: Implement Level class
//
// The class should load level from XML file using PugiXML. Level
// class should encapsulate Player, Tunnels and Path
// correctors. Level::update() and Level::render() should propagate on
// Player, Tunnels and Path correctors. See how to utilize
// NestedGroups here.
//
// If the Game class is refactored correctly there should be no
// difference between Game and Level classes.

Level::Level(const char *levelFilePath)
{
}

void Level::update(int32_t deltaTime)
{
}

void Level::render(sf::RenderTarget *renderTarget)
{
}
