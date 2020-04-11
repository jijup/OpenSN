# ProceduralNoise

Perlin noise generation and implementation using various hashing techniques.

SDL2 is required to compile and run for visual output (see https://www.libsdl.org/download-2.0.php).

### Pairing Function Implementations:

  1. Linear Function (implemented)
      - `y * width + x`
  2. Cantor Pairing Function (implemented)
      - `((x + y) * (x + y + 1)) / 2 + y`
  3. Szudzik Pairing Function (implemented)
      - `(x >= y) ? (x^2 + x + y) : (y^2 + x)`
  4. Rosenberg-Strong Pairing Function (implemented)
      - `(max(x, y))^2 + max(x, y) + x - y`

### Noise Implementations:

  1. Perlin noise (implemented)
  2. Gabor noise (in progress)

### Texture Implementations:

  1. Cloud texture (implemented)
  2. Marble texture (in progress)
  3. Wood texture (in progress)

### Building & Running:

  1. CMake (Follow below or run within IDE - CLion or QTCreator)
      - Run  `cmake -H. Bbuild` from inside main directory.
      - Run  `cmake --build build -- -j3` from inside main directory.
      - Executable located in `/build/` folder and run with `./Perlin`.

### Other Considerations:

There are various modes that can be enabled/disabled in the `Driver.cpp` file. 

  1. Analysis Mode (in progress)
      - Outputs `*Analysis.csv` of which is used to analyze results of the various functions.
      - Can enable amplitude and Fournier (in progress) analysis.
  2. Save Image Mode
      - Saves an image to .bmp.
      - Issue with .bmp rendering on Mac OS. 
          - Open with Photoshop/GIMP on and resave to resolve on Mac OS. 
          - Viewable without issue on Windows.
  3. Render Image Mode
      - Renders image via SDL.
  4. Multiple Iteration Mode
      - Performs multiple iterations for greater analysis datasets.
      - NOTE: This cannot be used in conjunction with the 'Render Image Mode'.



