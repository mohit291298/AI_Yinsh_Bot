
#!/bin/bash

## Compile our two program files
g++ -std=c++11 -Ofast -march=native -o code my_player.cpp Boardclass.cpp Node.cpp