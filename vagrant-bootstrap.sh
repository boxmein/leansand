#!/usr/bin/env bash

sudo apt-get update

echo "-- Installing packages... --"
sudo apt-get install -y build-essential
sudo apt-get install -y cmake
sudo apt-get install -y libsdl2-dev
sudo apt-get install -y libsdl2-image-2.0.0
sudo apt-get install -y libsdl2-ttf-2.0.0
sudo apt-get install -y git

echo "-- Installing basic GUI for testing... --"
sudo apt-get install -y xorg
sudo apt-get install -y fluxbox

echo "-- Installing cmake 3.2 --"
wget -qO cmake.sh http://www.cmake.org/files/v3.2/cmake-3.2.2-Linux-i386.sh
yes | sudo sh cmake.sh
echo "-- Done! --"

echo "-- Adding cmake to PATH via .bashrc... --"
echo "export \$PATH=/home/vagrant/cmake-3.2.2-Linux-i386/bin:\$PATH" >> /home/vagrant/.bashrc

echo "-- Installing Lua 5.3 --"

sudo apt-get install -y libreadline-dev
wget -qO lua.tar.gz http://www.lua.org/ftp/lua-5.3.0.tar.gz
tar xzf lua.tar.gz
cd lua-5.3.0
sudo make linux install

