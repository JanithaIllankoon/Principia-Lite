#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <cmath>
#include <string>

// ---------------------------------------------------------
// 1. SETTINGS & CONSTANTS
// ---------------------------------------------------------
const int SCREEN_WIDTH = 40;     // Console width (columns)
const int SCREEN_HEIGHT = 20;    // Console height (rows)
const float GRAVITY = 9.81f;
const float TIME_STEP = 0.033f;  // ~30 FPS (slower for ASCII)

// ---------------------------------------------------------
// 2. THE PHYSICS OBJECT
// ---------------------------------------------------------
struct Particle {
    float x, y;
    float vx, vy;

    void update() {
        vy += GRAVITY * TIME_STEP;
        x += vx * TIME_STEP;
        y += vy * TIME_STEP;

        // Floor Collision (Bounce)
        if (y >= SCREEN_HEIGHT - 1) {
            y = SCREEN_HEIGHT - 1;
            vy = -vy * 0.8f; // Lose 20% energy
        }

        // Wall Collisions (Left/Right)
        if (x <= 0) {
            x = 0;
            vx = -vx * 0.8f;
        }
        if (x >= SCREEN_WIDTH - 1) {
            x = SCREEN_WIDTH - 1;
            vx = -vx * 0.8f;
        }
    }
};

// ---------------------------------------------------------
// 3. THE RENDERER
// ---------------------------------------------------------
void draw(const Particle& p) {
    // A. Clear the screen (Windows specific command)
    system("cls");

    // B. Create a buffer (a blank screen of spaces)
    std::vector<std::string> screen(SCREEN_HEIGHT, std::string(SCREEN_WIDTH, ' '));

    // C. Draw the Floor
    for (int i = 0; i < SCREEN_WIDTH; i++) screen[SCREEN_HEIGHT - 1][i] = '#';

    // D. Place the Ball
    // We have to cast float (5.4) to int (5) to pick a grid slot
    int px = (int)p.x;
    int py = (int)p.y;

    // Boundary check to prevent crashing if ball goes off screen
    if (px >= 0 && px < SCREEN_WIDTH && py >= 0 && py < SCREEN_HEIGHT) {
        screen[py][px] = 'O';
    }

    // E. Print the frame
    for (const auto& row : screen) {
        std::cout << row << "\n";
    }

    std::cout << "Pos: (" << p.x << ", " << p.y << ")" << std::endl;
}

// ---------------------------------------------------------
// 4. MAIN LOOP
// ---------------------------------------------------------
int main() {
    // Spawn ball in middle of screen
    Particle ball = { 5.0f, 2.0f, 15.0f, 0.0f }; // x, y, vx, vy

    while (true) {
        // 1. Calculate
        ball.update();

        // 2. Draw
        draw(ball);

        // 3. Wait
        std::this_thread::sleep_for(std::chrono::milliseconds(33));
    }

    return 0;
}