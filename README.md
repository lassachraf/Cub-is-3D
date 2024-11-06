# Cub3D Project

![](https://miro.medium.com/v2/resize:fit:7604/1*2K4EluyVP_olBM_quzq5yQ.png)

# Introduction

The Cub3D project is a 3D game development challenge from the Common Core curriculum of the 42 Network, an innovative and renowned coding school with campuses worldwide. This project introduces students to ray-casting techniques and fundamental graphics programming, with a focus on C and the MiniLibX library.

# Project Overview

### Objective

The goal of the Cub3D project is to create a basic first-person view game engine, where the player can navigate through a map using ray-casting to simulate 3D graphics. Students implement movement, rendering, and interactions within a 2D map that appears 3D through projected walls.

### Key Features

  * **Ray Casting**: Calculate the distance between the player and walls to render a realistic 3D perspective.
  * **Player Navigation**: Implement smooth player movement, wall collision, and directional controls.
  * **Texture Mapping**: Apply textures to walls for enhanced visual appeal, adding depth and realism.
  * **MiniMap**: Render a top-down view of the map for easier navigation and orientation.

### Game Elements

The project includes several core elements within the game environment:
  * **Walls** ('1') - Rendered with textures to form the boundaries of the map.
  * **Empty Spaces** ('0') - Walkable areas where the player can move.
  * **Doors** ('D') - Interactable objects that can open and close.
  * **Player** ('N', 'S', 'E', or 'W') - Represented as a character on the map with an initial facing direction.

### Implementation Details

  * **Ray-Casting Engine**: This core engine is responsible for creating a 3D projection of the 2D map, simulating depth by casting rays from the player's position.
  * **Directional Control**: Implemented using arrow keys to rotate the player's view and WASD keys to move the player.
  * **Texture Management**: Textures are loaded and mapped to the correct walls based on the player’s position and orientation.

### Compilation and Execution

To run the Cub3D project:

1. Clone the repository:
   ```bash
   git clone https://github.com/lassachraf/Cub-is-3D.git
   cd Cub-is-3D
