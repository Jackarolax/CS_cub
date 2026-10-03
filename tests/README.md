# Identifier parser fixtures

These fixtures cover only the `.cub` identifiers. They intentionally contain no map lines.

## Valid

- `identifiers_boundaries.cub`: RGB values `0` and `255`.
- `identifiers_reordered.cub`: identifiers in a different order.
- `identifiers_color_spaces.cub`: spaces after color commas and extra spacing before a texture path.
- `identifiers_blank_lines.cub`: blank lines between and after identifiers.
- `identifiers_tabs_in_texture_path.cub`: a tab between a texture identifier and its path.

## Invalid

- Invalid fixtures are numbered in execution order, from `1.duplicate_no.cub` through `27.unknown_id.cub`.
- Missing one identifier, including each texture identifier and both colors.
- Duplicate `NO`, `SO`, `WE`, `EA`, `F`, or `C`.
- Missing, unreadable, or extra texture-path arguments.
- Color values that are negative, above `255`, non-numeric, decimal, empty, incomplete, or have extra components.
- Lowercase identifiers, unknown identifiers, and identifier-prefix collisions such as `NOPE` and `FOO`.

Texture paths are relative to the repository root and use `minilibx/test/open.xpm`, which is present in this checkout.