Anim2 is a particle renderer which I made while taking a class in computational physics to have a tool that could support hardware acceleration for various different other small projects I worked on.

Please note that this project is only supported on Linux systems, and will not work on Windows as 
this tool uses the same scheme as the original Anim, using unix pipes to communicate with the user simulation instead of having the user include a static lib or create their own dll to be used by the program.

to build the project, run `make config=release`

to install run `./install.sh`

Example C file is in Examples/

To build example C simulation:
    `gcc -lm example.c -o exampleProgram`
    
then to run the program:
    `./exampleProgram | anim2`
