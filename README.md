# cub3D

A raycasting engine written in C, inspired by Wolfenstein 3D, that renders a first-person 3D view of a 2D map in real time using MiniLibX.

## About

`cub3D` parses a custom map file (`.cub`) describing walls, textures, floor/ceiling colors, and a player starting position, then renders it as a navigable 3D scene using the raycasting technique — the same core idea used in classic early-90s FPS engines. The player can move and rotate through the map with the keyboard, with walls, floors, and ceilings textured and shaded based on distance and wall orientation.

## Features

- Real-time raycasting renderer using [MiniLibX](https://github.com/42Paris/minilibx-linux)
- Custom `.cub` map file parsing and validation
- Directional wall textures (north, south, east, west)
- Configurable floor and ceiling colors
- Player movement (forward/backward/strafe) and rotation
- Collision detection against walls
- Map integrity checks (closed map, valid characters, valid player spawn)

## Controls

| Key | Action |
|---|---|
| `W` | Move forward |
| `S` | Move backward |
| `A` | Strafe left |
| `D` | Strafe right |
| `←` | Rotate camera left |
| `→` | Rotate camera right |
| `ESC` | Exit |

## Map File Format (`.cub`)

A `.cub` file defines the scene before the ASCII map itself:

```
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm

F 220,100,0
C 225,30,0

111111
100001
1000N1
111111
```

| Identifier | Meaning |
|---|---|
| `NO` / `SO` / `WE` / `EA` | Paths to wall textures for each direction |
| `F` | Floor color (RGB) |
| `C` | Ceiling color (RGB) |
| `1` | Wall |
| `0` | Empty/walkable space |
| `N` / `S` / `E` / `W` | Player start position and facing direction |

The map must be fully enclosed by walls; an unenclosed map is rejected during parsing.

## Building

```bash
make        # builds cub3D
make clean  # removes object files
make fclean # removes object files and the executable
make re     # rebuilds from scratch
```

Requires MiniLibX and its dependencies (X11, math library) to be installed/available at build time.

## Usage

```bash
./cub3D maps/example.cub
```

## Project Structure

Grouped by responsibility (from the header):

| Area | Responsibility |
|---|---|
| Parsing (`split`, `read_map`) | Reads and tokenizes the `.cub` file |
| Validation (`validate_args`, `map_parsing`, `validate_textures`) | Checks map syntax, enclosure, textures, and colors |
| Init (`init_game`, `init_window`, `init_image`) | Sets up game state and the MiniLibX window/image buffer |
| Raycasting (`raycast`, `my_mlx_pixel_put`) | Casts rays per screen column and computes wall distances |
| Drawing (`draw_wall`, `draw_ceiling_and_floor`) | Renders textured walls, floor, and ceiling per frame |
| Textures (`load_textures`, `get_dir`) | Loads and selects the correct wall texture per ray hit |
| Events (`key_press`, `key_release`, `update`) | Handles input and updates player position/angle each frame |
| Error handling (`error`, `*_free`, `clean`) | Cleans up resources and reports invalid input |

### Key structs

- **`t_game`** — top-level state: MiniLibX handles, parsed map, textures, current ray/texture info, and the player.
- **`t_player`** — position (`x`, `y`), view angle, direction/camera-plane vectors, and movement flags.
- **`t_ray`** — per-ray raycasting state (DDA step data, hit info, wall distance, draw bounds).
- **`t_texture`** / **`t_image`** — texture file paths and MiniLibX image buffer data (bpp, line length, endianness).

## Notes

- This is a learning project (42 School curriculum) focused on 2D/3D math (vectors, DDA raycasting algorithm), graphics programming, and rigorous input parsing/validation.
- Depends on a local `get_next_line` implementation (`gnl/get_next_line.h`) for reading the map file.

## License

No license specified.
