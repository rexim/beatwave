#ifndef LEVEL_HPP_
#define LEVEL_HPP_

namespace sf {
    class RenderTarget;
}

class Level
{
public:
    Level(const char *levelFilePath);

    void update(int32_t deltaTime);
    void render(sf::RenderTarget *renderTarget);
};

#endif  // LEVEL_HPP_
