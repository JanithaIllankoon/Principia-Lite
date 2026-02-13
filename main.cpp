#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <cmath>

// ---------------------------------------------------------
// 1. THE PHYSICS OBJECT
// ---------------------------------------------------------
struct Particle {
    float x, y;         // Position
    float vx, vy;       // Velocity
    float radius;       // Size
    float mass;         // Heaviness

    // Constructor to make it easy to spawn particles
    Particle(float startX, float startY, float startVx, float startVy, float r, float m)
        : x(startX), y(startY), vx(startVx), vy(startVy), radius(r), mass(m) {
    }
};

// ---------------------------------------------------------
// 2. THE WORLD SETTINGS
// ---------------------------------------------------------
const float GRAVITY = 9.81f;        // Earth gravity (m/s^2)
const float TIME_STEP = 0.016f;     // 60 FPS (1.0 / 60.0)
const float GROUND_LEVEL = 10.0f;   // The floor is at y = 10 meters
const float DAMPING = 0.8f;         // Bounciness (1.0 = superball, 0.5 = wet sand)

// ---------------------------------------------------------
// 3. THE SOLVER (The "Why" Section)
// ---------------------------------------------------------
void updatePhysics(std::vector<Particle>& particles) {
    for (auto& p : particles) {
        // A. APPLY FORCES (F = ma)
        // Since Gravity is constant acceleration, we just add it.
        // If we had wind, we would do: p.vx += wind_force * TIME_STEP;
        p.vy += GRAVITY * TIME_STEP;

        // B. INTEGRATE (Semi-Implicit Euler)
        // Notice: We use the NEW velocity (p.vx, p.vy) to update position.
        p.x += p.vx * TIME_STEP;
        p.y += p.vy * TIME_STEP;

        // C. COLLISION DETECTION (Floor)
        // If the bottom of the ball (y + radius) goes past the floor...
        if (p.y + p.radius > GROUND_LEVEL) {

            // 1. Teleport it back to the surface (Constraint Solving)
            // This prevents "Tunneling" or sinking into the floor.
            p.y = GROUND_LEVEL - p.radius;

            // 2. Reflect Velocity (The Bounce)
            // We flip the Y velocity and reduce it by the damping factor.
            p.vy = -p.vy * DAMPING;

            // Optional: Stop it if it's barely moving (Sleep threshold)
            if (std::abs(p.vy) < 0.5f) p.vy = 0;
        }
    }
}

// ---------------------------------------------------------
// 4. THE MAIN LOOP
// ---------------------------------------------------------
int main() {
    // Create a world with one ball
    // Spawning at (0, 0), moving Right at 2 m/s, Radius 0.5m, Mass 1kg
    std::vector<Particle> world;
    world.emplace_back(0.0f, 0.0f, 2.0f, 0.0f, 0.5f, 1.0f);

    std::cout << "--- SIMULATION START ---" << std::endl;
    std::cout << "Time(s) \t Height(m) \t Velocity(m/s)" << std::endl;

    // Run for 300 frames (about 5 seconds)
    for (int frame = 0; frame < 300; frame++) {

        // Run the physics math
        updatePhysics(world);

        // Render (Print to console)
        // Only print every 10 frames so we don't spam the terminal
        if (frame % 10 == 0) {
            float time = frame * TIME_STEP;
            std::cout << "T=" << time << "s \t Y=" << world[0].y << "m \t Vy=" << world[0].vy << std::endl;
        }

        // Slow down the loop so we can watch it (optional, mostly for effect)
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }

    std::cout << "--- SIMULATION END ---" << std::endl;
    return 0;
}