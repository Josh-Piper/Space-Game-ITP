# Space Game 
## Description
Lost in Space is a Space Game created for Introduction to Programming at Deakin University

## Installation

Space Game requires [SplashKit](https://www.splashkit.io/) and [MSYS2](https://www.msys2.org/) to run.

Install the dependencies and and fork the repository. Once complete, navigate to the folder and enter the following commands into the msys2 Terminal.

```sh
skm new c++
skm clang++ program.cpp ./Source/GameData/*.cpp ./Source/MenuData/*.cpp ./Source/Utilities/*.cpp -o LostInSpace.exe
./LostInSpace.exe
```

## TO DO
+ Levels
+ Different Sound Effects
+ Difficulties
+ Enemies (that hurts your fuel)
+ Levelling System
+ Refactor leaderboard file to csv system
+ Input Validation for the Leaderboard Entries