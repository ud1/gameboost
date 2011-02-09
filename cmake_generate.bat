@echo off
mkdir .build
cd .build
cmake -G "Visual Studio 10 Win64" ..
@rem cmake -G "Visual Studio 10" ..
