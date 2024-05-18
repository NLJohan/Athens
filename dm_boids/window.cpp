#include <SFML/Graphics.hpp>
#include "window.h"

void initialize_window(sf::RenderWindow& window, int windowWidth, int windowHeight) {
    window.create(sf::VideoMode(windowWidth, windowHeight), "Boids Simulation");
}

void draw_boids(std::vector<Boid>& boids, sf::RenderWindow& window) {
    window.clear();
    for (const Boid& boid : boids) {
        sf::CircleShape shape(3);
        shape.setPosition(boid.position.x, boid.position.y);
        shape.setFillColor(sf::Color::White);
        window.draw(shape);
    };
    window.display();
}
