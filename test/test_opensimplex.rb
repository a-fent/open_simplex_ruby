require 'minitest/autorun'
$: << '../lib'
require 'open_simplex'

class TestOpenSimplex < MiniTest::Test
  def test_simplex
    o = OpenSimplex::simplex(0.2)
    assert_kind_of(Float, o)
    assert(o > -1)
    assert(o < 1)
    o = OpenSimplex::simplex(0.3, 0.5)
    assert_kind_of(Float, o)
    assert(o > -1)
    assert(o < 1)
    o = OpenSimplex::simplex(0.1, 0.7, 1.2)
    assert_kind_of(Float, o)
    assert(o > -1)
    assert(o < 1)
    o = OpenSimplex::simplex(1.5, 21, 0.2, -0.5)
    assert_kind_of(Float, o)
    assert(o > -1)
    assert(o < 1)
  end
  
  def test_ridged
    o = OpenSimplex::ridged(0.2)
    assert_kind_of(Float, o)
    assert(o > 0)
    assert(o < 1)
    o = OpenSimplex::ridged(0.3, 0.5)
    assert_kind_of(Float, o)
    assert(o > 0)
    assert(o < 1)
    o = OpenSimplex::ridged(0.1, 0.7, 1.2)
    assert_kind_of(Float, o)
    assert(o > 0)
    assert(o < 1)
    o = OpenSimplex::ridged(1.5, 21, 0.2, -0.5)
    assert_kind_of(Float, o)
    assert(o > 0)
    assert(o < 1)
  end
  
  def test_worley
    o = OpenSimplex::worley(0.3, 0.5)
    assert_kind_of(Float, o)
    assert(o > -1)
    assert(o < 1)
    o = OpenSimplex::worley(0.1, 0.7, 1.2)
    assert_kind_of(Float, o)
    assert(o > -1)
    assert(o < 1)
  end
  
  def test_periodic
    o1 = OpenSimplex::simplex_periodic(0.2, 0.5, 3, 4)
    o2 = OpenSimplex::simplex_periodic(3.2, 0.5, 3, 4)
    p o1
    assert_equal(o1, o2)
    o1 = OpenSimplex::simplex(0.2, 0.5, 3, 4)
    o2 = OpenSimplex::simplex(3.2, 0.5, 3, 4)
    refute(o1 == o2)
  end
end
