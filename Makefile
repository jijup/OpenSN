CC=g++
PTH=/Library/Frameworks/SDL2.framework

all: Perlin 
	
Perlin: Driver.cpp Perlin.cpp Fractal.cpp
	$(CC) Driver.cpp Perlin.cpp Fractal.cpp -I/Library/Frameworks/SDL2.framework  -lSDL2 -o $@

clean:
	rm -f driver.exe driver

