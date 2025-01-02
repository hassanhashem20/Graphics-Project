# OpenGL Game: Shooting and Falling Balls

## Overview
This is a simple 2D OpenGL game implemented in C++ using the FreeGLUT library. The objective is to control a player character, shoot bullets, and destroy falling enemy balls before they reach the ground. If an enemy reaches the ground, the game ends.

## Features
- **Player Movement**: Move the player left and right using arrow keys.
- **Shooting Bullets**: Press the spacebar to shoot bullets upward.
- **Enemy Spawning**: Enemies randomly spawn at the top of the screen and fall downward.
- **Collision Detection**: Bullets destroy enemies upon collision.
- **Game Over Condition**: The game ends if an enemy reaches the ground.
- **Score System**: The score increases for every enemy destroyed.
- **Real-Time Graphics**: Smooth gameplay with approximately 60 frames per second (FPS).

## Prerequisites
- C++ compiler (e.g., `g++` or `clang`)
- FreeGLUT and OpenGL libraries installed on your system

## Installation
### Ubuntu/Debian
1. Update the package list:
   ```bash
   sudo apt update && sudo apt upgrade
   ```

2. Install the required libraries:
   ```bash
   sudo apt install freeglut3 freeglut3-dev libglu1-mesa-dev
   ```

### Windows
- Download and install [FreeGLUT](http://freeglut.sourceforge.net).
- Link the FreeGLUT and OpenGL libraries in your IDE or build system.

### macOS
- Install OpenGL using Homebrew:
   ```bash
   brew install freeglut
   ```

## How to Run
1. Clone this repository:
   ```bash
   git clone <repository_url>
   cd <repository_name>
   ```

2. Compile the code:
   ```bash
   g++ -o OpenGLGame main.cpp -lGL -lGLU -lglut
   ```

3. Run the game:
   ```bash
   ./OpenGLGame
   ```

## Controls
- **Arrow Keys**: Move the player left and right.
- **Spacebar**: Shoot bullets.
- **Escape (ESC)**: Quit the game.

## Screenshots
![Game Screenshot](https://via.placeholder.com/800x600.png?text=Game+Screenshot)

## Code Highlights
- **Player Movement**:
  ```cpp
  case GLUT_KEY_LEFT:
      playerX -= 0.1f;
      if (playerX < -1.0f) playerX = -1.0f;
      break;
  case GLUT_KEY_RIGHT:
      playerX += 0.1f;
      if (playerX > 1.0f) playerX = 1.0f;
      break;
  ```

- **Bullet-Enemy Collision Detection**:
  ```cpp
  for (Bullet& bullet : bullets) {
      for (Enemy& enemy : enemies) {
          if (fabs(bullet.x - enemy.x) < 0.05f && fabs(bullet.y - enemy.y) < 0.05f) {
              enemies.erase(std::remove(enemies.begin(), enemies.end(), enemy), enemies.end());
              bullets.erase(std::remove(bullets.begin(), bullets.end(), bullet), bullets.end());
              score += 1;
              break;
          }
      }
  }
  ```

## Dependencies
- [FreeGLUT](http://freeglut.sourceforge.net)
- OpenGL

## Known Issues
- The game ends abruptly when an enemy reaches the ground; consider adding a restart feature.
- Performance might vary depending on the system's graphics capabilities.

## License
This project is licensed under the MIT License. See the `LICENSE` file for details.

## Contributions
Contributions, bug reports, and feature requests are welcome! Feel free to fork this repository and submit pull requests.

---
Enjoy the game and happy coding!

