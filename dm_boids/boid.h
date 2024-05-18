#ifndef BOID_H
#define BOID_H

#include <vector>
#include "vector.h"

struct Boid {
    Vector position;
    Vector velocity;

    Boid(float x, float y, float vx, float vy) : position(x, y), velocity(vx, vy) {}
};

std::vector<Boid> initialize_boids(float N_boids, float windowWidth, float windowHeight);

Vector cohesion(const Boid& boid, const std::vector<Boid>& boids, float dist_neighbors);
Vector separation(const Boid& boid, const std::vector<Boid>& boids, float dist_neighbors);
Vector alignment(const Boid& boid, const std::vector<Boid>& boids, float dist_neighbors);

void updateBoids(std::vector<Boid>& boids, float dist_neighbors, float cohesion_cste, float separation_cste, float alignment_cste, float dt);

#endif // BOID_H