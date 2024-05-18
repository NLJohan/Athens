#include <vector>
#include <SFML/Graphics.hpp>
#include "window.h"
#include "boid.h"
#include "vector.h"


// WSL : g++ -o boids main.cpp boid.cpp window.cpp -lsfml-graphics -lsfml-window -lsfml-system
// WSL : ./ boids
// WSL : rm boids


int main(){
float dist_neighbors=50.0;
float cohesion_cste=0.01;
float separation_cste=0.5;
float alignment_cste=0.2;
float dt=1.0;
int N_boids=75;
int FPS=60;

const sf::Time frameTime = sf::seconds(1.0 / FPS);


sf::RenderWindow window;
initialize_window(window, windowWidth, windowHeight);

std::vector<Boid> boids = initialize_boids(N_boids, windowWidth, windowHeight);
sf::Clock clock;
while (window.isOpen()) {
        // Code used to close the window if asked
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            };
        };

        updateBoids(boids, dist_neighbors, cohesion_cste, separation_cste, alignment_cste, dt);
        draw_boids(boids, window);

        sf::Time elapsedTime = clock.restart();
        if (elapsedTime < frameTime) {
            sf::sleep(frameTime - elapsedTime);
        }
};
return 0;
}

int main();
