require 'mkmf'
have_library('stdc++')
$CXXFLAGS += " -std=gnu++17"

create_makefile('open_simplex')
