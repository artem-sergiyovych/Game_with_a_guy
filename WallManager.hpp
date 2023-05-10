#include <iostream>
#include <SFML/Graphics.hpp>

class WallManager : public sf::Drawable {
private:
    std::vector<sf::Sprite> walls;
    sf::Texture texture_grass;

public:
    void addWalls(sf::Texture &texture, const std::vector<sf::Vector2f> &positions, float scale = 1.0f) {
        for (const auto &position: positions) {
            sf::Sprite wall(texture);
            wall.setPosition(position);
            wall.setScale(scale, scale);
            walls.push_back(wall);
        }
    }

    void draw(sf::RenderTarget &target, sf::RenderStates states = sf::RenderStates::Default) const {
        for (const auto &wall: walls) {
            target.draw(wall, states);
        }
    }

    const std::vector<sf::Sprite> &getWalls() const {
        return walls;
    }

};