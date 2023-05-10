#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

class Man : public sf::Drawable, public sf::Transformable {
private:
    sf::Texture texture_man;
    sf::Sprite man;
public:
    Man() {
        texture_man.loadFromFile("guy.png");
        man.setTexture(texture_man);
        man.setScale(4, 4);
    }

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
        target.draw(man, states);
    }

    virtual void setPosition(float x, float y) {
        man.setPosition(x, y);
    }

    virtual void setPosition(sf::Vector2f vector) {
        man.setPosition(vector);
    }

    virtual sf::FloatRect getLocalBounds() const {
        return man.getLocalBounds();
    }

    virtual sf::Vector2f getPosition() const {
        return man.getPosition();
    }

    virtual sf::Vector2f getMovementVector(sf::Keyboard::Key key) const {
        sf::Vector2f movement(0, 0);
        const float movementSpeed = 10;
        if (key == sf::Keyboard::Up) {
            movement.y -= movementSpeed;
        } else if (key == sf::Keyboard::Left) {
            movement.x -= movementSpeed;
        } else if (key == sf::Keyboard::Down) {
            movement.y += movementSpeed;
        } else if (key == sf::Keyboard::Right) {
            movement.x += movementSpeed;
        }
        return movement;
    }

    virtual sf::Transform getTransform() const {
        return man.getTransform();
    }
};
