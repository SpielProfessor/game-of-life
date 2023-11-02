# game of life
A conway's game of life simple version written in C with the ncurses library. 
## rules
```
1: live cell with 2-3 neighbours lives to next round
2: live cell with <2 Neighbours dies
3: live cell with over 3 neighbours dies
4: dead cell with 3 neighbours becomes live
```
## compiling
To compile the program with GCC, run

```
gcc gameoflife.c -o gameoflife -lncurses
```
and then to execute it on linux/*nix
```./gameoflife```
and on windows ```gameoflife.exe```
