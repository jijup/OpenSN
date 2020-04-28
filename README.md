# ProceduralNoise

Noise generation and applications using various hashing techniques.

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

  1. Perlin Noise
  2. Marble Noise
  3. Gabor Noise (in progress)
  4. Curl Noise (in progress)
  5. Worley Noise (in progress)

### Building & Running:

  1. CMake (Follow below or run within IDE - CLion or QTCreator)
      - Run  `cmake -H. Bbuild` from inside main directory.
      - Run  `cmake --build build -- -j3` from inside main directory.
      - Executable located in `/build/` folder and run with `./Perlin`.

### Other Considerations:

There are various modes that can be enabled/disabled in the `Driver.cpp` file. 

  1. Analysis Mode 
      - Outputs `<Type>Analysis_Pair<#>_Noise<#>_W<#>_H<#>.csv` of which is used to analyze results of the various functions.
        - Type: Fournier or Analysis
        - Pair: 0 - Linear, 1 - Cantor, 2 - Szudzik, 3 - Rosenberg Strong
        - Noise: 0 - Perlin, 1 - Gabor, 2 - Marble
        - W: Width 
        - H: Height
      - Ability to enable/disable amplitude and Fourier analysis.
  2. Save Noise Image Mode
      - Saves an image to .bmp.
  3. Application type
      - Renders and saves generated noise in the following applications
          - Texturing OBJ files
          - Procedural landscape (in progress)
          
### Library Requirements:
  1. [Assimp](https://www.assimp.org/)
  2. [Eigen3](https://eigen.tuxfamily.org/dox/)
  3. [OpenGP](https://github.com/OpenGP/OpenGP)
  4. [OpenGL](https://www.opengl.org/)
  5. [GLEW](http://glew.sourceforge.net/)
  6. [GLFW3](https://www.glfw.org/)
