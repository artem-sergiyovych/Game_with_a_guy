#include <SFML/Graphics.hpp>
#include "WallManager.hpp"
#include "Man.hpp"

#define windowWidth  2700
#define windowHeight 1500


int main() {
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "My window");

    sf::Texture texture_grass;
    if (!texture_grass.loadFromFile("grass.png")) { return 1; }
    texture_grass.setRepeated(true);
    texture_grass.setSmooth(true);
    sf::Sprite grass(texture_grass);
    grass.setTextureRect(sf::IntRect(0, 0, windowWidth, windowHeight));


    Man man;
    man.setPosition(20, 40);

    sf::Texture texture_wall;
    if (!texture_wall.loadFromFile("wall.png")) { return 1; }
    texture_wall.setRepeated(true);


    WallManager wallManager;
    std::vector<sf::Vector2f> wallPositions = {
            {300,  300},
            {300,  390},
            {300,  480},
            {300,  570},
            {300,  660},
            {300,  750},
            {300,  840},
            {300,  930},
            {300,  1020},
            {300,  1110},

            {2000, 300},
            {2000, 390},
            {2000, 480},
            {2000, 570},
            {2000, 660},
            {2000, 750},
            {2000, 840},
            {2000, 930},
            {2000, 1020},
            {2000, 1110},

            {420,  600},
            {540,  600},
            {660,  600},

            {1000, 300},
            {1000, 390},
            {1000, 480},
            {1000, 570},
            {1000, 660},
            {1000, 750},
            {1000, 840},
            {1000, 930},
            {1000, 1020},
            {1000, 1110},

            {1120, 900},
            {1240, 900},
            {1360, 900},
            {1480, 900},

            {1880, 300},
            {1760, 300},
            {1640, 300},
            {1520, 300}

    };
    wallManager.addWalls(texture_wall, wallPositions, .6f);

    sf::Clock clock;
    sf::Vector2f movement(0, 0);
    sf::Vector2f newPosition(0, 0);
    bool guyMoved = false;
    while (window.isOpen()) {
        sf::Time elapsedTime = clock.restart();
        const float movementSpeed = 1000;
        sf::Event event{};

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::KeyPressed) {
                movement = man.getMovementVector(event.key.code) * movementSpeed * elapsedTime.asSeconds();
                newPosition = man.getPosition() + movement;
                guyMoved = true;
            }
        }

        if (guyMoved) {
            bool intersectsWithWalls = false;
            for (const auto &wall: wallManager.getWalls()) {
                sf::FloatRect guyBounds = man.getLocalBounds();
                sf::FloatRect guyGlobalBounds = man.getTransform().transformRect(guyBounds);
                guyGlobalBounds.left = newPosition.x;
                guyGlobalBounds.top = newPosition.y;

                if (newPosition.x < 0) {
                    newPosition.x = 0;
                }
                if (newPosition.x + guyGlobalBounds.width > windowWidth) {
                    newPosition.x = windowWidth - guyGlobalBounds.width;
                }
                if (newPosition.y < 0) {
                    newPosition.y = 0;
                }
                if (newPosition.y + guyGlobalBounds.height > windowHeight) {
                    newPosition.y = windowHeight - guyGlobalBounds.height;
                }


                if (guyGlobalBounds.intersects(wall.getGlobalBounds())) {
                    intersectsWithWalls = true;
                    float newX = man.getPosition().x;
                    float newY = man.getPosition().y;
                    if (movement.x > 0) {
                        newX = wall.getGlobalBounds().left - guyGlobalBounds.width;
                    } else if (movement.x < 0) {
                        newX = wall.getGlobalBounds().left + wall.getGlobalBounds().width;
                    }
                    if (movement.y > 0) {
                        newY = wall.getGlobalBounds().top - guyGlobalBounds.height;
                    } else if (movement.y < 0) {
                        newY = wall.getGlobalBounds().top + wall.getGlobalBounds().height;
                    }
                    newPosition = sf::Vector2f(newX, newY);
                    break;
                }
            }

            if (!intersectsWithWalls) {
                man.setPosition(newPosition);
                movement = sf::Vector2f(0, 0);
            } else {

                movement = sf::Vector2f(0, 0);
            }
        }
        guyMoved = false;

        window.clear(sf::Color::Black);


        window.draw(grass);
        window.draw(wallManager);
        window.draw(man);


        window.display();
    }
}