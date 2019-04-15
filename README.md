# Raytracer II

* Epitech 1st year group project (4 ppl).
* Project Written in C using csfml librairy.

## Get the project

1. Clone or download repository
2. Get the dependancies ``flex and csfml``
3. Build the project using the Makefile (`make`)

## Test the project
* launch the project using the config file:
    `./Raytracer2 <path-to-config>`

## Example Config
```
#!raytracer2
eye -800 0 30
sphere 50 color 200 200 200 translate 200 200 -100 reflection 1
sphere 50 color 200 200 200 translate 200 200 200 reflection 1
sphere 50 color 200 200 200 translate 200 -200 -100 reflection 1
sphere 50 color 200 200 200 translate 200 -200 200 reflection 1
sphere 50 color 200 200 200 translate -200 200 -100 reflection 1
sphere 50 color 200 200 200 translate -200 200 200 reflection 1
sphere 50 color 200 200 200 translate -200 -200 -100 reflection 1
sphere 50 color 200 200 200 translate -200 -200 200 reflection 1
light 100 100 150
light -100 100 150
light 100 -100 150
light -100 -100 150
cylinder 30 translate 200 200 0 reflection 0.1
cylinder 30 translate 200 -200 0 reflection 0.1
cylinder 30 translate -200 200 0 reflection 0.1
cylinder 30 translate -200 -200 0 reflection 0.1
plane 0 translate 0 0 -200 color 255 255 255 damier 50 min 500 -1 -1
plane 0 translate 0 0 300 color 38 211 210 min -500 -500 -1 max 500 500 -1 damier 100
```


## Who worked on the project ?

Théo Ferreira, James Faure, Paul Varé and Julien ALDON.