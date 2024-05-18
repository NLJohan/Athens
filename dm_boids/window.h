#ifndef WINDOW_H
#define WINDOW_H

#include <SFML/Graphics.hpp>
#include "boid.h"

void initialize_window(sf::RenderWindow& window, int windowWidth, int windowHeight);
void draw_boids(std::vector<Boid>& boid, sf::RenderWindow& window);

#endif // WINDOW_H
