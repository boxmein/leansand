#!/usr/bin/env bash

sudo apt-get update
echo "-- Installing packages... --"
sudo apt-get install -y build-essential cmake libsdl2 libsdl2-dev libsdl2-image-2.0.0 libsdl2-ttf-2.0.0 git
echo "-- Installing basic GUI for testing... --"
sudo apt-get install -y xorg fluxbox
echo "-- Installing cmake 3.2 --"
wget -qO cmake.sh http://www.cmake.org/files/v3.2/cmake-3.2.2-Linux-i386.sh
yes | sudo sh cmake.sh
echo "-- Done! --"
