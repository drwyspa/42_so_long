![42_so_long](https://github.com/user-attachments/assets/883e15c1-c871-4065-8156-4b82a1950751)

Would you like to play a little bit?

First, you need MinilibX library. You can do this two ways:

1. Easy way: just type "make all" command to download MinilibX and install it. Plus you'll compile rest of game guts.
2. Hard way: you can also download library and put it in to "mlx" folder inside game folder. Then install it. After that, you can type "make" or "make all" command (if you fill mlx folder by yourself, we can handle that with Makefile, no worries).

To run the game, just type:

./so_long ./maps/themapyouwanttoplay.ber

Not all the maps are correct. We need bad ones to test error handling ofcourse. They are some rules for the maps:

1. The map has to be constructed with 3 components: walls, collectibles, and free space.
2. The map can be composed of only these 5 characters:
   - 0 for an empty space,
   - 1 for a wall,
   - C for a collectible,
   - E for a map exit,
   - P for the player’s starting position.
3. The map must contain 1 exit, at least 1 collectible, and 1 starting position to be valid.
4. If the map contains a duplicates characters (exit/start), we should display an error message.
5. The map must be rectangular.
6. The map must be closed/surrounded by walls. If it’s not, the program must return an error.
7. There have to be a valid path in the map.

Yo know what is also cool? You can build your own map, according to above rules. For example:

![carbon (2)](https://github.com/user-attachments/assets/0d3cdb20-0b43-4ba7-8a31-afc4c503a1c2)

That's it! Have fun and go ahead, make your own maps and maybe an assets also?
