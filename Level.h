#ifndef LEARNCPP_LEVEL_H
#define LEARNCPP_LEVEL_H

#include <vector>
#include <boost/filesystem.hpp>
#include <boost/multi_array.hpp>

class Scene;
class Entity;
class RenderWindow;
class Texture;
class Rectangle;

class Level {
public:
    Level(Scene& scene, const boost::filesystem::path& levelPath, int tileSize);
    void draw_to(RenderWindow& targetRenderer);

    bool check_collision(Entity& entity);
private:
    const Texture* pTexture;
    //std::vector<std::vector<const SDL_Rect*>> grid;
    boost::multi_array<const Rectangle*, 2> grid;
    int tileSize;
};


#endif //LEARNCPP_LEVEL_H
