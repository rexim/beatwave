#include <SFML/Graphics/RenderWindow.hpp>
#include <beatwave/pathcorrectorswarm.hpp>

PathCorrectorSwarm::PathCorrectorSwarm(const pugi::xml_node&)
{
    // TODO: Implement XML constructor for path corrector swarm
    //
    // It should construct the swarm from the XML node according to
    // the XML schema `level.xsd`. It should also check if the
    // corresponding node exists.
}

PathCorrectorSwarm::PathCorrectorSwarm(std::initializer_list<sf::Vector2f> positions)
{
    for (const auto &position: positions) {
        m_pathCorrectors.push_back(std::unique_ptr<PathCorrector>(new PathCorrector(position)));
    }
}

void PathCorrectorSwarm::hit(Player *player)
{
    for (auto &pathCorrector: m_pathCorrectors) {
        pathCorrector->hit(player);
    }
}

void PathCorrectorSwarm::tick(int32_t deltaTime)
{
    for (auto &pathCorrector: m_pathCorrectors) {
        pathCorrector->tick(deltaTime);
    }
}

void PathCorrectorSwarm::render(sf::RenderTarget *renderTarget) const
{
    for (const auto &pathCorrector: m_pathCorrectors) {
        pathCorrector->render(renderTarget);
    }
}
