#!/usr/bin/bash

# Detect package manager
if command -v apt &> /dev/null; then
    sudo apt update
    sudo apt install -y build-essential cmake git libgl1-mesa-dev libglu1-mesa-dev libx11-dev libxcursor-dev libxrandr-dev libxi-dev libxinerama-dev libxxf86vm-dev libxkbcommon-dev dos2unix xvfb zsync
elif command -v pacman &> /dev/null; then
    pacman -Syu --noconfirm
    pacman -S --noconfirm base-devel cmake git mesa glu libx11 libxcursor libxrandr libxi libxinerama libxxf86vm libxkbcommon dos2unix xvfb zsync
else
    echo "Unsupported package manager. Please install raylib dependencies manually."
    exit 1
fi

echo "Raylib dependencies installation completed."
