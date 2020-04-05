# ProceduralNoise

Perlin noise generation and implementation using various hashing techniques.

SDL2 is required to compile and run for visual output (see https://www.libsdl.org/download-2.0.php).

### Hashing implementations:

  1. Linear Function (implemented)
      - `y * width + x`
  2. Cantor Pairing Function (implemented)
      - `((x + y) * (x + y + 1)) / 2 + y`
  3. Szudzik Pairing Function (implemented)
      - `(x >= y) ? (x^2 + x + y) : (y^2 + x)`
  4. Rosenberg-Strong Pairing Function (implemented)
      - `(max(x, y))^2 + max(x, y) + x - y`

### Building & Running:

  1. CMake
      - Run  `cmake -H. Bbuild` from inside main directory.
      - Run  `cmake --build build -- -j3` from inside main directory.
      - Executable located in `/build/` folder and run with `./Perlin`.
  2. Makefile
      - Run `make` from inside main directory.
      - Executable locate in main directory and run with `./Perlin`.

### Other Considerations:

There is both a testing and analysis mode that can be enabled/disabled in the `Driver.cpp` file. 

  1. Testing Mode
      - Outputs hash function inputs, outputs, etc. to the command line.
  2. Analysis Mode
      - Outputs `*Analysis.csv` of which is used to analyze results of the various functions.
  3. Image Output Mode
      - Outputs an image of the Perlin noise generated.
      - Saves an image to .bmp
  4. Analysis Type
      - Performs multiple iterations with same number of octaves/lacunarity/persistence
        or performs multiple iterations with varying parameters.
      - NOTE: This cannot be used in conjunction with the 'Image Output Mode'.

      
### Noteworthy Items:

  1. BMP issue on Mac OSX
      - Output that is written to .bmp files won't open on Mac OSX native photo viewers. Adobe products
        open the .bmp fine. Works fine on Windows.
  2. Fournier Analysis 
      - Currently under development (commented out of code).


