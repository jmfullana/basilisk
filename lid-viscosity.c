#include "grid/multigrid.h"
#include "navier-stokes/centered.h"
#include "tracer.h"

scalar f[];
scalar * tracers = {f};
face vector muv[] ;

int main()
{
  // coordinates of lower-left corner
  //origin (-0.5, -0.5);
  // number of grid points
  init_grid(64);
  // viscosity

  mu = muv;

  // maximum timestep
  DT = 0.1 ;
  // CFL number
  CFL = 0.8;

  run();

}

// boundary
u.t[top] = dirichlet(1.);
u.t[bottom] = dirichlet(0);
u.t[left]   = dirichlet(0);
u.t[right]  = dirichlet(0);


event init (i = 0) 
{
  foreach()
    u.x[] = 0.;

  foreach()
    f[] = ( x > 0.75 ? 1 : 0.);
  
}

event properties (i++) {
  foreach_face()
    muv.x[] = 1e-3 * ( 2. - f[] ); 
}


event print ( t += 1 ; t <= 100 )
{
  
  static FILE * fp1 = popen ("ppm2mpeg > lid.mpg", "w");
  output_ppm (f, fp1, linear = true, spread = 4);
}
