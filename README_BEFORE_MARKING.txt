Hello,

Welcome to my High Distinction 9.5H project which is cross-platform friendly!. Please read the README.md
to understand how the application works as a whole.

Please open a MINGW terminal in the folder with all of the files and contents,
to compile the program run:                               ./LostInSpace setup
to run the program run:                                   ./LostInSpace.exe

These custom commands utilise the following commands in the backend:
skm new c++ # Generate the C++ resources
skm clang++ program.cpp ./Source/GameData/Entities/*.cpp ./Source/GameData/*.cpp ./Source/MenuData/*.cpp ./Source/Utilities/*.cpp -o LostInSpace.exe # Compile the program
./LostInSpace.exe # Run the application

Therefore, you may need to compile the program the long way if issues are persisting.

Please note that I have tried to implement all of the artefacts we have been taught through this unit, this includes but is not limited to:
- Lambda Functions
- Pointers
- If/Else
- Switch-Case
- Variables
- Enumerations
- Structs

I have implemented the following advanced features as per the suggestions given throughout the unit:
- File Read-Write Validation (As per the Week 10 Lecture)
- Sorting (As per the 7.3D task sheet)
Feel free to test these validation methods by adding false information in the leaderboard file that does not follow its current format. 
Furthermore, you can delete the leaderboard or information text files and then run the game and 
it will regenerate!

Specific conventions have been following such as using @field for the comments regarding members within the structs. This convention was taught and highlighted in Task 5.2. 
However, @field does not highlight in the text editor Visual Code Studio, thus, please have consideration when marking due to these issues.

Happy marking! 


Kind regards,



Joshua Piper (219135768)
