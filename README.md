# ProceduralNoise

Perlin noise generation and implementation using various hashing techniques.

SDL2 is required to compile and run for visual output (see https://www.libsdl.org/download-2.0.php).

Hashing implementations:

  1. Linear Function (implemented)
      - `y * width + x`
  2. Cantor Pairing Function (implemented - one way)
      - `((x + y) * (x + y + 1)) / 2 + y`
  3. Szudzik Pairing Function (coming soon)
      - `(x > y) ? (x^2 + x + y) : (y^2 + x)`
