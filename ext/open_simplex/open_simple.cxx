#include <time.h>
#include "ruby.h"
#include "math.h"
#include "Simplex.h"

// Set seed, affects all future calls
static VALUE osimplex_seed(VALUE self, VALUE seed_i) {
  Simplex::seed( NUM2INT(seed_i) );
  return Qnil;
}

// Simplex Noise
static VALUE osimplex_noise_value(int argc, VALUE* argv, VALUE self)
{
  float val;
  if (argc == 1) {
	val = Simplex::noise(NUM2DBL(argv[0]));  }
  else if (argc == 2) {
	val = Simplex::noise(glm::vec2(NUM2DBL(argv[0]), NUM2DBL(argv[1]))); }
  else if (argc == 3) {
	val = Simplex::noise(glm::vec3(NUM2DBL(argv[0]), NUM2DBL(argv[1]),
								   NUM2DBL(argv[2]))); }
  else if (argc == 4) {
	val = Simplex::noise(glm::vec4(NUM2DBL(argv[0]), NUM2DBL(argv[1]),
								   NUM2DBL(argv[2]), NUM2DBL(argv[3]))); }
  else {
	rb_raise(rb_eArgError, "Wrong number of arguments");  }
  return DBL2NUM(val);
}

// Ridged noise
static VALUE osimplex_ridgednoise_value(int argc, VALUE* argv, VALUE self)
{
  float val;
  if (argc == 1) {
	val = Simplex::ridgedNoise(NUM2DBL(argv[0]));  }
  else if (argc == 2) {  
	val = Simplex::ridgedNoise(glm::vec2(NUM2DBL(argv[0]), NUM2DBL(argv[1]))); }
  else if (argc == 3) {
	val = Simplex::ridgedNoise(glm::vec3(NUM2DBL(argv[0]), NUM2DBL(argv[1]),
								   NUM2DBL(argv[2]))); }
  else if (argc == 4) {
	val = Simplex::ridgedNoise(glm::vec4(NUM2DBL(argv[0]), NUM2DBL(argv[1]),
								   NUM2DBL(argv[2]), NUM2DBL(argv[3]))); }
  else {
	rb_raise(rb_eArgError, "Wrong number of arguments");  }
  return DBL2NUM(val);
}


// Worley noise
static VALUE osimplex_worleynoise_value(int argc, VALUE* argv, VALUE self)
{
  float val;
  if (argc == 2) {  
	val = Simplex::worleyNoise(glm::vec2(NUM2DBL(argv[0]), NUM2DBL(argv[1]))); }
  else if (argc == 3) {
	val = Simplex::worleyNoise(glm::vec3(NUM2DBL(argv[0]), NUM2DBL(argv[1]),
								   NUM2DBL(argv[2]))); }
  else {
	rb_raise(rb_eArgError, "Wrong number of arguments, should be 2-3");  }
  return DBL2NUM(val);
}


// static VALUE osimplex_curlnoise_value(int argc, VALUE* argv, VALUE self)
// {
//   float val;
//   if (argc == 1) {
// 	val = Simplex::curlNoise(NUM2DBL(argv[0]));
//   }
//   else if (argc == 2) {
// 	val = Simplex::curlNoise(glm::vec2(NUM2DBL(argv[0]), NUM2DBL(argv[1])));
//   }
//   else if (argc == 3) {
// 	val = Simplex::curlNoise(glm::vec3(NUM2DBL(argv[0]), NUM2DBL(argv[1]),
// 								   NUM2DBL(argv[2])));
//   }
//   else if (argc == 4) {
// 	val = Simplex::curlNoise(glm::vec4(NUM2DBL(argv[0]), NUM2DBL(argv[1]),
// 								   NUM2DBL(argv[2]), NUM2DBL(argv[2])));
//   }
//   else {
// 	rb_raise(rb_eArgError, "Wrong number of arguments");
//   }
//   return DBL2NUM(val);
// }

static VALUE opsimp_2d_periodic(VALUE self, VALUE x, VALUE y, VALUE size_x, VALUE size_y)
{

  double r_x = NUM2DBL(x) / NUM2DBL(size_x);
  double r_y = NUM2DBL(y) / NUM2DBL(size_y);

  double dx = r_x * 2 * M_PI;
  double dy = r_y * 2 * M_PI;

  double a = cos(dx) * (2*M_PI);
  double b = cos(dy) * (2*M_PI);
  double c = sin(dx) * (2*M_PI);
  double d = sin(dy) * (2*M_PI);

  return DBL2NUM(Simplex::noise(glm::vec4(a, b, c, d)));
}

static VALUE opsimp_fbm(int argc, VALUE* argv, VALUE self)
{
  VALUE dim1, dim2, dim3, dim4;
  VALUE opts;
  rb_scan_args(argc, argv, "13:", &dim1, &dim2, &dim3, &dim4, &opts);

  if (NIL_P(opts)) opts = rb_hash_new();
  VALUE octa_r = rb_hash_aref(opts, ID2SYM(rb_intern("octaves")));
  uint8_t octa  = NIL_P(octa_r) ? 4 : NUM2UINT(octa_r);
  VALUE lacu_r = rb_hash_aref(opts, ID2SYM(rb_intern("lacunarity")));
  float lacu  = NIL_P(lacu_r) ? 2.0f : NUM2DBL(lacu_r);
  VALUE gain_r = rb_hash_aref(opts, ID2SYM(rb_intern("gain")));
  float gain  = NIL_P(gain_r) ? 0.5f : NUM2DBL(gain_r);
  float val;
  if ( ! NIL_P(dim4) )  {
	val = Simplex::fBm(glm::vec4(NUM2DBL(dim1), NUM2DBL(dim2),
								 NUM2DBL(dim3), NUM2DBL(dim4) ),
					   octa, lacu, gain);
  }
  else if ( ! NIL_P(dim3) ) {
	val = Simplex::fBm(glm::vec3(NUM2DBL(dim1), NUM2DBL(dim2),
								 NUM2DBL(dim3) ),
					   octa, lacu, gain);

  }
  else if (! NIL_P(dim2) ) {
	val = Simplex::fBm(glm::vec2(NUM2DBL(dim1), NUM2DBL(dim2)),
					   octa, lacu, gain);
  }
  else {
	val = Simplex::fBm(NUM2DBL(dim1), octa, lacu, gain);
  }
  return DBL2NUM(val);
}

static VALUE opsimp_worley_fbm(int argc, VALUE* argv, VALUE self)
{
  VALUE dim1, dim2, dim3, dim4;
  VALUE opts;
  rb_scan_args(argc, argv, "21:", &dim1, &dim2, &dim3, &opts);

  if (NIL_P(opts)) opts = rb_hash_new();
  VALUE octa_r = rb_hash_aref(opts, ID2SYM(rb_intern("octaves")));
  uint8_t octa  = NIL_P(octa_r) ? 4 : NUM2UINT(octa_r);
  VALUE lacu_r = rb_hash_aref(opts, ID2SYM(rb_intern("lacunarity")));
  float lacu  = NIL_P(lacu_r) ? 2.0f : NUM2DBL(lacu_r);
  VALUE gain_r = rb_hash_aref(opts, ID2SYM(rb_intern("gain")));
  float gain  = NIL_P(gain_r) ? 0.5f : NUM2DBL(gain_r);
  float val;
  if ( ! NIL_P(dim3) ) {
	val = Simplex::worleyfBm(glm::vec3(NUM2DBL(dim1), NUM2DBL(dim2),
								 NUM2DBL(dim3) ),
					   octa, lacu, gain);

  }
  else {
	val = Simplex::worleyfBm(glm::vec2(NUM2DBL(dim1), NUM2DBL(dim2)),
					   octa, lacu, gain);
  }
  return DBL2NUM(val);
}

  
  
// static VALUE opsimp_2d_periodic_value(VALUE self, VALUE x, VALUE y,
// 									  VALUE size_x, VALUE size_y)
// {
//   struct osn_context *ctx;
//   Data_Get_Struct(self, struct osn_context, ctx);

//   double noise = opsimp_2d_periodic(ctx,
// 									NUM2DBL(x), NUM2DBL(y),
// 									NUM2DBL(size_x), NUM2DBL(size_y));
//   return DBL2NUM(noise);
// }

extern "C" void Init_open_simplex() {
  VALUE cOpenSimplex = rb_define_class("OpenSimplex", rb_cObject);
  rb_define_singleton_method(cOpenSimplex, "seed", &osimplex_seed, 1);
  rb_define_singleton_method(cOpenSimplex, "simplex", &osimplex_noise_value, -1);
  rb_define_method(cOpenSimplex, "simplex", &osimplex_noise_value, -1);
  rb_define_singleton_method(cOpenSimplex, "ridged", &osimplex_ridgednoise_value, -1);
  rb_define_method(cOpenSimplex, "ridged", &osimplex_ridgednoise_value, -1);
  rb_define_singleton_method(cOpenSimplex, "worley", &osimplex_worleynoise_value, -1);
  rb_define_method(cOpenSimplex, "worley", &osimplex_worleynoise_value, -1);
  // rb_define_method(cOpenSimplex, "noise_3d", &opsimp_3d_value, 3);
  // rb_define_method(cOpenSimplex, "noise_4d", &opsimp_4d_value, 4);
  rb_define_singleton_method(cOpenSimplex, "simplex_periodic", &opsimp_2d_periodic, 4);
  rb_define_singleton_method(cOpenSimplex, "fbm", &opsimp_fbm, -1);
}
