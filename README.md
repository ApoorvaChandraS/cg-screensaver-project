CG Project - IT255
(Concept Screensaver using Basic Algorithms)
==============
Authors: Apoorva Chandra S, Dilip Mallya, R Kaushik, Kartik Sreenivasan, S Avinash
--------------

**Info:**
The platform we are using is OpenGL but we are implementing even the most basic primitives such as lines, polygons using our own functions and libraries. All these programs are written in C and compiled by the gcc compiler on Linux
platform.

The file OpeningScreen.c is the opening screen that you view when you execute the program. The program is run using the script exec (./exec filename).


**To compile and run:**
On Linux-
give execute permissions to the script named 'exec' ,
- sudo chmod ugo+x exec
exec contains the following shell commands
	gcc  $@ -lglut -lGL -lGLU -lX11 -lm > /dev/null
	./a.out 
compile and run using,
- ./exec OpeningScreen.c

	gcc  $@ -lglut -lGL -lGLU -lX11 -lm > /dev/null
	./a.out 
    