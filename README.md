# Cub3d

**Codam [42 Network] project**: first-person 3D representation of a 2D maze using **raycasting**. Inspired by the world-famous 90's game **Wolfenstein**.

**Project requirements**:

- Use the **MinilibX** (basic graphical library written in C and used by 42 students).
- **Display different wall textures**, that vary depending on which compass point the wall is facing (NESW).
- Display a **sprite** instead of a wall.
- Set **floor and ceiling colours**.
- **Save** the first rendered image in .bmp format.
- Parse a config file in which you can set 

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


https://user-images.githubusercontent.com/58479085/195980815-13221a4b-ea1b-4012-b518-9d6a4cb65b09.mov




