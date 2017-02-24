#ifndef BEATWAVE_PATHCORRECTORSWARM_HPP_
#define BEATWAVE_PATHCORRECTORSWARM_HPP_

#include <pugixml.hpp>

#include <vector>
#include <memory>
#include <initializer_list>

#include <beatwave/pathcorrector.hpp>

namespace sf {
    class RenderTarget;
}

class PathCorrectorSwarm
{
public:
    PathCorrectorSwarm(const pugi::xml_node&);
    PathCorrectorSwarm(std::initializer_list<sf::Vector2f> positions);

    void hit(Player *player);
    void tick(int32_t deltaTime);
    void render(sf::RenderTarget *renderTarget) const;

private:
    // TODO: Investigate Sigmentation Fault on using PathCorrectors by value
    //
    // Replace `std::vector<std::unique_ptr<PathCorrector>>` with
    // `std::vector<PathCorrector>`. Observe that Player doesn't
    // interact with path correctors anymore and sometimes the
    // application sigfaults when the player dies.
    //
    // We need to investigate why exactly this happens.
    std::vector<std::unique_ptr<PathCorrector>> m_pathCorrectors;
};

#endif  // BEATWAVE_PATHCORRECTORSWARM_HPP_
