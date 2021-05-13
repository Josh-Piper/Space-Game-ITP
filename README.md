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
+ With the levels - add planets, and more planets spawn the greater the level
+ with the end message, have it change the text dependending on what the user got. So its depending on the scenarioo
+ Have a stay clear message,
+ Have enemies that navigate towards you and attack
+ Paused Menu hooked into the Settings Menu - to allow muting and changing of the volume
+ Different messages depndent on the users score
+ A shooting powerup
+ Only allow the user to change speeds when they have certain things, and make them slow down depending on the fuel
+ Different Worlds
+ When the user clicks Play give them an option of level and difficulty
+ Fix the issue with the music