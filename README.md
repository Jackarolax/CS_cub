*This project has been created as part of the 42 curriculum by anematol, ssin.*

# cub3D

## Description

`cub3D` is a small raycasting engine written in C as part of the 42 curriculum. It turns a two-dimensional map into a first-person 3D view, using MiniLibX to open a window, draw the scene, and process keyboard input.

The project focuses on the foundations of a Wolfenstein 3D-style renderer:

- Parsing and validating `.cub` scene files.
- Reading wall texture paths and floor/ceiling RGB colors.
- Casting rays from the player to detect walls and calculate their projected height.
- Drawing the map, player, obstacles, and rendered view.
- Moving through the map while checking wall collisions.
- Moving the player and rotating the view with the keyboard.

## Requirements

- A C compiler (`cc` or `gcc`).
- `make`.
- X11 development libraries on Linux: `libX11`, `libXext`, `libbsd`, and `libm`.
- An X11 display available when running the program.

MiniLibX is built automatically from the copy in `minilibx/`. Libft is built automatically from the copy in `libft/`.

## Instructions

Build the project from the repository root:

```sh
make
```

Run the executable with a map file:

```sh
./cub3D maps/minimalist.cub
```

Useful Make targets:

```sh
make clean      # Remove project and Libft object files
make fclean     # Remove object files, libraries, and the executable
make re         # Clean and rebuild everything
make sanitize   # Rebuild with AddressSanitizer and UndefinedBehaviorSanitizer
```

### Controls

| Key | Action |
| --- | --- |
| `W` | Move forward |
| `S` | Move backward |
| `A` | Move left |
| `D` | Move right |
| Left arrow | Turn left |
| Right arrow | Turn right |
| `Esc` | Exit |

### Map format

A scene file must contain the following identifiers before the map:

```text
NO path/to/north_texture.xpm
SO path/to/south_texture.xpm
WE path/to/west_texture.xpm
EA path/to/east_texture.xpm
F 220,100,10
C 225,30,2
```

The map uses `1` for walls, `0` for walkable space, and exactly one of `N`, `S`, `E`, or `W` for the player's starting position and direction. The playable area must be enclosed by walls. Example maps are available in [`maps/`](maps/).

## Project structure

- [`src/parser/`](src/parser/) parses identifiers, colors, and map content.
- [`src/raycasting.c`](src/raycasting.c) calculates ray directions and wall collisions.
- [`src/draw.c`](src/draw.c) draws the scene and minimap elements.
- [`src/movement.c`](src/movement.c) and [`src/movement_collision_checking.c`](src/movement_collision_checking.c) handle movement and collision checks.
- [`minilibx/`](minilibx/) provides the graphical window and input layer.
- [`libft/`](libft/) provides the project's C utility library.

## Resources

- [42 cub3D subject](https://cdn.intra.42.fr/pdf/pdf/96026/en.subject.pdf) - project requirements and expected scene format.
- [Lodev's Raycasting Tutorial](https://lodev.org/cgtutor/raycasting.html) - explanation of grid raycasting and projected wall slices.
- [MiniLibX documentation](https://harm-smits.github.io/42docs/libs/minilibx) - window creation, events, images, and drawing.
- [X11 keysym definitions](https://www.x.org/releases/current/doc/man/man7/X11_Keysym.7.xhtml) - keyboard constants used on Linux.
- [Linux man-pages](https://man7.org/linux/man-pages/) - reference documentation for Linux system calls, C library functions, file descriptors, and mathematical functions used by the project.
- [42 Norm](https://github.com/42School/norminette) - coding-style reference used by the project.

### AI usage

AI was used as a documentation assistant for this repository. It helped inspect the existing Makefile and source files, summarize the build commands, and draft this README. It was not used to generate the renderer, parser, movement, collision, or MiniLibX implementation.
