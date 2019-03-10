#!/usr/bin/env bash

# print all cookies in the debian fortune-zh package - a test for UTF-8 handling

files="/usr/share/games/fortunes/chinese /usr/share/games/fortunes/song100 /usr/share/games/fortunes/tang300"
for i in $files; do echo $i; Debug/fortuneEcp -m $i; done 
