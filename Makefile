all:
	g++ -Wall -g solarsys.cpp planet.cpp texture_loader.cpp -o solarsys -lGL -lGLU -lglut -lSOIL