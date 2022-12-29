# Cub3d

![C](https://img.shields.io/badge/c-%2300599C.svg?style=for-the-badge&logo=c&logoColor=white)

**Codam [42 Network] project**: code a first-person 3D representation of a 2D maze using **raycasting**. In this maze you'll be able to walk around. Inspired by the world-famous 90's game [Wolfenstein 3D](http://users.atw.hu/wolf3d/).

__Project requirements__:

- Use the **MinilibX** (basic graphical library written in C and used by 42 students).
- **Display different wall textures**, that vary depending on which compass point the wall is facing (NESW).
- Display a **sprite** instead of a wall.
- Set **floor and ceiling colours**.
- **Save** the first rendered image in .bmp format.
- The program must take a **.cub** file as a first argument, which contains the scene description.

__Skills__:

- Imperative programming
- Graphics
- Rigor
- Algorithms & AI

## Instructions :clipboard:

### Clone

`git clone https://github.com/nvanwinden/cub3D.git`

### Compile

Run `make`.

### Run

`./cub3d maps/map.cub`

|  |  |
|--|--|
|&#8592; | look left |
|&#8594; | look right |
| `W` | forward |
| `A` | left |
| `S` | backward |
| `D` | right |
| `ESC` | quit program |

### Save bitmap

`./cub3d maps/map.cub --save`

### Cub

The map must be composed of 4 possible digits:

- **0** for an empty space
- **1** for a wall
- **2** for a sprite
- **N**, **E**, **S** or **W** for the player's starting position and cardinal direction

```
111111
100101
102001
1100N1
111111
```

|  |  |
|--|--|
| **R** 1920 1080 | x render size, y render size |
| **NO** ./path_to_the_north_texture | north texture |
| **SO** ./path_to_the_south_texture | south texture |
| **WE** ./path_to_the_west_texture | west texture |
| **EA** ./path_to_the_east_texture | east texture |
| **S** ./path_to_the_sprite_texture | sprite texture |
| **F** 220,100,0 | floor color in RGB |
| **C** 225,30,0 | ceiling color in RGB |

## In action :surfing_man:

<img width="894" alt="cub3d-screenshot" src="https://user-images.githubusercontent.com/58479085/205441804-44ec8706-841f-41a4-9338-89f32a255aa1.png">


