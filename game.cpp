#define M_PI 3.14159265358979323846

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>

// Bullet structure
struct Bullet {
    float x, y;
};

// Enemy structure
struct Enemy {
    float x, y;
};

// Comparison operators for Bullet and Enemy
bool operator==(const Bullet& lhs, const Bullet& rhs) {
    return (lhs.x == rhs.x && lhs.y == rhs.y);
}

bool operator==(const Enemy& lhs, const Enemy& rhs) {
    return (lhs.x == rhs.x && lhs.y == rhs.y);
}

// Global variables
float playerX = 0.0f, playerY = -0.8f;
int score = 0;
std::vector<Bullet> bullets;
std::vector<Enemy> enemies;
bool gameOver = false;  // Game over flag

// Function to draw a circle
void drawCircle(float x, float y, float radius) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for (int i = 0; i <= 100; ++i) {
        float angle = i * 2.0f * M_PI / 100;
        glVertex2f(x + (float)cos(angle) * radius, y + (float)sin(angle) * radius);  // Cast to float
    }
    glEnd();
}

// Function to handle key press events
void handleKeys(unsigned char key, int x, int y) {
    if (gameOver) return;  // Prevent further input after game over

    switch (key) {
    case 27:  // Escape key to quit
        exit(0);
        break;
    case ' ':
        bullets.push_back({ playerX, playerY });  // Shoot bullet
        break;
    }
    glutPostRedisplay();
}

// Function to handle special key events (arrow keys)
void handleSpecialKeys(int key, int x, int y) {
    if (gameOver) return;  // Prevent movement after game over

    switch (key) {
    case GLUT_KEY_LEFT:
        playerX -= 0.1f;  // Move left
        if (playerX < -1.0f) playerX = -1.0f;  // Prevent going out of bounds
        break;
    case GLUT_KEY_RIGHT:
        playerX += 0.1f;  // Move right
        if (playerX > 1.0f) playerX = 1.0f;  // Prevent going out of bounds
        break;
    }
    glutPostRedisplay();
}

// Function to display the game
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // Draw player
    glColor3f(1.0f, 0.0f, 0.0f);
    drawCircle(playerX, playerY, 0.05f);

    // Draw bullets
    glColor3f(0.0f, 0.0f, 1.0f);
    for (const Bullet& bullet : bullets) {
        drawCircle(bullet.x, bullet.y, 0.02f);
    }

    // Draw enemies (falling balls) only if game is not over
    if (!gameOver) {
        glColor3f(0.0f, 1.0f, 0.0f);
        for (const Enemy& enemy : enemies) {
            drawCircle(enemy.x, enemy.y, 0.05f);
        }
    }

    // Display score
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(-0.9f, 0.9f);
    char scoreText[20];
    sprintf_s(scoreText, sizeof(scoreText), "Score: %d", score);  // Use sprintf_s
    for (int i = 0; scoreText[i] != '\0'; i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, scoreText[i]);
    }

    // Display "Game Over" if the game is over
    if (gameOver) {
        glColor3f(1.0f, 0.0f, 0.0f);  // Red color for Game Over text
        glPushMatrix();
        glScalef(100.0f, 100.0f, 100.0f);
        glRasterPos2f(-0.0f, 0.0f);
        const char* gameOverText = "Game Over!";
        for (int i = 0; gameOverText[i] != '\0'; i++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, gameOverText[i]);
        }
        glPopMatrix();
    }

    glutSwapBuffers();
}

// Function to update game logic
void update(int value) {
    // Update bullet positions
    for (Bullet& bullet : bullets) {
        bullet.y += 0.05f;  // Move the bullet up
    }

    // Remove bullets that go off-screen
    bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [](Bullet& bullet) {
        return bullet.y > 1.0f;
        }), bullets.end());

    // Update enemy positions (falling down)
    for (Enemy& enemy : enemies) {
        enemy.y -= 0.005f;  // Make the enemy fall slower
    }

    // Check if any enemy hits the ground (game over condition)
    for (const Enemy& enemy : enemies) {
        if (enemy.y < -1.0f) {
            // Game over: Set the flag and stop further gameplay
            gameOver = true;
            printf("Game Over! The ball hit the ground.\n");

            // Remove all enemies when the game is over
            enemies.clear();

            break;  // Exit the loop after the game over condition
        }
    }

    // Remove enemies that go off-screen (before checking for game over)
    enemies.erase(std::remove_if(enemies.begin(), enemies.end(), [](Enemy& enemy) {
        return enemy.y < -1.0f;
        }), enemies.end());

    // Check for bullet-enemy collisions
    for (Bullet& bullet : bullets) {
        for (Enemy& enemy : enemies) {
            if (fabs(bullet.x - enemy.x) < 0.05f && fabs(bullet.y - enemy.y) < 0.05f) {
                // Collision detected: remove both the bullet and the enemy
                enemies.erase(std::remove(enemies.begin(), enemies.end(), enemy), enemies.end());
                bullets.erase(std::remove(bullets.begin(), bullets.end(), bullet), bullets.end());
                score += 1;  // Increase score by 1 per hit
                break;
            }
        }
    }

    // Spawn new enemies randomly
    if (rand() % 100 < 5 && !gameOver) {
        float enemyX = (float)(rand() % 200 - 100) / 100.0f;  // Random X position
        enemies.push_back({ enemyX, 1.0f });  // Spawn at the top of the screen
    }

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);  // Update every 16ms (approx. 60 FPS)
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("OpenGL Game");

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0f, 1.0f, -1.0f, 1.0f);

    glutDisplayFunc(display);
    glutKeyboardFunc(handleKeys);
    glutSpecialFunc(handleSpecialKeys);  // Special keys (arrow keys)
    glutTimerFunc(25, update, 0);

    glutMainLoop();

    return 0;
}
