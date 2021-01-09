lib = File.expand_path("../lib", __FILE__)
$LOAD_PATH.unshift(lib) unless $LOAD_PATH.include?(lib)
require "open_simplex"

Gem::Specification.new do |spec|
  spec.name          = "open_simplex"
  spec.version       = OpenSimplex::VERSION
  spec.authors       = ["Alex Fenton"]
  spec.email         = ["alex@pressure.to"]

  spec.summary       = %q{Open Simplex noise generation.}
  spec.description   = %q{This C extension for Ruby provides a fast way of producing consistent
noise using the OpenSimplex algorithm. Consistent noise is comprised of
random values at points across one or more dimensions, in which however
close points have close values. Depending on the specific noise
function, this produces the effect of ridges, gradients and the like.
Such distributions may be useful for procedural generation, for textures
in graphics, or anywhere where a reproducible random value for one or
more coordinates is needed.

OpenSimplex is a patent-unencumbered implementation of the Simplex
algorithm, which is itself an improved version of Perlin noise. Simplex
noise produces similar textures to Perlin noise, but is computationally
simpler and avoids some known artifacts that Perlin noise can produce.}
  spec.homepage      = "https://github.com/a-fent/open_simplex_ruby"
  spec.license       = "Unlicense"

  # Prevent pushing this gem to RubyGems.org. To allow pushes either set
  # the 'allowed_push_host' to allow pushing to a single host or delete
  # this section to allow pushing to any host.
  if spec.respond_to?(:metadata)
    spec.metadata["allowed_push_host"] =
      "TODO: Set to 'http://mygemserver.com'"
  else
    raise "RubyGems 2.0 or newer is required to protect against " \
          "public gem pushes."
  end

  spec.files =
    [ "UNLICENCE", "README.org" ] +
    Dir["lib/**/*.rb"] +
    Dir["ext/**/*"] +
    Dir["test/**/*"] +
    Dir["samples/**/*"] 
  spec.extensions = [ "ext/open_simplex/extconf.rb" ]
  
  spec.require_paths = ["lib"]

  spec.add_development_dependency "rake", "~> 12.0.0"
  spec.add_development_dependency "rake-compiler", "1.0.0"
end
