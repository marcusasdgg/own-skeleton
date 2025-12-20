This module adds basic font support to print to the screen. probably should make font support layer on vga here.

Basic support plan:
Use a prebuilt font that each glyph takes 8x8 space, pull it from web and hardcode it into an array and draw accordingly.

structure of tty module:
- intialisation function which takes x,y and width, length variables, size is the size of terminal in glyphs, and x/y are where the top left corner starts.
- renderCharacter function which takes relative x and y positions i.e. glyph position and character to draw which it does in the terminal.
- ttyputchar function which puts character on the current x and y of the cursor which is stored in our class.
- ttyputstr function which puts string onto the character with basic wrapping support.

- if content reaches bottom of the bounding box, the top line gets removed and everything shoves up by 1 line.
