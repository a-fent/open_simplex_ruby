# require "bundler/gem_tasks"
require "rake/extensiontask"

# file "ext/OpenSimplex_wrap.cxx" => "ext/OpenSimplex.i" do
#   sh "swig -c++ -ruby ext/OpenSimplex.i"
# end

# file "ext/OpenSimplex.so" => "ext/OpenSimplex.cxx" do
#   cd "ext" do 
#     sh "ruby extconf.rb"
#     sh "make"
#   end
# end

# file "lib/open_simplex/OpenSimplex.so" => "ext/OpenSimplex.so" do
#   FileUtils::copy("ext/OpenSimplex.so", "lib/open_simplex/OpenSimplex.so")
# end

gemspec = Gem::Specification.load('open_simplex.gemspec')

Rake::ExtensionTask.new do |ext|
  ext.name = 'open_simplex'
  ext.ext_dir = 'ext/open_simplex'
  ext.source_pattern = "*.{cxx,h}"
end

task :default => ["lib/open_simplex/OpenSimplex.so"]
