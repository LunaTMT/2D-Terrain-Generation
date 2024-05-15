#!/bin/bash

# Compile main.cpp and game.cpp along with other source files
g++ -fdiagnostics-color=always -g src/main.cpp src/entities/*.cpp src/commands/*.cpp src/utilities/*.cpp -o main -Iinclude -Iinclude/entities -Iinclude/commands -Iinclude/utilities -lsfml-graphics -lsfml-window -lsfml-system

# Check if compilation was successful
if [ $? -eq 0 ]; then
    echo "Compilation successful."
    ./main
else
    echo "Compilation failed."
fi
