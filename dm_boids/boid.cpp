#include <vector>
#include <random>
#include "vector.h"
#include "boid.h"

constexpr float Vmax=4;


float randomFloat(float a, float b) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    
    std::uniform_real_distribution<float> dis(a, b);

    return dis(gen);
}


std::vector<Boid> initialize_boids(float N_boids, float windowWidth, float windowHeight){
    std::vector<Boid> boids;
    for (int i = 0; i < N_boids; ++i) {
        boids.emplace_back(windowWidth*rand()/RAND_MAX/10, windowHeight*rand()/RAND_MAX/10, Vmax*randomFloat(-1,1), Vmax*randomFloat(-1,1));
    }
    return boids;
}

Vector cohesion(const Boid& boid, const std::vector<Boid>& boids, float dist_neighbors) {
    Vector CdM(0.0f, 0.0f);
    int count = 0;
    for (const Boid& other : boids) {
        float dist = (boid.position - other.position).norm();
        if (dist > 0 && dist < dist_neighbors) {
            CdM += other.position;
            count++;
        }
    }
    if (count > 0) {
        CdM = CdM * (1.0f / count);
        return (CdM - boid.position);
    }
    return Vector(0.0f, 0.0f);
}

Vector separation(const Boid& boid, const std::vector<Boid>& boids, float dist_neighbors) {
    Vector steer(0.0f, 0.0f);
    int count = 0;
    for (const Boid& other : boids) {
        float dist = (boid.position - other.position).norm();
        if (dist > 0 && dist < dist_neighbors) {
            steer += (boid.position - other.position).normalize();
            count++;
        }
    }
    if (count > 0) {
        steer = steer * (1.0f / count);
    }
    return steer;
}

Vector alignment(const Boid& boid, const std::vector<Boid>& boids, float dist_neighbors) {
    Vector vmoy(0.0f, 0.0f);
    int count = 0;
    for (const Boid& other : boids) {
        float dist = (boid.position - other.position).norm();
        if (dist > 0 && dist < dist_neighbors) {
            vmoy += other.velocity;
            count++;
        }
    }
    if (count > 0) {
        vmoy = vmoy * (1.0f / count);
    }
    return boid.velocity - vmoy;
}

void updateBoids(std::vector<Boid>& boids, float dist_neighbors, float cohesion_cste, float separation_cste, float alignment_cste, float dt) {
    std::vector<Boid> old_boids = boids;

    for (Boid& boid : boids) {
        Vector cohesion_vector = cohesion(boid, old_boids, dist_neighbors);
        Vector separation_vector = separation(boid, old_boids, dist_neighbors);
        Vector alignment_vector = alignment(boid, old_boids, dist_neighbors);

        Vector acceleration = cohesion_vector*cohesion_cste  +  separation_vector*separation_cste  + alignment_vector*alignment_cste;
        boid.velocity = boid.velocity + acceleration*dt;
        if ( boid.velocity.norm() > Vmax) {
            boid.velocity = boid.velocity*Vmax/boid.velocity.norm();
        }
        boid.position = boid.position + boid.velocity*dt;
    }
}