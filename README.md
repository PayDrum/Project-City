# Project-City

The project aims to simulate a living city, with one million citizens in a form of a game(not necessarily). The scope of the project has not been set yet, but current plans are to implement terraforming, tools for building the city(roads, zones, water, power, etc), and daily citizen activities. The lack of a set scope is to due to the unknown hardware limitations and optimization ceilings at this point of the project; however, heavy use of multithreading and in an extreme case, offloading some calculations(such as pathfinding) to the GPU is planned.

The project does not prioritize the graphics and most are developed in a simplistic manner, unless the aims change in the future. 
The project is developed in a platform independant manner for the time being and is planned to continue for the forseeable future. Building on other platforms than Windows have not been tested yet but should not be too difficult.

External libraries currently in use:
SDL2 is for handling the window management, controls and sounds.
GlEW.

Current roadmap:
1. Creating the basic scene with an ortographic camera. (completed)
2. Creating the ground floor, with the ability to add terraforming capibility later on.(completed)
3. Creating a grid for the map (completed)
4. implementing a usable camera system with zooming and panning(in progress)
5. developing a method(or using an extrnal libraries), for loading external models (in progress)
6. Adding a HUD and basic controls (in progress)
7. Creating the foundation and the functionality for adding roads
8. Adding zones(commercial,residential,industrial).
9. Adding a ticking system for the population, populating the city.
10. Adding the first pathfinding system for the citizens to go from home to work every day, based on the available roads.

