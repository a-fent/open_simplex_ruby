# This produces pngs to demonstrate the different variants of simplex
# noise supported by the library

$: << '../lib'
require 'open_simplex'
require 'mini_magick'

HEIGHT = 250
WIDTH  = 250
SCALE  = 100

# Seed for reproducible random values
OpenSimplex::seed(5)

# Generate an image file by passing a block which should accept x and y
# values and return a pixel value between 0 (black) and 255 (white)
def noise_image(image_file)
  pixels = Array.new(HEIGHT) do | y |
    Array.new(WIDTH) do | x |
      val = yield( x.fdiv(SCALE), y.fdiv(SCALE) )
      Array.new(3, val)
    end
  end
  image = MiniMagick::Image.get_image_from_pixels(pixels, [WIDTH,HEIGHT],
                                                  'rgb', 8, 'png')
  image.write(image_file)
end

noise_image("simplex.png") do | x, y |
  val = OpenSimplex::simplex(x, y)
  # Simplex noise ranges over -1..1
  (val + 1) * 128 
end

noise_image("simplex_tiled.png") do | x, y |
  val = OpenSimplex::simplex_periodic(x, y, WIDTH.fdiv(SCALE), HEIGHT.fdiv(SCALE))
  # Simplex noise ranges over -1..1
  (val + 1) * 128 
end

noise_image("ridged.png") do | x, y |
  val = OpenSimplex::ridged(x, y)
  # Ridged noise ranges 0..1
  val * 255
end

noise_image("worley.png") do | x, y |
  val = OpenSimplex::worley(x, y)
  val * 255
end

noise_image("simplex_fractal.png") do | x, y |
  val = OpenSimplex::fbm(x, y)
  (val + 1) * 128 
end

noise_image("simplex_fractal_periodic.png") do | x, y |
  val = OpenSimplex::fbm_periodic(x, y, WIDTH.fdiv(SCALE), HEIGHT.fdiv(SCALE))
  (val + 1) * 128 
end

noise_image("worley_smooth.png") do | x, y |
  val = OpenSimplex::worley_smooth(x, y, falloff: 0.1)
  val * 255
end

