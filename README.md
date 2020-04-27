# ProceduralNoise

Noise generation, implementation and application using various hashing techniques.

### Pairing Function Implementations:

  1. Linear Function 
      - `y * width + x`
  2. Cantor Pairing Function
      - `((x + y) * (x + y + 1)) / 2 + y`
  3. Szudzik Pairing Function 
      - `(x >= y) ? (x^2 + x + y) : (y^2 + x)`
  4. Rosenberg-Strong Pairing Function 
      - `(max(x, y))^2 + max(x, y) + x - y`

### Noise Implementations:

  1. Perlin noise
  2. Gabor noise (in progress)
  3. Marble Noise via Perlin Noise 

### Building & Running:

  1. CMake (Follow below or run within IDE - CLion or QTCreator)
      - Run  `cmake -H. Bbuild` from inside main directory.
      - Run  `cmake --build build -- -j3` from inside main directory.
      - Executable located in `/build/` folder and run with `./Perlin`.

### Other Considerations:

There are various modes that can be enabled/disabled in the `Driver.cpp` file. 

  1. Analysis Mode 
      - Outputs `<AnalysisType>Analysis.csv` of which is used to analyze results of the various functions.
      - Can enable amplitude and Fournier analysis (in progress).
  2. Save Noise Image Mode
      - Saves an image to .bmp.
      - Issue with .bmp rendering on Mac OS. 
          - Open with Photoshop/GIMP on and re-save to resolve on Mac OS. 
          - Viewable without issue on Windows.
  3. Render Noise Image Mode
      - Renders image via SDL.
  4. Application type
      - Renders and saves generated noise in the following applications
          - Texturing vase (and other OBJ files)
          - Procedural landscape (in progress)
          
### Library Requirements:
  1. SDL2 (soon to be removed)
  2. ASSIMP
  3. EIGEN3
  4. OPENGP
  5. OPENGL
  6. GLEW
  7. GLFW3 
