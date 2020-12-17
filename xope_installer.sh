#!/bin/bash

echo "Welcome to XOPE Alpha 0.4.2 installer"
echo "Installing dependencies"
sudo apt-get update -y
sudo apt-get install -y nasm
echo "Dependencies installed succcessfully"
echo "Installing xope"
make compile
echo "export PATH=\$PATH:$(pwd)" >> ~/.bashrc
echo "Installation Successful"
echo ""
echo ""
echo "NOTICE:"
echo "You must restart the terminal to start using XOPE"

