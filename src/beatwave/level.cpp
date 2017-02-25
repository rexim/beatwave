#include <pugixml.hpp>

#include <string>
#include <beatwave/config.hpp>
#include <beatwave/level.hpp>

Level::Level(const char *levelFilePath)
{
    pugi::xml_document doc;

    doc.load_file(levelFilePath);

    m_player.reset(new Player(doc.child("player")));
    m_tunnel.reset(new Tunnel(doc.child("tunnel")));
    m_pathCorrectors.reset(new PathCorrectorSwarm(doc.child("pathCorrectors")));
}

void Level::tick(int32_t deltaTime)
{
    m_player->tick(deltaTime);
    m_pathCorrectors->tick(deltaTime);

    m_tunnel->hit(m_player.get());
    m_pathCorrectors->hit(m_player.get());
}

void Level::render(sf::RenderTarget *renderTarget)
{
    renderTarget->clear(config::WALL_COLOR);
    m_player->centerView(renderTarget);

    m_tunnel->render(renderTarget);
    m_player->render(renderTarget);
    m_pathCorrectors->render(renderTarget);
}

void Level::kick()
{
    m_player->kickStep();
}

void Level::snare()
{
    m_player->snareStep();
}

void Level::hihat()
{
    m_player->hihatStep();
}

void Level::shaman()
{
    m_player->shamanStep();
}
