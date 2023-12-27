#include "grid/multigrid.h"
#include "navier-stokes/centered.h"

int main()
{
  // coordinates of lower-left corner
  origin (-0.5, -0.5);
  // number of grid points
  init_grid(64);
  // viscosity

  const face vector muc[] = {1e-3,1e-3};
  mu = muc;

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
}


event print ( t += 10 ; t <= 200 )
{
   scalar omega[];
  vorticity (u, omega);
  static FILE * fp1 = popen ("ppm2mpeg > lid.mpg", "w");
  output_ppm (omega, fp1, linear = true, spread = 4);
}
