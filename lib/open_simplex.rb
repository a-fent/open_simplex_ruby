require_relative 'open_simplex.so'


class OpenSimplex
  require_relative 'open_simplex/version'
  class << self
    alias :cellular :worley
    alias :cellular_fractal :worley_fractal
    alias :simplex_fractal :fbm
  end
end
